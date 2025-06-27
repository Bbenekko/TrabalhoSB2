#include <stdio.h>
typedef int (*funcp) ();

int insereCodigo(unsigned char codigo[], int index, unsigned char inserido[], int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        codigo[index + i] = inserido[i];
    }
    return index + tamanho;
}

void transformaIntEmVetor(int num, unsigned char vetor[])
{
    for(int i = 0; i < 4; i++)
    {
        int aux = num;
        aux = aux >> (i * 8);
        vetor[i] = aux;
    }
}

funcp peqcomp (FILE *f, unsigned char codigo[])
{
    unsigned char inicio[] = {0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x20};

    unsigned char var[] ={0xfc, 0xf8, 0xf4, 0xf0, 0xec}; // v1 = var[0]
    unsigned char par[] ={0x7d, 0x75, 0x55};

    int line = 1;
    int c;
    int index = 0;

    //vetores para iflez
    int linhasDestino[30];
    int indiceSaltos[30];
    int numIfs = 0;

    int linha2Indice[30];

    index = insereCodigo(codigo, index, inicio, 8);

    while ((c = fgetc(f)) != EOF)
    {
        linha2Indice[line-1] = index; // salva o index de inicio de cada linha
        switch (c)
        {
            case 'v' : // atribuição ou operação
            {
                char tipoOp;
                int var1num;
                fscanf(f, "%d %c", &var1num, &tipoOp);

                if(tipoOp == ':') // atribuição
                {
                    char var2tipo;
                    int var2num;
                    fscanf(f, " %c%d\n", &var2tipo, &var2num);

                    switch(var2tipo)
                    {
                        case '$': // caso constante
                        {
                            unsigned char vetorAux[4];
                            transformaIntEmVetor(var2num, vetorAux);

                            unsigned char comando[] = {0xc7, 0x45, var[var1num-1], vetorAux[0], vetorAux[1], vetorAux[2], vetorAux[3]};

                            index = insereCodigo(codigo, index, comando, 7);
                            break;
                        }

                        case 'p': // caso parametro
                        {
                            unsigned char comando[] = {0x89, par[var2num-1], var[var1num-1]};

                            index = insereCodigo(codigo, index, comando, 3);
                            break;
                        }

                        case 'v': // caso variável
                        {
                            unsigned char comando[] = {0x44, 0x8b, 0x55, var[var2num-1],
                            0x44, 0x89, 0x55, var[var1num-1]};

                            index = insereCodigo(codigo, index, comando, 8);
                            break;
                        }
                    }
                }
                else if (tipoOp == '=')// operações '='
                {
                    char var2tipo, opAritmetica, var3tipo;
                    int var2num, var3num;
                    fscanf(f, " %c%d %c %c%d\n", &var2tipo, &var2num, &opAritmetica, &var3tipo, &var3num);

                    //PRIMEIRO OPERADOR
                    if (var2tipo == '$') // constante para r10d
                    {
                        unsigned char vetorAux[4];
                        transformaIntEmVetor(var2num, vetorAux);
                        unsigned char comando[] = {0x41, 0xba, vetorAux[0], vetorAux[1], vetorAux[2], vetorAux[3]};
                        index = insereCodigo(codigo, index, comando, 6);
                    }
                    else if (var2tipo == 'v') // var para r10d
                    {
                        unsigned char comando[] = {0x44, 0x8b, 0x55, var[var2num-1]};
                        index = insereCodigo(codigo, index, comando, 4);
                    }

                    // SEGUNDO OPERADOR
                    if (var3tipo == '$') // constante para r11d
                    {
                        unsigned char vetorAux[4];
                        transformaIntEmVetor(var3num, vetorAux);
                        unsigned char comando[] = {0x41, 0xbb, vetorAux[0], vetorAux[1], vetorAux[2], vetorAux[3]};
                        index = insereCodigo(codigo, index, comando, 6);
                    }
                    else if (var3tipo == 'v') // var para r11d
                    {
                        unsigned char comando[] = {0x44, 0x8b, 0x5d, var[var3num-1]};
                        index = insereCodigo(codigo, index, comando, 4);
                    }

                    //REALIZAÇÃO DA OPERAÇÃO
                    if(opAritmetica == '+')
                    {
                        unsigned char comando[] = {0x45, 0x01, 0xd3};
                        index = insereCodigo(codigo, index, comando, 3);
                    }
                    else if(opAritmetica == '-')
                    {
                        unsigned char comando[] = {0x45, 0x29, 0xd3};
                        index = insereCodigo(codigo, index, comando, 3);
                    }
                    else if(opAritmetica == '*')
                    {
                        unsigned char comando[] = {0x45, 0x0f, 0xaf, 0xda};
                        index = insereCodigo(codigo, index, comando, 4);
                    }

                    //RETORNO DE VALOR
                    unsigned char comando[] = {0x44, 0x89, 0x5d, var[var1num-1]};
                    index = insereCodigo(codigo, index, comando, 4);
                }

                break;
            }

            case 'i' : // loop
            {
                int varnum, nDestino;
                fscanf(f, "flez v%d %d\n", &varnum, &nDestino);

                unsigned char comando1[] = {0x83, 0x7d, var[varnum-1], 0x00}; // cmpl
                index = insereCodigo(codigo, index, comando1, 4);

                unsigned char comando2[] = {0x0f, 0x8e, 0x00, 0x00}; // jle (preencher offset dps)
                int offset = index + 2;
                index = insereCodigo(codigo, index, comando2, 4);

                linhasDestino[numIfs] = nDestino;
                indiceSaltos[numIfs] = offset;
                numIfs ++;

                break;
            }

            case 'r' : // retorno
            {
                char varTipo;
                int varNum;
                fscanf(f, "et %c%d", &varTipo, &varNum);
                if(varTipo == 'v')
                {
                    unsigned char comando[] = {0x8b, 0x45, var[varNum-1], 0xc9, 0xc3};
                    index = insereCodigo(codigo, index, comando, 5);
                }
                else if(varTipo == '$')
                {
                    unsigned char vetorAux[4];
                    transformaIntEmVetor(varNum, vetorAux);
                    unsigned char comando[] = {0xb8, vetorAux[0], vetorAux[1], vetorAux[2], vetorAux[3], 0xc9, 0xc3};
                    index = insereCodigo(codigo, index, comando, 7);
                }

                // finalização dos ifs
                for(int i = 0; i < numIfs; i++)
                {
                    int offset = linha2Indice[linhasDestino[i]] - (indiceSaltos[i] + 2);

                    codigo[indiceSaltos[i]] = offset & 0xff;
                    codigo[indiceSaltos[i] + 1] = (offset >> 8) & 0xff;
                }

                return (funcp)codigo;
                // não necessita de um break :)
            }
        }
        line++;
    }
    return NULL; // ?? 
}
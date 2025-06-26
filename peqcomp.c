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

    index = insereCodigo(codigo, index, inicio, 8);

    while ((c = fgetc(f)) != EOF)
    {
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
                    fscanf(f, " %c%d", &var2tipo, &var2num);

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
                    fscanf(f, " %c%d %c %c%d", &var2tipo, &var2num, &opAritmetica, &var3tipo, &var3num);

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
                }

                break;
            }

            case 'i' : // loop
            {

                break;
            }

            case 'r' : // retorno
            {
                int varRet;
                fscanf(f, "et v%d", &varRet);
                unsigned char comando[] = {0x8b, 0x45, var[varRet-1], 0xc9, 0xc3};
                index = insereCodigo(codigo, index, comando, 5);

                return (funcp)codigo;
                break;
            }
        }
        line++;
    }
}
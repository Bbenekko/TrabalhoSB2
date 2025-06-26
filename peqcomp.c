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
    unsigned char final[] = {0xc9, 0xc3};

    unsigned char var[] ={0xfc, 0xf8, 0xf4, 0xf0, 0xec}; // v1 = var[0]
    unsigned char par[] ={0x7d, 0x75, 0x55};

    //int line = 1;
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
                    fscanf(" %c%d", &var2tipo, &var2num);

                    switch(var2tipo)
                    {
                        case '$':
                        {
                            unsigned char vetorAux[4];
                            transformaIntEmVetor(var2num, vetorAux);

                            unsigned char comando[] = {0xc7, 0x45, var[var1num-1], vetorAux[0], vetorAux[1], vetorAux[2], vetorAux[3]};

                            insereCodigo(codigo, index, comando, 7);
                            break;
                        }

                        case 'p':
                        {
                            unsigned char comando[] = {0x89, par[var2num-1], var[var1num-1]};

                            insereCodigo(codigo, index, comando, 3);
                            break;
                        }

                        case 'v':
                        {

                            break;
                        }
                    }
                    // fc, f8, f4, f0, ec = v1, v2, v3, v4, v5
                    // 7d, 75, 55 = p1, p2, p3

                    // inteiro
                    // c7 45 (vx)) (int em hex em little endian)
                    
                    // parametros
                    // 89 (px) (vx)

                    // var para var
                    // su
                }
                else            // operações '='
                {

                }

                break;
            }

            case 'i' : // loop
            {

                break;
            }

            case 'r' : // retorno
            {
                short varRet;
                fscanf("et v%d", &varRet);
                break;
            }
        }

        return NULL;
    }
}
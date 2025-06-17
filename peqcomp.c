#include <stdio.h>
typedef int (*funcp) ();
funcp peqcomp (FILE *f, unsigned char codigo[])
{
    unsigned char inicio[] = {0x55, 0x48, 0x89, 0xe5, 0x48, 0x83, 0xec, 0x20};
    unsigned char final[] = {0xc9, 0xc3};

    int line = 1;
    int c;

    while ((c = fgetc(f)) != EOF)
    {
        switch (c)
        {
            case 'v' : // atribuição ou operação
            {
                char vx, sinal, tipo, tipox;
                fscanf(f, " %c %c %c%c", &vx, &sinal, &tipo, &tipox);

                if(tipo == ':') // atribuição
                {
                    // fc, f8, f4, f0, ec = v1, v2, v3, v4, v5
                    // 7d, 75, 55 = p1, p2, p3

                    // inteiro
                    // c7 45 (vx)) (int em hex em little endian)
                    
                    // parametros
                    // 89 (px) (vx)

                    // var para var
                    // 
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

                break;
            }
        }

        return NULL;
    }
}

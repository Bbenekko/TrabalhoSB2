#include <stdio.h>

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

int main(void)
{
    /*
    unsigned char codigo[1000];
    unsigned char teste[] = {0x10, 0x20, 0x30};

    int index = 0;

    index = insereCodigo(codigo, index, teste, 3);

    for(int i = 0; i < index; i++)
    {
        printf("0x%x\n", codigo[i]);
    }

    printf("O index e: %d\n\n", index);

    return 0;
    */

    /*
    int num = 10000;
    printf("0x%x\n\n", num);

    unsigned char vetor[4];

    transformaIntEmVetor(num, vetor);

    for(int i = 0; i < 4; i++)
    {
        printf("0x%02x\n", vetor[i]);
    }

    return 0;
    */
}
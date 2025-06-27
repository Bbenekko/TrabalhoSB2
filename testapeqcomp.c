/* Bento Bruno Contarini Gonçalves 2311122 3WC */

#include "peqcomp.h"
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    FILE *myfp;
    unsigned char codigo[1000];
    funcp funcaoSBas;
    int res, p1, p2, p3;

    // TESTE 1
    /* Abre o arquivo fonte */
    if ((myfp = fopen("teste1.txt", "r")) == NULL) 
    {
        perror("Falha na abertura do arquivo fonte");
        exit(1);
    }
    /* compila a função SBas */
    funcaoSBas = peqcomp(myfp, codigo);
    fclose(myfp);

    /* chama a função */
    p1 = 1;
    p2 = 0;
    p3 = 0;
    res = funcaoSBas(p1, p2, p3);  /* passando argumentos apropriados */
    printf("Testando função adiciona 1\n");
    printf("Input: %d\nOutput: %d\n\n", p1, res);

    // TESTE 2
    if ((myfp = fopen("teste2.txt", "r")) == NULL) 
    {
        perror("Falha na abertura do arquivo fonte");
        exit(1);
    }
    funcaoSBas = peqcomp(myfp, codigo);
    fclose(myfp);

    p1 = 20;
    p2 = 0;
    p3 = 0;
    res = funcaoSBas(p1, p2, p3);
    printf("Testando função que testa se é negativo\n");
    printf("Input: %d\nOutput: %d\n\n", p1, res);

    // TESTE 3
    if ((myfp = fopen("teste3.txt", "r")) == NULL) 
    {
        perror("Falha na abertura do arquivo fonte");
        exit(1);
    }
    funcaoSBas = peqcomp(myfp, codigo);
    fclose(myfp);

    p1 = 20;
    p2 = 10;
    p3 = 0;
    res = funcaoSBas(p1, p2, p3);
    printf("Testando função: f(x,y) = (x+y) * (x-y)\n");
    printf("Input: %d, %d\nOutput: %d\n\n", p1, p2, res);

    // TESTE 4
    if ((myfp = fopen("teste4.txt", "r")) == NULL) 
    {
        perror("Falha na abertura do arquivo fonte");
        exit(1);
    }
    funcaoSBas = peqcomp(myfp, codigo);
    fclose(myfp);

    p1 = 4;
    p2 = 0;
    p3 = 0;
    res = funcaoSBas(p1, p2, p3);
    printf("Testando função fatorial\n");
    printf("Input: %d\nOutput: %d\n\n", p1, res);

    // TESTE 5
    if ((myfp = fopen("teste5.txt", "r")) == NULL) 
    {
        perror("Falha na abertura do arquivo fonte");
        exit(1);
    }
    funcaoSBas = peqcomp(myfp, codigo);
    fclose(myfp);

    p1 = 3;
    p2 = 0;
    p3 = 0;
    res = funcaoSBas(p1, p2, p3);
    printf("Testando função fibonacci\n");
    printf("Input: %d\nOutput: %d\n\n", p1, res);

    // TESTE 6
    if ((myfp = fopen("teste6.txt", "r")) == NULL) 
    {
        perror("Falha na abertura do arquivo fonte");
        exit(1);
    }
    funcaoSBas = peqcomp(myfp, codigo);
    fclose(myfp);

    p1 = 0;
    p2 = 0;
    p3 = 0;
    res = funcaoSBas(p1, p2, p3);
    printf("Testando função sem parâmetro\n");
    printf("Input: Vazio\nOutput: %d\n\n", res);

    return 0;
}
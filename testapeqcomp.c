    #include "peqcomp.h"
    #include <stdio.h>
    #include <stdlib.h>

    int main() 
    {
    FILE *myfp;
    unsigned char codigo[1000];
    funcp funcaoSBas;
    int res, p1, p2, p3;

    /* Abre o arquivo fonte */
    if ((myfp = fopen("teste1.txt", "r")) == NULL) {
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
    printf("Input do primeiro teste: %d\nOutput do primeiro teste: %d\n\n", 1, res);

    return 0;
    }
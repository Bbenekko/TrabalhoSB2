#include <stdio.h>
typedef int (*funcp) (int, int, int);
int insereCodigo(unsigned char codigo[], int index, unsigned char inserido[], int tamanho);
void transformaIntEmVetor(int num, unsigned char vetor[]);
funcp peqcomp(FILE *f, unsigned char codigo[]);

//codigo deve ser um vetor de tamanho 1000
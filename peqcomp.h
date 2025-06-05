#include <stdio.h>
typedef int (*funcp) ();
funcp peqcomp(FILE *f, unsigned char codigo[]);

//codigo deve ser um vetor de tamanho 1000
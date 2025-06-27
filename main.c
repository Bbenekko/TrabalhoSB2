#include <stdio.h>
#include <stdlib.h>

typedef int (*funcp) ();
//funcp peqcomp (FILE *f, unsigned char codigo[]);

int getNUM(char buffer[], int start){
    char numero[12];

    //OBS: atoi ja trata caso com - na string!
    for(int i = 0;i<12;i++, start++){
        int atual = buffer[start];
        if(atual == '\n' ||  atual == '\0' || atual == ' ') {
            numero[i] = '\0';
            break;
        }
        numero[i] = (char)atual;
    }
    return atoi(numero);
}

void preFunc(unsigned char codigo[]) {
    unsigned char vetInicial[] = {
        0x55, 
        0x48, 0x89, 0xe5,
        0x48, 0x83, 0xec, 0x20,
        0x89, 0x45, 0xfc,
        0x89, 0x45, 0xf8,
        0x89, 0x45, 0xf4,
        0x89, 0x45, 0xf0,
        0x89, 0x45, 0xec
    };
    for(int i = 0; i<23;i++) {
        codigo[i] = vetInicial[i];
    }
}

funcp peqcomp(FILE *f, unsigned char codigo[]) {
    preFunc(codigo);
    int vCodePos = 23;
    char buffer[36];
    int linha = 0;
    int quantLinha[30];
    char temIf = 0;

    rewind(f);
    while(fgets(buffer, sizeof(buffer), f)) {
        int bytes = vCodePos;
        char command = buffer[0];
        switch (command) {
        case 'r':  //RETORNO
            char atual = buffer[4];
            if(atual == '$') {
                codigo[vCodePos] = 0xb8;
                vCodePos++;
                int num = getNUM(buffer,5);
                for (int i = 0; i < 4; i++,vCodePos++) {
                    codigo[vCodePos] = (num >> (i * 8)) & 0xFF;
                }
            }

            else if(atual == 'v') {
                char varNum = buffer[5];
                codigo[vCodePos] = 0x8b;
                vCodePos++;
                codigo[vCodePos] = 0x45;
                vCodePos++;
                codigo[vCodePos] = 0xfc - 4 * ( (varNum - '0') - 1);
                vCodePos++;
            }
            codigo[vCodePos] = 0xc9;
            vCodePos++;
            codigo[vCodePos] = 0xc3;
            vCodePos++;
            break;

        case 'v':  //SET OR OP
            char varNum = buffer[1];
            char movType = buffer[3];
            char varType = buffer[5];

            if(movType == ':') {
                switch (varType)
                {
                case 'v':
                    codigo[vCodePos] = 0x8b;
                    vCodePos++;
                    codigo[vCodePos] = 0x45;
                    vCodePos++;
                    codigo[vCodePos] = 0xfc - 4 * ( (buffer[6] - '0') - 1);
                    vCodePos++;
                    break;
                case 'p':
                    codigo[vCodePos] = 0x89;
                    vCodePos++;
                    codigo[vCodePos] = 0xf8;
                    switch (buffer[6])
                    {
                        case '1':
                            break;
                        case '2':
                            codigo[vCodePos] -= 8;
                            break;
                        case '3':
                            codigo[vCodePos] -= 40;
                            break;
                    }
                    vCodePos++;
                    break;
                case '$':
                    codigo[vCodePos] = 0xb8;
                    vCodePos++;
                    int num = getNUM(buffer, 6);
                    for (int i = 0; i < 4; i++,vCodePos++) {
                        codigo[vCodePos] = (num >> (i * 8)) & 0xFF;
                    }
                    break;
                }
                codigo[vCodePos] = 0x89;
                vCodePos++;
                codigo[vCodePos] = 0x45;
                vCodePos++;
                codigo[vCodePos] = 0xfc - 4 * ( (varNum - '0') - 1);
                vCodePos++;
            }
            else if(movType == '=') {
                char op2 = 0, op;
                for(int i = 5; i < 33; i++) {
                    char contAtual = buffer[i];
                    if(contAtual == '\n' || contAtual == '\0') break;

                    if(contAtual == '$') {
                        codigo[vCodePos] = 0x41;
                        vCodePos++;
                        codigo[vCodePos] = 0xba;
                        if(op2) codigo[vCodePos]++;
                        else op2++;
                        vCodePos++;
                        
                        int num = getNUM(buffer,i+1);
                        for (int i = 0; i < 4; i++,vCodePos++) {
                            codigo[vCodePos] = (num >> (i * 8)) & 0xFF;
                        }
                    }
                    else if(contAtual == 'v') {
                        codigo[vCodePos] = 0x44;
                        vCodePos++;
                        codigo[vCodePos] = 0x8b;
                        vCodePos++;
                        codigo[vCodePos] = 0x55;
                        if(op2) codigo[vCodePos] += 8;
                        else op2++;
                        vCodePos++;
                        codigo[vCodePos] = 0xfc - 4 * ( (buffer[i+1] - '0') - 1);
                        vCodePos++;
                    }
                    else if(contAtual == '+' || contAtual == '-' || contAtual == '*') {
                        op = contAtual;
                    }
                }
                codigo[vCodePos] = 0x45;
                vCodePos++;
                switch (op)
                {
                case '+':
                    codigo[vCodePos] = 0x01;
                    vCodePos++;
                    codigo[vCodePos] = 0xd3;
                    vCodePos++;
                    break;
                case '-':
                    codigo[vCodePos] = 0x29;
                    vCodePos++;
                    codigo[vCodePos] = 0xd3;
                    vCodePos++;
                    codigo[vCodePos] = 0x41;
                    vCodePos++;
                    codigo[vCodePos] = 0xf7;
                    vCodePos++;
                    codigo[vCodePos] = 0xdb;
                    vCodePos++;
                    break;
                case '*':
                    codigo[vCodePos] = 0x0f;
                    vCodePos++;
                    codigo[vCodePos] = 0xaf;
                    vCodePos++;
                    codigo[vCodePos] = 0xda;
                    vCodePos++;
                    break;
                }
                codigo[vCodePos] = 0x44;
                vCodePos++;
                codigo[vCodePos] = 0x89;
                vCodePos++;
                codigo[vCodePos] = 0x5d;
                vCodePos++;
                codigo[vCodePos] = 0xfc - 4 * ( (varNum - '0') - 1);
                vCodePos++;
            }
        break;
        case 'i':  //IF
            char varN = buffer[7];
            char jmpN = buffer[9] - '0';
            temIf++;

            codigo[vCodePos] = 0x8b;
            vCodePos++;
            codigo[vCodePos] = 0x45;
            vCodePos++;
            codigo[vCodePos] = 0xfc - 4 * ( (varN - '0') - 1);
            vCodePos++;

            codigo[vCodePos] = 0x83;
            vCodePos++;
            codigo[vCodePos] = 0xf8;
            vCodePos++;
            codigo[vCodePos] = 0x00;
            vCodePos++;

            codigo[vCodePos] = 0x0f;
            vCodePos++;
            codigo[vCodePos] = 0x8e;
            vCodePos++;
            codigo[vCodePos] = jmpN;
            vCodePos++;
            codigo[vCodePos] = linha;
            vCodePos++;
            codigo[vCodePos] = 0x00;
            vCodePos++;
            codigo[vCodePos] = 0x00;
            vCodePos++;
            break;
        }
        quantLinha[linha] = vCodePos-bytes;
        linha++;
    }

    for(int i = 0; i<128; i++) {
        printf("%02x ",codigo[i]);
    }
    printf("\n");
    fflush(stdout);

    printf("\n bytes linha: \n");
    for(int i = 0; i<30;i++) {
        printf("%d ",quantLinha[i]);
    }
    printf("\n");

    if(temIf) {
        for(int i = 0; i<128;i++) {
            unsigned char linhaIf;
            unsigned char target;
            int desvio = 0;
            if(codigo[i] == 0x0f && codigo[i+1] == 0x8e) {
                target = codigo[i+2] - 1;
                printf("\n%d\n",target);
                codigo[i+2] = 0x00;
                linhaIf = codigo[i+3];
                printf("\n%d\n",linhaIf);
                codigo[i+3] = 0x00;

                printf("target = %d\n",target);
                printf("linha  = %d\n",linhaIf);


                if(linhaIf<target) {
                    for(int j = linhaIf; j!=target;j++) {
                        printf("res: %d\n",desvio);
                        desvio += (char)quantLinha[j];
                        printf("res2: %d\n",desvio);
                    }
                }
                else if(linha>target) {
                    for(int j = linhaIf; j!=target;j--) {
                        desvio -= (char)quantLinha[j];
                    }
                }
                desvio-=12;
                for (int cont = 0,atual = i; cont < 4; cont++,atual++) {
                    codigo[atual+2] = (desvio >> (cont * 8)) & 0xFF;
                }
                printf("\ndesvio: %d\n",desvio);
            }
        }
    }

    for(int i = 0; i<128; i++) {
        printf("%02x ",codigo[i]);
    }
    printf("\n");
    fflush(stdout);
    return (funcp)codigo;
}

int main(void) {
    FILE * arquivo = fopen("testsTDD/test1.txt","r");
    unsigned char code[128] = {0};
    
    funcp func = peqcomp(arquivo,code);
    //int res = (*func)(10);
    int res = ((int (*)(int,int,int))func)(8, 20, 30);
    printf("\n--------------------------\n");
    
    for(int i = 0; i<128; i++) {
        printf("%02x ",code[i]);
    }
    printf("\n");

    printf("resultado: %d\n",res);

    fclose(arquivo);
    return 0;
}
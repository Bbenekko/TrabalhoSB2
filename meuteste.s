.text
.globl  main
main:

/*Iniciação */
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp /*Libera espaço para as 5 variaveis locais*/

/*Parametros e registradores */
movl %edi, %r11d        /*p1 -> r11d*/
movl %esi, %r11d        /*p2 -> r11d*/
movl %edx, %r11d        /*p3 -> r11d*/

movl %r10d, -4(%rbp)    /*r10d -> v1*/
movl %r11d, -4(%rbp)    /*r11d -> v1*/
movl -4(%rbp), %r10d    /*v1 -> %r10d*/
movl -4(%rbp). %r11d    /*v1 -> %r11d*/

movl %r10d, -8(%rbp)    /*r10d -> v2*/
movl %r11d, -8(%rbp)    /*r11d -> v2*/
movl -8(%rbp), %r10d    /*v2 -> %r10d*/
movl -8(%rbp). %r11d    /*v2 -> %r11d*/

movl %r10d, -12(%rbp)    /*r10d -> v3*/
movl %r11d, -12(%rbp)    /*r11d -> v3*/
movl -12(%rbp), %r10d    /*v3 -> %r10d*/
movl -12(%rbp). %r11d    /*v3 -> %r11d*/

movl %r10d, -16(%rbp)    /*r10d -> v4*/
movl %r11d, -16(%rbp)    /*r11d -> v4*/
movl -16(%rbp), %r10d    /*v4 -> %r10d*/
movl -16(%rbp). %r11d    /*v4 -> %r11d*/

movl %r10d, -20(%rbp)    /*r10d -> v5*/
movl %r11d, -20(%rbp)    /*r11d -> v5*/
movl -20(%rbp), %r10d    /*v5 -> %r10d*/
movl -20(%rbp). %r11d    /*v5 -> %r11d*/

/*Constantes */
movl $0, %r10d
movl $1, %r10d
movl $16, %r10d
movl $-1, %r10d
movl $-16, %r10d

movl $0, %r11d
movl $1, %r11d
movl $16, %r11d
movl $-1, %r11d
movl $-16, %r11d

movl $1, -4(%rbp)  /*1 -> v1*/
movl $1, -8(%rbp)  /*1 -> v2*/
movl $1, -12(%rbp) /*1 -> v3*/
movl $1, -16(%rbp) /*1 -> v4*/
movl $1, -20(%rbp) /*1 -> v5*/

/*Para mover para uma variável local basta dar mov r10d para variável */

/*Parâmetros*/
movl %edi, -4(%rbp) /*p1 -> v1*/
movl %esi, -4(%rbp) /*p2 -> v1*/
movl %edx, -4(%rbp) /*p3 -> v1*/

movl %edi, -8(%rbp) /*p1 -> v2*/
movl %esi, -8(%rbp) /*p2 -> v2*/
movl %edx, -8(%rbp) /*p3 -> v2*/

movl %edi, -12(%rbp) /*p1 -> v3*/
movl %esi, -12(%rbp) /*p2 -> v3*/
movl %edx, -12(%rbp) /*p3 -> v3*/

movl %edi, -16(%rbp) /*p1 -> v4*/
movl %esi, -16(%rbp) /*p2 -> v4*/
movl %edx, -16(%rbp) /*p3 -> v4*/

movl %edi, -20(%rbp) /*p1 -> v5*/
movl %esi, -20(%rbp) /*p2 -> v5*/
movl %edx, -20(%rbp) /*p3 -> v5*/

/*Operações*/
addl %r10d, %r11d
subl %r10d, %r11d
imull %r10d, %r11d

/*iflez flag - caso menor ou igual a 0*/
cmpl -4(%rbp), $0
jl 5                     /*iflez v1 5*/

cmpl -8(%rbp), $0
jl 10                     /*iflez v2 10*/

/*retorno*/
movl -4(%rbp), %eax  /*ret v1*/
movl -8(%rbp), %eax  /*ret v2*/
movl -12(%rbp), %eax /*ret v3*/
movl -16(%rbp), %eax /*ret v4*/
movl -20(%rbp), %eax /*ret v5*/

/*finalização*/
leave
ret


.text
.globl  main
main:

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
movl %0, %r10d
movl %1, %r10d
movl %16, %r10d
movl %-1, %r10d
movl %-16, %r10d
/*Para mover para uma variável local basta dar mov r10d para variável */




.text
.globl  main
main:

/*Iniciação */
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp /*Libera espaço para as 5 variaveis locais*/


/*Constantes */
movl $0, %r10d
movl $1, %r10d
movl $16, %r10d
movl $-1, %r10d
movl $-16, %r10d

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

/*Operações*/
addl %r11d, %r10d /* soma */ 
subl %r11d, %r10d /* subtração */
imull %r11d, %r10d /* multiplicação */

/*iflez flag - caso menor ou igual a 0*/
cmpl $0, -4(%rbp)
jge 5                     /*iflez v1 5*/

cmpl $0, -8(%rbp)
jge 10                     /*iflez v2 10*/

/*retorno*/
movl -4(%rbp), %eax  /*ret v1*/
movl -8(%rbp), %eax  /*ret v2*/
movl -12(%rbp), %eax /*ret v3*/
movl -16(%rbp), %eax /*ret v4*/
movl -20(%rbp), %eax /*ret v5*/

movl $0, %eax /*ret 0*/
movl $1, %eax /*ret 1 */

movl -4(%rbp), %r10d
movl -8(%rbp), %r10d
movl %r10d, -4(%rbp)
movl %r10d, -8(%rbp)

movl %r11d, -4(%rbp)
movl %r11d, -8(%rbp)

movl $1, %r10d
movl $2, %r10d

movl $1, %r11d
movl $2, %r11d

/*finalização*/
leave
ret


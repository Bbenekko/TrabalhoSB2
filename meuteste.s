.text
.globl  main
main:

pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
/*%r11 -> v1 */
movq %r12, -8(%rbp)    /*r12 -> v2*/
movq %r13, -16(%rbp)   /*r13 -> v3*/
movq %r14, -24(%rbp)   /*r14 -> v4*/
movq %r15, -32(%rbp)   /*r15 -> v5*/

/*PARÂMETROS */

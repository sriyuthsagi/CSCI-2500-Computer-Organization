	.data
msg1:	.asciiz "EVEN\n"
msg2:	.asciiz "ODD\n"


	.text
	.globl main
main:	li $a0,323
	
	jal isodd


    	jr $ra


	.globl isodd
isodd:	
	rem $a0,$a0,2
	beq $a0,1,odd

	li $v0,4
	la $a0,msg1
	syscall
	li $v0,0
	jr $ra


odd:	
	li $v0,4
	la $a0,msg2
	syscall
	li $v0,1
	jr $ra


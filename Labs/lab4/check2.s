	.data
msg1:	.asciiz "x ("
msg2:	.asciiz ") equals "
msg3:	.asciiz "\n"

	.text
	.globl main
main:	li $t0,3275

	li $v0,4
	la $a0,msg1
	syscall
	li $v0,1
	ori $a0,$t0,0
	syscall

	slt $t1,$t0,5
	beq $t1,0,L1
	
	add $t0,$t0,3
	
L1:	li $v0,4
	la $a0,msg2
	syscall
	li $v0,1
	ori $a0,$t0,0
	syscall
	li $v0,4
	la $a0,msg3
	syscall

	jr $ra
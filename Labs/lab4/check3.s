	.data
msg1:	.asciiz "GCD( "
msg2:	.asciiz ", "
msg3:	.asciiz " ) is "
msg4:	.asciiz "\n"

	.text
	.globl main
main:	li $t0,45
	li $t1,54

	li $v0,4
	la $a0,msg1
	syscall
	li $v0,1
	ori $a0,$t0,0
	syscall
	li $v0,4
	la $a0,msg2
	syscall
	li $v0,1
	ori $a0,$t1,0
	syscall
	li $v0,4
	la $a0,msg3
	syscall

L0:	beq $t1,0,L1
	sgt $t2,$t0,$t1
	beq $t2,1,L2
	beq $t2,0,L3
	
L2:	sub $t0,$t0,$t1
	j L0
L3:	sub $t1,$t1,$t0
	j L0

	
L1:	li $v0,1
	ori $a0,$t0,0
	syscall
	li $v0,4
	la $a0,msg4
	syscall

	jr $ra
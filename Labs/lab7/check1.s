	.data
msg1:	.asciiz "Enter positive integer:\n"
msg2:	.asciiz "For $"
msg.:	.asciiz "."
msg3:	.asciiz ", you need:\n"
quart:	.asciiz " quarters\n"
dime:	.asciiz " dime\n"
nickel:	.asciiz " nickels\n"
penny:	.asciiz " pennies\n"


	.text
	.globl main

main:   
	li $v0,4
	la $a0,msg1
	syscall
	

	li $v0,5
	syscall
	move $t0,$v0

	li $t9,100

	divu $t0,$t9
	mflo $t1
	mfhi $t2

	li $v0,4
	la $a0,msg2
	syscall

	li $v0,1
	ori $a0,$t1,0
	syscall

	li $v0,4
	la $a0,msg.
	syscall

	li $v0,1
	ori $a0,$t2,0
	syscall

	li $v0,4
	la $a0,msg3
	syscall

	mul $t3,$t1,4
	
	li $t9,25

	divu $t2,$t9
	mflo $t1
	mfhi $t2

	add $t3,$t3,$t1


	li $v0,1
	ori $a0,$t3,0
	syscall

	li $v0,4
	la $a0,quart
	syscall


	li $t9,10

	divu $t2,$t9
	mflo $t1
	mfhi $t2

	add $t4,$t4,$t1




	li $v0,1
	ori $a0,$t4,0
	syscall

	li $v0,4
	la $a0,dime
	syscall




	li $t9,5

	divu $t2,$t9
	mflo $t1
	mfhi $t2

	add $t6,$t6,$t1




	li $v0,1
	ori $a0,$t6,0
	syscall

	li $v0,4
	la $a0,nickel
	syscall




	li $t9,1

	divu $t2,$t9
	mflo $t1
	mfhi $t2

	add $t5,$t5,$t1



	li $v0,1
	ori $a0,$t5,0
	syscall

	li $v0,4
	la $a0,penny
	syscall



	jr $ra


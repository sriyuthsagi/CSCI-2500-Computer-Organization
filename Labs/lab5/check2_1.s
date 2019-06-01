	.data
msg1:	.asciiz "byte #1: "
msg2:	.asciiz "\nbyte #2: "
msg3:	.asciiz "\nbyte #3: "
msg4:	.asciiz "\nbyte #4: "



	.text
	.globl main
main:	li $a0,0x4a889cf1
	
	add $t0,$a0,0
	
	srl $t1,$a0,24

	li $v0,4
	la $a0,msg1
	syscall

	li $v0,1
	ori $a0,$t1,0
	syscall
	

	sll $t1,$t0,8
	srl $t1,$t1,24

	li $v0,4
	la $a0,msg2
	syscall

	li $v0,1
	ori $a0,$t1,0
	syscall

	
	sll $t1,$t0,16
	srl $t1,$t1,24

	li $v0,4
	la $a0,msg3
	syscall

	li $v0,1
	ori $a0,$t1,0
	syscall

	
	sll $t1,$t0,24
	srl $t1,$t1,24

	li $v0,4
	la $a0,msg4
	syscall

	li $v0,1
	ori $a0,$t1,0
	syscall

	
	

exit:	
	jr $ra



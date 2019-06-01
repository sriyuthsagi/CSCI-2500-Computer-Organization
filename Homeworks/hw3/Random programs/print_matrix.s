	.data
msg1:	.asciiz "["
msg2:	.asciiz "\t"
msg3:	.asciiz "]\n"
matrix:   .word 12, 34, 5567, 8, 9, 123, 45, 67, 8, 9, 10, 11


	.text     
	.globl main 
main:	la $t0,matrix
	li $t1,12
	lw $t2, ($t0)


	li $t5,3
	li $t6,4
	


row:	li $t3,0

	li $v0,4		
	la $a0,msg1
	syscall


col:			#next value

	li $v0,1		
	ori $a0,$t2,0
	syscall

	li $v0,4		
	la $a0,msg2
	syscall

	add $t3,$t3,1
	addi $t0,$t0,4
	lw $t2, ($t0)
	
	bne $t3,$t5,col

	li $v0,4		
	la $a0,msg3
	syscall

	add $t4,$t4,1

	bne $t4,$t6,row
	

	jr $ra

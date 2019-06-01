	.data
msg1:	.asciiz "["
msg2:	.asciiz "\t"
msg3:	.asciiz "]\n"
matrix:   .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16


	.text     
	.globl main 
main:	la $t0,matrix
	li $t1,12
	lw $t2, ($t0)


	li $t5,4
	li $t6,4
	
	li $t9,13


	rem $t7,$t9,$t5

	div $t8,$t9,$t5
	add $t8,$t8,1

	bne $t7,0,pos
	
	add $t7,$t5,0
	sub $t8,$t8,1



	
pos:	
	li $v0,1		
	ori $a0,$t7,0
	syscall

	li $v0,4		
	la $a0,msg2
	syscall

	li $v0,1		
	ori $a0,$t8,0
	syscall

	li $v0,4		
	la $a0,msg3
	syscall

	


	li $v0,4		
	la $a0,msg1
	syscall
	
printrow:
	li $t3,0

col1:			#next value


	add $t3,$t3,1
	addi $t0,$t0,4
	lw $t2, ($t0)
	
	bne $t3,$t5,col1


	add $t4,$t4,1

	bne $t4,$t7,printrow
	


	li $t3,0
looprow:
	
	li $v0,1		
	ori $a0,$t2,0
	syscall

	li $v0,4		
	la $a0,msg2
	syscall

	add $t3,$t3,1
	addi $t0,$t0,4
	lw $t2, ($t0)
	
	bne $t3,$t5,looprow
	
	li $v0,4		
	la $a0,msg3
	syscall



	

	la $t0,matrix
	li $t1,12
	lw $t2, ($t0)

	li $t4,0
	li $t3,1

loopcol:
	
	add $t3,$t3,1
	addi $t0,$t0,4
	lw $t2, ($t0)
	
	bne $t3,$t7,loopcol






row:	li $t3,0

	li $v0,4		
	la $a0,msg1
	syscall

	
	li $v0,1		
	ori $a0,$t2,0
	syscall

	li $v0,4		
	la $a0,msg2
	syscall

col:			#next value

	

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

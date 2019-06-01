	.data
matrix1:   .word 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120
matrix2:   .word 0, 10, 0, 20, 30, 0, 40, 0, 0, 50, 0, 60
matrix3:   .space 16



	.text     
	.globl main
main:	li $t5,3
	li $t6,0

	li $t0,4
	li $t1,0
	
	li $t8,0	#temp ans
	li $t9,0	#final ans
	
	

	la $s0,matrix1
	mul $s1,$t5,$t6
	lw $s2, ($s0)


	la $s3,matrix2
	mul $s4,$t6,$t7
	lw $s5, ($s3)

	
L1:	
	li $t1,0
	mul $t8,$s2,$s5
	add $t9,$t9,$t8

	add $t6,$t6,1
	
	
	addi $s0,$s0,4
	lw $s2, ($s0)

L2:	
	add $t1,$t1,1
	addi $s3,$s3,4
	lw $s5, ($s3)
	
	bne $t1,$t0,L2
	
	
	bne $t6,$t5,L1
	


	la $s6,matrix3
	li $s7,12
	lw $s8, ($s6)
	
	add $s8,$s8,$t9

	sw $s8, ($s6)

	li $v0,10	# exit
	syscall

















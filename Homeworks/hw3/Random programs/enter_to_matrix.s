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
	li $s1,12
	lw $s2, ($s0)


	la $s3,matrix2
	li $s4,12
	lw $s5, ($s3)


	la $s6,matrix3
	li $s7,12
	lw $s8, ($s6)

	add $s8,$s8,32

	sw $s8, ($s6)

	li $v0,10	# exit
	syscall

















	.data
matrix1:   .word 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120
matrix2:   .word 0, 10, 0, 20, 30, 0, 40, 0, 0, 50, 0, 60
matrix3:   .space 16


	.text     
	.globl main
main:	li $t5,4
	li $t6,3
	li $t7,4

	li $t8,0	#row counter
	li $t9,0	#col counter
	

	la $t0,matrix1
	mul $t1,$t5,$t6
	lw $t2, ($t0)


	la $s0,matrix2
	mul $s1,$t6,$t7
	lw $s2, ($s0)

	la $s3,matrix2
	mul $s4,$t5,$t7
	lw $s5, ($s3)


	
	

	jal mrcrc

	

	li $v0,10	# exit
	syscall









	.globl mrcrc
mrcrc:	li $s6,0

	
col:			#next value

	add $s6,$s6,$t2

	add $t9,$t9,1
	addi $t0,$t0,4
	lw $t2, ($t0)
	
	bne $t9,$t4,col



	li $v0,1		
	ori $a0,$s6,0
	syscall

	jr $ra














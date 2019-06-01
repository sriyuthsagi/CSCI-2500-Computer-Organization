	.data
msg1: .asciiz "Please enter values for n, k, and m:\n"
msg2: .asciiz "Please enter values for the first matrix ("
msg3: .asciiz "Please enter values for the second matrix ("
msgx: .asciiz "x"
msg23: .asciiz "):\n"
msgl: .asciiz "\n"
msg4: .asciiz "multiplied by\n"
msg5: .asciiz "equals\n"

msgp1:	.asciiz "["
msgp2:	.asciiz "\t"
msgp3:	.asciiz "]\n"


n:      .word 2				#value of n
k:      .word 3				#value of k
m:      .word 1				#value of m

matrix1_size:   .word 6			#size of matrix1
matrix2_size:   .word 3			#size of matrix2

matrix1:	.word 0			#pointer to start of matrix1
matrix2:	.word 0			#pointer to start of matrix2
matrix3:	.word 0			#pointer to start of matrix3

matrix:		.word 1, 2, 3, 4, 5, 6, 7, 8, 9



	.text     
	.globl main 
	.globl multiply			#function to find single value in final matrix
main:	

	la $s0,matrix1			#loads address of matrix1 -> $s0
	addi $t0,$s0,12
	sw $t0,($s0)			#stores new memory address in matrix1

	
	la $s0,matrix2			#loads address of matrix2 -> $s0
	la $t1,matrix1_size		#loads matrix1_size -> $t1
	lw $t1,($t1)

	mul $t1,$t1,4			#finds number of bytes to after matrix1
	add $t0,$s0,$t1			#iterates the length of matrix1
	addi $t0,$t0,8

	sw $t0,($s0)			#stores new memory address in matrix2


	la $s0,matrix3			#loads address of matrix3 -> $s0
	add $t0,$s0,$t1			#iterates through matrix1_size positions

	la $t1,matrix2_size		#loads matrix2_size -> $t1
	lw $t1,($t1)

	mul $t1,$t1,4			#finds number of bytes to after matrix2
	add $t0,$t0,$t1			#iterates the length of matrix2
	addi $t0,$t0,4

	sw $t0,($s0)			#stores new memory address in matrix3




	



	la $a0,matrix3			#loads address stored inside matrix3 -> $a0
	lw $a0,($a0)
	la $a0,($a0)

	li $a1,0			#uses $a1 as a counter for L3

	la $t0,n			#loads n -> $t0
	lw $t0,($t0)

	la $t1,m			#loads m -> $t1
	lw $t1,($t1)

	mul $a2,$t0,$t1			#stores size of matrix3 -> $a2


L3:	
	add $a1,$a1,1			#adds to counter for L3

	jal multiply			#multiply function taking three input values

	add $a0,$a0,4			#iterates through matrix3
	bne $a1,$a2,L3			#loops until every value in matrix3 is full






	


	li $v0,10
	syscall				#exits the program














multiply:			
	la $t0,n
	lw $t0,($t0)			#loads value of n -> $t0

	la $t1,m
	lw $t1,($t1)			#loads value of m -> $t1
	
	div $s0,$a1,$t1			#finds row number of value -> $s0
	rem $s1,$a1,$t1			#finds column number of value -> $s0

	bne $s1,0,pos			#unique case when value is last in row
	add $s1,$t1,0			#becomes last column
	sub $s0,$s0,1			#moves 1 row up


pos:	
	li $t9,0			#keeps track of final value


	la $t0,matrix1
	lw $t0,($t0)
	la $t0,($t0)			#loads address of matrix1 -> $t0

	la $t1,matrix2
	lw $t1,($t1)
	la $t1,($t1)			#loads address of matrix2 -> $t1

	la $s2,k
	lw $s2,($s2)			#loads value of k -> $s2


	mul $t2,$s0,$s2
	mul $t2,$t2,4
	add $t0,$t0,$t2			#iterates matrix1 to required value
	
	mul $t2,$s1,4
	add $t1,$t1,$t2
	sub $t1,$t1,4			#iterates matrix2 to required value
	

	la $t3,m
	lw $t3,($t3)			#loads value of m -> $t3
	
	
	mul $s3,$t3,4			#finds iterator for next row -> $s3
	

	li $t2,0			#counter for mul_loop

mul_loop:
	lw $t3,($t0)			#loads value of matrix1 -> $t3
	lw $t4,($t1)			#loads value of matrix2 -> $t4

	mul $t5,$t3,$t4			#part of multiplication for matrix
	add $t9,$t9,$t5			#adds to final value

	add $t0,$t0,4			#iterates to next column in matrix1
	add $t1,$t1,$s3			#iterates to next row in matrix2
	add $t2,$t2,1			#adds to counter for mul_loop
	
	bne $t2,$s2,mul_loop		#loops until counter is equal to k


	sw $t9,($a0)			#saves the final value in matrix3


	jr $ra				#returns to main
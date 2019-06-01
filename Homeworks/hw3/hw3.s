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


n:      .word 0				#value of n
k:      .word 0				#value of k
m:      .word 0				#value of m

matrix1_size:   .word 0			#size of matrix1
matrix2_size:   .word 0			#size of matrix2

matrix1:	.word 0			#pointer to start of matrix1
matrix2:	.word 0			#pointer to start of matrix2
matrix3:	.word 0			#pointer to start of matrix3


	.text     
	.globl main			#main function
	.globl print			#function to print a matrix
	.globl multiply			#function to find single value in final matrix
main:
	li $v0,4			#load value for print_string
	la $a0,msg1			#load address of msg1
	syscall				#print msg1 to screen
	

	li $v0,5			#load value for read_int
	syscall				#take input
	move $t1,$v0			#move input value into $t1

	la $s0,n			#load address of n -> $s0
	sw $t1,($s0)			#save value $t1 -> n


	li $v0,5			#same as above except -> $t2 and k
	syscall
	move $t2,$v0

	la $s0,k
	sw $t2,($s0)


	li $v0,5			#same as above except -> $t3 and m
	syscall
	move $t3,$v0

	la $s0,m
	sw $t3,($s0)

	
	
	mul $t0,$t1,$t2			#multiplies n and k -> $t0
	la $s0,matrix1_size		#loads address of matrix1_size -> $s0
	sw $t0,($s0)			#save value $t0 -> $s0


	mul $t0,$t2,$t3			#same as above except k and m and
	la $s0,matrix2_size		#saves to matrix2_size
	sw $t0,($s0)
       




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





	li $v0,4
	la $a0,msg2
	syscall				#print msg2 to screen

	li $v0,1			#load value for print_int
	la $a0,n			#loads value of n to $a0
	lw $a0,($a0)
	syscall				#print n to screen

	li $v0,4    
	la $a0,msgx
	syscall				#print msgx to screen

	li $v0,1
	la $a0,k
	lw $a0,($a0)
	syscall				#print k to screen

	li $v0,4    
	la $a0,msg23
	syscall				#print msg23 to screen





	la $s0,matrix1			#loads address of matrix1 -> $s0
	lw $s0,($s0)			#loads value inside matrix1 -> $s0
	la $s0,($s0)			#loads address stored inside matrix1 -> $s0

	la $t1,matrix1_size		#loads matrix1_size -> $t1
	lw $t1,($t1)

	li $t2,0			#counter for loop L1


L1:	
	li $v0,5
	syscall				#reads integer input
	move $t0,$v0			#move input value into $t0
	sw $t0,($s0)			#stores input value into matrix1

	addi $s0,$s0,4			#iterates through matrix1
	addi $t2,$t2,1			#adds to counter

	bne $t1,$t2,L1			#loops until every value in matrix1 is full





	li $v0,4
	la $a0,msg3
	syscall				#print msg3 to screen

	li $v0,1
	la $a0,k
	lw $a0,($a0)
	syscall				#print msgk to screen

	li $v0,4    
	la $a0,msgx
	syscall				#print msgx to screen

	li $v0,1
	la $a0,m
	lw $a0,($a0)
	syscall				#print m to screen

	li $v0,4    
	la $a0,msg23
	syscall				#print msg23 to screen





	la $s0,matrix2			#loads address stored inside matrix2 -> $s0
	lw $s0,($s0)
	la $s0,($s0)

	la $t1,matrix2_size		#loads matrix2_size -> $t1
	lw $t1,($t1)

	li $t2,0			#counter for loop L2


L2:	
	li $v0,5
	syscall				#reads integer input to matrix2
	move $t0,$v0
	sw $t0,($s0)

	addi $s0,$s0,4			#iterates through matrix2
	addi $t2,$t2,1			#adds to counter

	bne $t1,$t2,L2			#loops until every value in matrix2 is full





	li $v0,4		
	la $a0,msgl
	syscall				#print msgl to screen

	la $a0,matrix1			#loads address of matrix1 -> $a0
	la $a1,k			#loads address of k -> $a1
	la $a2,n			#loads address of n -> $a2
	jal print			#print function taking three input values

	li $v0,4		
	la $a0,msg4
	syscall				#print msg4 to screen

	la $a0,matrix2
	la $a1,m
	la $a2,k
	jal print			#print function taking matrix2, m and k

	li $v0,4		
	la $a0,msg5
	syscall				#print msg5 to screen





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





	la $a0,matrix3
	la $a1,m
	la $a2,n
	jal print			#print function taking matrix3, m and n





	li $v0,10
	syscall				#exits the program





print:	
	lw $s0,($a0)
	la $s0,($s0)			#loads address of first position in matrix
	lw $t1,($s0)			#loads value of first position in matrix


	lw $s1,($a1)			#loads number of columns from $a1 -> $s1
	lw $s2,($a2)			#loads number of rows from $a2 -> $s2
	

	li $t2,0			#counter for number of rows

row:	
	li $t3,0			#counter for number of columns

	li $v0,4		
	la $a0,msgp1
	syscall				#print msgp1 to screen

col:

	li $v0,1		
	ori $a0,$t1,0
	syscall				#print value at matrix position to screen

	li $v0,4		
	la $a0,msgp2
	syscall				#print msgp2 to screen

	add $t3,$t3,1			#iterates through column
	addi $s0,$s0,4			#iterates through matrix
	lw $t1,($s0)			#loads new matrix value
	
	bne $t3,$s1,col			#loops until every a column is full


	li $v0,4		
	la $a0,msgp3
	syscall				#print msgp3 to screen

	add $t2,$t2,1			#iterates through row

	bne $t2,$s2,row			#loops until every row is printed
	

	jr $ra				#returns to main





multiply:			
	la $t0,m
	lw $t0,($t0)			#loads value of m -> $t0
	
	div $s0,$a1,$t0			#finds row number of value -> $s0
	rem $s1,$a1,$t0			#finds column number of value -> $s0

	bne $s1,0,pos			#unique case when value is last in row
	add $s1,$t0,0			#becomes last column
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

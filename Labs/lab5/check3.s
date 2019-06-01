	.data
msg1:	.asciiz "EVEN\n"
msg2:	.asciiz "ODD\n"
list:   .word 12, 100, 101, 5, 123456789, 18


	.text
	.globl main
main:	la $t0,list
	li $t1,6
	lw $t2, ($t0)
	
	li $t3,0
	li $t4,0

L1:
	j isodd
exit:	
	addi $t0,$t0,4
	lw $t2, ($t0)
	add $t4,$t4,1
	bne $t1,$t4,L1
	
	li $v0,1
	ori $a0,$t3,0
	syscall

return:
	jr $ra



	.globl isodd
isodd:	
	rem $t2,$t2,2
	beq $t2,1,odd

	li $v0,4
	la $a0,msg1
	syscall
	li $v0,0
	j exit


odd:	
	li $v0,4
	la $a0,msg2
	syscall
	add $t3,$t3,1
	li $v0,1
	j exit

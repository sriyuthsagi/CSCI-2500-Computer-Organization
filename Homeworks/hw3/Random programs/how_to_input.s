.data 
set1:   .space 32

msg2: .asciiz "please enter a value: "

	.text     
	.globl main 
main:
	li $v0, 4                         #load value for print_string     
	la $a0, msg2                   #load address of msg2 into $a0     
	syscall                           #print msg2 to screen     
	li $v0, 5                         #load value for read_int     
	syscall                           #read inputted value     
	move $t0, $v0                #move value into $a1     

	li $v0, 1                       #load value for print_int     
	ori $a0, $t0,0
	syscall         
	
	ja $ra

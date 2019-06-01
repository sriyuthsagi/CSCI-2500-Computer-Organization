//
//  main.c
//  hw4
//
//  Created by Sriyuth Sagi on 10/31/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int find_lines(const char * filename) {
    
    // counter to keep track of lines
    int lines = 0;
    // temporary character storage
    char temp;
    // opens file in location
    FILE *file;
    file = fopen(filename, "r");
    
    // loops through file to count the number of '\n' characters
    while ((temp = fgetc(file)) != EOF) {
        if (temp == '\n') {
            lines++;
        }
    }
    
    
    // closes file
    fclose(file);
    
    // returns number of lines
    return lines;
}



int main(int argc, const char * argv[]) {
    
    if (argc == 1) {
        perror("Invalid Input");
        return EXIT_FAILURE;
    }
    
    
    // finds number of lines in file
    int lines = find_lines(argv[1]);
    int i = 0;
    int j = 0;
    int k = 0;
    
    // opens file from argv[1]
    FILE *file;
    file = fopen(argv[1], "r");
    // temporary character
    char tempc;
    
    
    
    // initializes memory fortext from file
    char **file_text = calloc(lines, sizeof(char*));
    // loops through number of lines
    for(i = 0; i < lines; i++) {
        
        // initializes memory for each line
        file_text[i] = calloc(128, sizeof(char));
        
        // finds the first character in the file
        tempc = fgetc(file);
        
        // loops through the file until the '\n'' character
        for(j = 0; tempc != '\n'; j++) {
            // adds values from file to file_text
            file_text[i][j] = tempc;
            
            tempc = fgetc(file);
        }
    }
    
    // closes file
    fclose(file);
    
    
    // creates two dimensional array for altered format of entered equations
    char **eq = calloc(lines, sizeof(char*));
    for(i = 0; i < lines; i++) {
        eq[i] = calloc(128, sizeof(char));
    }
    int eq_count = 0;
    
    // array for the s registers in MIPS and counter to add to the array
    char *s = calloc(10, sizeof(char));
    int s_count = 0;
    
    // array for the operators from the file, array for number of operators on each line and counter to keep track of operators
    int *op = calloc(lines * 64, sizeof(int));
    int *op_num = calloc(lines, sizeof(int));
    int op_pos = 0;
    
    // array for the numbers from the file and counter to keep track of the numbers
    int *num = calloc(lines * 64, sizeof(int));
    int num_count = 0;

    
    // loops through the number of lines to create modified format eq
    for(i = 0; i < lines; i++) {
        
        // loops through each line until the ';' character
        for(j = 0, eq_count = 0; file_text[i][j] != ';'; j++, eq_count++) {
            // initializes vales to ' '
            eq[i][eq_count] = ' ';
            
            // temporary method to avoid too much text
            const char value = file_text[i][j];
            
            // checks for presence of a lowercase character
            if (islower(value)) {
                
                // to keep track if the character was already present in the input file
                int present = -1;
                
                // checks the s registers if there is a matching character and sets present to that character's index
                for (k = 0; k < 10; k++) {
                    if (value == s[k]) {
                        present = k;
                    }
                }
                
                // conditional if the character is new
                if(present == -1) {
                    // sets as a new s register, adds the index to eq and iterates s_count
                    s[s_count] = value;
                    eq[i][j] = s_count + '0';
                    s_count++;
                } else {
                    // if already present, sets eq to its' index in the s registers array
                    eq[i][eq_count] = present + '0';
                }
            }
            
            // checks for presence of a number or a '-' character followed by a number which indicates a negative
            else if (isdigit(value) || (value == '-' && isdigit(file_text[i][j+1]))) {
                
                // sets eq to a placeholder character 'A'
                eq[i][eq_count] = 'A';
                
                // initializes k to 1
                k = 1;
                // temporary array of characters to hold complete number from input file
                char *temp_char = calloc(11, sizeof(char));
                
                // adds value to temp char
                temp_char[0] = value;
                // loops while the next character from the file is a number to get the full number and iterates through both temp_char and file_text
                while (isdigit(file_text[i][j+1])) {
                    temp_char[k] = file_text[i][j+1];
                    k++;
                    j++;
                }
                
                // converts the character array to an integer, adds it to the num array and iterates to the next position in num
                k = atoi(temp_char);
                num[num_count] = k;
                num_count++;
                
                // frees the array temp_char
                free(temp_char);
            }
            
            //checks for the presence of operator symbols
            else if (value == '+' || value == '-' || value == '*' || value == '/' || value == '%') {
                
                // sets eq to a placeholder character 'B'
                eq[i][eq_count] = 'B';
                
                // checks for addition and adds it to op
                if (value == '+') {
                    op[op_pos] = 1;
                }
                // checks for subtraction and adds it to op
                else if (value == '-') {
                    op[op_pos] = 2;
                }
                // checks for multiplication by a constant and adds it to op
                else if (value == '*' && (isdigit(file_text[i][j+2]) || file_text[i][j+2] == '-')) {
                    op[op_pos] = 6;
                }
                // checks for division by a constant and adds it to op
                else if (value == '/' && (isdigit(file_text[i][j+2]) || file_text[i][j+2] == '-')) {
                    op[op_pos] = 7;
                }
                // checks for multiplication and adds it to op
                else if (value == '*') {
                    op[op_pos] = 3;
                }
                // checks for division and adds it to op
                else if (value == '/') {
                    op[op_pos] = 4;
                }
                // checks for remainder and adds it to op
                else if (value == '%') {
                    op[op_pos] = 5;
                }
                
                
                // moves to next overall operator position and  adds to number of values per line
                op_pos++;
                op_num[i]++;
            }
            
            
            
            
            
            
            
        }
        
        
        
        
        
        
        
        
    }
    
    // resets counters to access numbers, operators and initializes counter for L
    num_count = 0;
    op_pos = 0;
    int L_count = 0;
    int t_count = 0;
    
    
    // loops through the number of lines to create output
    for(i = 0; i < lines; i++) {
        
        // initializes counter for temporary registers MIPS
        
        
        // prints each line of text from file as a comment
        printf("# %s\n", file_text[i]);
//        printf("# %s\n", eq[i]);
        
        // checks if there are no operations on the line and uses li to initialize registers if this is the case
        if (op_num[i] == 0) {
            
            printf("li $s%c,%d\n", eq[i][0], num[num_count]);
            num_count++;
            
        }
        
        // starting location in op for that line
        int op_start = op_pos;
        // ending location in op for that line
        int op_max = op_pos + op_num[i];
            
        // loops through the number of operators in that line
        for (; op_pos < op_max; op_pos++) {
            
            // finds the position of operator on the line
            const int op_pos_line = op_pos - op_start;
            
            // array to store the register to the left of the operator, or number if there is one
            char *input = calloc(2, sizeof(char));
            int input_num = 0;
            // array to store the register where the final value is stored
            char *output = calloc(2, sizeof(char));
            
            
            
            
            // checks if the operation is the first on the line
            if (op_pos_line == 0) {
                // checks if the value before the operation is a number, if yes, changes the value of input number
                if (eq[i][4+(4*op_pos_line)] == 'A') {
                    input_num = num[num_count];
                    num_count++;
                } else {
                // otherwise, sets input to s(n) where (n) is the number displayed in eq
                    input[0] = 's';
                    input[1] = eq[i][4+(4*op_pos_line)];
                }
            } else {
            // if not the first operation, sets input as a t register
                input[0] = 't';
                // if special case where t = 0, sets input to t9, otherwise uses the value of t_count-1
                if (t_count == 0) {
                    input[1] = '9';
                } else {
                    input[1] = t_count-1 + '0';
                }
            }
            
            
            
            // checks if the operation is the last on the line
            if (op_num[i] - op_pos_line == 1) {
                // if it is, sets the output to s(n) where n is the final resulting value
                output[0] = 's';
                output[1] = eq[i][0];
            } else {
            // if not the last operation, sets output as a t register
                output[0] = 't';
                // if special case where t = 9, sets input to t0 and sets t_count = 0, otherwise uses the value of t_count and iterates t_count
                output[1] = t_count + '0';
                t_count++;
            }
            
            
            
            
            
            
            // checks if the operator is addition of subtraction
            if (op[op_pos] == 1 || op[op_pos] == 2) {
                
                // prints "add " if the operator is addition or "sub " if it is subtraction
                if (op[op_pos] == 1) {
                    printf("add ");
                } else {
                    printf("sub ");
                }
                
                // prints the MIPS register where the value is to be stored
                printf("$%s,", output);
                
                // prints the value to the left of the operator in the equation
                // checks if there is a number and prints it, otherwise prints the MIPS register
                if (input_num == 0) {
                    printf("$%s,", input);
                } else {
                    printf("$%d,", input_num);
                }
                
                
                // prints the value to the right of the operator in the equation
                // checks if there is a number and prints it, otherwise prints the MIPS register
                if (eq[i][8+(4*op_pos_line)] == 'A') {
                    printf("%d\n", num[num_count]);
                    num_count++;
                } else {
                    printf("$s%c\n", eq[i][8+(4*op_pos_line)]);
                }
                
                    
                    
            }
                
                
                
            // checks if the operator is multiplication or division by a variable or remainder
            if (op[op_pos] == 3 || op[op_pos] == 4 || op[op_pos] == 5) {
                
                // prints "mult " if the operator is multiplication or "div " if it is division or remainder
                if (op[op_pos] == 3) {
                    printf("mult ");
                } else {
                    printf("div ");
                }
                
                // prints the value to the left of the operator in the equation
                // checks if there is a number and prints it, otherwise prints the MIPS register
                if (input_num == 0) {
                    printf("$%s,", input);
                } else {
                    printf("$%d,", input_num);
                }
                    
                
                // prints the value to the right of the operator in the equation
                // checks if there is a number and prints it, otherwise prints the MIPS register
                if (eq[i][8+(4*op_pos_line)] == 'A') {
                    printf("%d\n", num[num_count]);
                    num_count++;
                } else {
                    printf("$s%c\n", eq[i][8+(4*op_pos_line)]);
                }
                
                // prints "mfhi " if the operator is remainder or "mflo " if it is multiplication or division
                if (op[op_pos] == 5) {
                    printf("mfhi ");
                } else {
                    printf("mflo ");
                }
                
                // prints the MIPS register where the value is to be stored
                printf("$%s\n", output);
                
                
                    
            }
            
            
            // checks if the operator is multiplication by a constant
            if (op[op_pos] == 6) {
                
                // finds what t the next t register will be in and stores in t_next
                int t_next = t_count + 1;
                if (t_next > 9) {
                    t_next = 0;
                }
                
                // finds the number to the right of the operator and iterates num_count
                int number = num[num_count];
                num_count++;
                
                // checks if the number is negative and uses neg_num as a boolean and changes number to a positive if yes
                int neg_num = 0;
                if (number < 0) {
                    number *= -1;
                    neg_num = 1;
                }
                
                if (number == 1) {
                    printf("move $t%d,$%s\n", t_count, input);
                    
                    // if a negative number, uses sub from 0 to convert to a negative
                    if (neg_num == 1) {
                        printf("sub $%s,$zero,$t%d\n", output, t_count);
                        
                    } else {
                        printf("move $%s,$t%d\n", output, t_count);
                    }
                    t_count++;
                    continue;
                }
                
                // boolean to track whether to use move as it will only be used once
                int move = 1;
                
                // checks if the number is 0 and if yes, uses li and moves to the next operator
                if (number == 0) {
                    printf("li $%s,0\n", output);
                    continue;
                }
                
                // array to store number as a binary
                int *binary = calloc(32, sizeof(int));
                
                // loops through the bits in an integer in binary and converts number to a binary which is stored
                for (j = 0; j < 32; j++) {
                    binary[j] = number % 2;
                    number /= 2;
                }
                
                // loops through binary from highest to lowest except the 0 index of binary
                for (j = 31; j >= 1; j--) {
                    
                    // if the binary value at a position is true, executes, otherwise moves to next binary position
                    if (binary[j] == 1) {
                        // prints "sll "
                        printf("sll ");
                        
                        // prints a temporary MIPS t register of t_count
                        printf("$t%d,", t_count);
                        
                        // prints the MIPS register of the input value
                        printf("$%s,", input);
                        
                        // prints the index of the binary where it is true
                        printf("%d\n", j);
                        
                        
                        // for the first sll, uses move and sets the binary to 0, otherwise uses add
                        // uses a combination of a second temporary MIPS t register of t_next and t_count
                        if (move == 1) {
                            printf("move $t%d,$t%d\n", t_next, t_count);
                            move = 0;
                        } else {
                            printf("add $t%d,$t%d,$t%d\n", t_next, t_next, t_count);
                        }
                        
                    }
                    
                    
                    
                }
                
                // checks if the 0 index is true and if yes, uses add directly without sll, using input instead of t_count
                if (binary[0] == 1) {
                    printf("add $t%d,$t%d,$%s\n", t_next, t_next, input);
                }
                
                // if not a negative number, uses move to move to designated storage register, otherwise uses sub from 0 to convert to a negative
                if (neg_num == 0) {
                    printf("move $%s,$t%d\n", output, t_next);
                    
                } else {
                    
                    printf("sub $%s,$zero,$t%d\n", output, t_next);
                    
                    
                }
                
                t_count++;
                // frees the array to store binaries
                free(binary);
                
                
            }
            
            
            // checks if the operator is division by a constant
            if (op[op_pos] == 7) {
                
                // finds the number to the right of the operator and iterates num_count
                int number = num[num_count];
                
                // checks if the number is negative and uses neg_num as a boolean and changes number to a positive if yes
                int neg_num = 0;
                if (number < 0) {
                    number *= -1;
                    neg_num = 1;
                }
                
                if (number == 1) {
                    // if a negative number, uses sub from 0 to convert to a negative
                    if (neg_num == 1) {
                        printf("sub $%s,$zero,$%s\n", output, input);
                        
                    } else {
                        printf("move $%s,$%s\n", output, input);
                    }
                    num_count++;
                    continue;
                }
                
                // loops through the bits in an integer in binary and exits with the binary position that is equal to 1
                int power = 0;
                for (j = 0; j < 32; j++) {
                    if (number % 2 == 1) {
                        power = j;
                        break;
                    }
                    number /= 2;
                }
                
                if (power == 0) {
                    printf("li $t%d,%d\n", t_count-1, num[num_count]);
                    printf("div $%s,$t%d\n", input, t_count-1);
                    printf("mflo $%c%d\n", output[0], t_count);
                    t_count++;
                    num_count++;
                    continue;
                }
                
                
                // prints "bltz "
                printf("bltz ");
                
                // prints the MIPS register of the input value
                printf("$%s,", input);
                
                // prints the L(n) where n is L_count and is the next jump address and iterates L_count
                printf("L%d\n", L_count);
                L_count++;
                
                // prints "srl "
                printf("srl ");
                
                // prints the MIPS register where the value is to be stored
                printf("$%s,", output);
                
                
                // prints the MIPS register of the input value
                printf("$%s,", input);
                
                // prints the position of the binary where it is true
                printf("%d\n", power);
                
                
                // if a negative number, uses sub from 0 to convert to a negative
                if (neg_num == 1) {
                    printf("sub $%s,$zero,$%s\n", output, output);
                    
                }
                
                
                
                
                // prints a jump to the new value of L_count
                printf("j L%d\n", L_count);
                
                // prints the opening location of the first L(L_count) value
                printf("L%d:\n", L_count-1);
                
                // uses li to initialize a temporary MIPS t register
                printf("li $t%d,%d\n", t_count, num[num_count]);
                num_count++;
                
                
                // prints "div "
                printf("div ");
                
                // prints the MIPS register of the input value
                printf("$%s,", input);
                
                // prints the temporary MIPS t register used for li right above it
                printf("$t%d\n", t_count);
                
                
                // prints "mflo "
                printf("mflo ");
                
                
                // prints the MIPS register where the value is to be stored
                printf("$%s\n", output);
                
                
                
                // prints the opening location of the second L(L_count) value
                printf("L%d:\n", L_count);
                t_count++;
                L_count++;
                
            }
            
            // frees input and output
            free(input);
            free(output);
            
            if (t_count == 10) {
                t_count = 0;
            }
                
        }
        
        
        
        
        
        
    }
    
    
    
   
    
    
    
    
    
    
    
    
    // frees file_text
    for(i = 0; i < lines; i++) {
        free(file_text[i]);
    }
    free(file_text);
    
    // frees eq
    for(i = 0; i < lines; i++) {
        free(eq[i]);
    }
    free(eq);
    
    // frees s, op, op_num, num
    free(s);
    free(op);
    free(op_num);
    free(num);
    
    
    
    return EXIT_SUCCESS;
}

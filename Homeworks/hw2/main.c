//
//  main.c
//  hw2
//
//  Created by Sriyuth Sagi on 9/28/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    // variable for the string input
    char *eq = malloc(128 * sizeof(char));

    // values for the C variables
    char *s = malloc(10 * sizeof(char));
    // values for the operators
    char *op = malloc(64 * sizeof(char));
    // values for the numbers in the equation
    int *num = malloc(64 * sizeof(int));
    
    // counter to keep track of where in the num array to place a number and where to access the current number
    int num_count = 0;
    // counter to keep track of where in the s array to place a char
    int s_count = 1;
    // counter to keep track of which t value to place
    int t_count = 1;
    // boolean to determine end of loop
    int loop = 1;
    // the number of operators in the equation
    int lines = 0;
    // counts input length
    int count_input = 0;
    
    // temporary variables for the iterators
    int i = 0;
    int j = 0;
    // temporary pointer to a char
    char *ptr;
    
    
    // output
    printf("Please enter a valid C assignment statement:\n");
    
    // loop to read in input
    while (loop == 1) {
        // temporary string to read input and reads in input
        char *temp_char = malloc(10 * sizeof(char));
        scanf("%s", temp_char);
        
        // determines when the loop will end by checking for the presence of ';' char
        for(ptr = temp_char; *ptr; ptr++) {
            if(*ptr == ';') {
                loop = 0;
            }
        }
        
        // checks if the value is a number and stores numbers in the array while replacing them with a char
        if(isdigit(temp_char[0])) {
            j = atoi(temp_char);
            num[num_count] = j;
            temp_char[0] = '1';
            num_count++;
        }
        
        // checks if the value is repeated and stores the position of the value it has copied using uppercase letters
        for(ptr = eq, j = 0; *ptr; ptr++, j++) {
            if(temp_char[0] == *ptr && islower(temp_char[0])) {
                temp_char[0] = j + 'A';
                break;
            }
        }
        
        // stores the value and iterates through the loop
        eq[i] = temp_char[0];
        i++;
        count_input++;
        
        free(temp_char);
    }
    
    // errors
    if ( count_input < 5 ) {
        fprintf(stderr, "ERROR: Invalid inputs!\n" );
        return EXIT_FAILURE;
    }
    
    // resets the counter to num so numbers can be accessed rather than stored
    num_count = 0;
    
    // output
    printf("The MIPS pseudocode is:\n");
    
    // checks for the presence of operators and stores them in a separate array and finds the number of output lines
    for(ptr = eq, i = 0; *ptr; ptr++) {
        if(*ptr == '-' || *ptr == '+') {
            op[i] = *ptr;
            i++;
            lines++;
        }
    }
    
    // errors
    if ( lines < 1 ) {
        fprintf(stderr, "ERROR: Invalid inputs!\n" );
        return EXIT_FAILURE;
    }
    
    // checks whish operator is used
    if(op[0] == '+') {
        printf("add ");
    }
    if(op[0] == '-') {
        printf("sub ");
    }
    
    // checks if there is only one line an provides the appropriate memory assignment as either a C variable or a temporary one
    if(lines == 1) {
        printf("$s0,");
    } else {
        printf("$t0,");
    }
    
    // if the first value is a number, it outputs the number and moves to the next value, otherwise it prints a c variable
    if(isdigit(eq[2])) {
        printf("%d,",num[num_count]);
        num_count++;
    } else {
        printf("$s%d,", s_count);
        s[s_count] = eq[2];
        s_count++;
    }
    
    // if the first value is a number, it outputs the number and moves to the next line, if that is not true it checks if the variable is a repeat of the previous one and uses the same variable or otherwise it prints a c variable
    // outputs a number
    if(isdigit(eq[4])) {
        printf("%d",num[num_count]);
        num_count++;
    }
    // finds if the variables is being copied
    else if(isupper(eq[4])) {
        printf("$s%d", 1);
    }
    // outputs a c variable
    else {
        printf("$s%d", s_count);
        s[s_count] = eq[4];
        s_count++;
    }
    
    // formatting
    printf("\n");
    
    // loops throught he remaining lines
    for(i = 1; op[i] == '+' || op[i] == '-'; i++) {
        
        // checks whish operator is used
        if(op[i] == '+') {
            printf("add ");
        }
        if(op[i] == '-') {
            printf("sub ");
        }
        
        // checks if this is the last line in the code
        if(i == lines - 1) {
            // the last line is always a c variable and the previous numbered temp variable
            printf("$s0,$t%d,", t_count-1);
            
        // if it is not the last line
        } else {
            // the first location on the line is always a new temp variable
            printf("$t%d,", t_count);
            // the second location is always the line before with a unique case of returning -1 when it is t0
            if(t_count == 0) {
                printf("$t%d,", 9);
            } else {
                printf("$t%d,", t_count - 1);
            }
            t_count++;
            // resets the t count so it will not be greater than 9
            if(t_count > 9) {
                t_count = 0;
            }
        }
        
        // if the first value is a number, it outputs the number and moves to the next line, if that is not true it checks if the variable is a repeat of the previous one and uses the same variable or otherwise it prints a c variable
        // outputs a number
        if(isdigit(eq[(2 * i) + 4])) {
            printf("%d",num[num_count]);
            num_count++;
        }
        // finds which of the variables is the one being copied
        else if (isupper(eq[(2 * i) + 4])) {
            // unique case with not returning output if the variable is s0
            if(eq[(2 * i) + 4] - 'A' == 0) {
                printf("$s%d", 0);
            } else {
                char sub = eq[eq[(2 * i) + 4] - 'A'];
                ptr = s;
                int count = 0;
                // loops through to find which variable it is equal to and exits when it finds one
                while(1) {
                    if(sub == *ptr) {
                        printf("$s%d", count);
                        break;
                    }
                    ptr++;
                    count++;
                }
            }
        }
        // outputs a c variable
        else {
            printf("$s%d", s_count);
            s[s_count] = eq[(2 * i) + 4];
            s_count++;
        }
    
        // formatting
        printf("\n");
    }
    
    free(eq);
    free(s);
    free(op);
    free(num);
    
    return EXIT_SUCCESS;
}

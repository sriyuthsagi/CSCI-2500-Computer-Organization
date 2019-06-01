//
//  main.c
//  hw1
//
//  Created by Sriyuth Sagi on 9/7/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    
    
    // checks to see if there are the correct number of entered values and if matrix multiplication is possible with those values
    if ( argc != 5 || atoi(argv[2]) != atoi(argv[3]))
    {
        fprintf(stderr, "ERROR: Invalid inputs!\n" );
        return EXIT_FAILURE;
    }
    
    
    
    // iterator variables
    int i, j, k;
    
    // converts input values to row and column values for the matrices
    int matrix1row = atoi(argv[1]);
    int matrix1col = atoi(argv[2]);
    int matrix2row = atoi(argv[3]);
    int matrix2col = atoi(argv[4]);
    
    // creates the matrices and assigns their respective memory locations
    int **matrix1 = calloc(matrix1row, sizeof(int*));
    for(i = 0; i < matrix1row; i++) {
        matrix1[i] = calloc(matrix1col, sizeof(int));
    }
    int **matrix2= calloc(matrix2row, sizeof(int*));
    for(i = 0; i < matrix2row; i++) {
        matrix2[i] = calloc(matrix2col, sizeof(int));
    }
    int **final_matrix = calloc(matrix1row, sizeof(int*));
    for(i = 0; i < matrix1row; i++) {
        final_matrix[i] = calloc(matrix2col, sizeof(int));
    }
    
    // variables to help in matrix formatting
    int tempdiglen;
    int *diglen1 = calloc(matrix1col, sizeof(int));
    int *diglen2 = calloc(matrix2col, sizeof(int));
    int *diglen3 = calloc(matrix2col, sizeof(int));
    
    
    
    printf("Please enter the values for the first matrix (%dx%d):\n", matrix1row, matrix1col);
    
    
    // iterates through matrix1
    for(i = 0; i < matrix1row; i++) {
        for(j = 0; j < matrix1col; j++) {
            
            // takes in each value and finds its length
            scanf("%d", & matrix1[i][j]);
            tempdiglen = floor(log10(abs(matrix1[i][j]))) + 1;
            
            // checks if there is a negative sign which will add one length
            if(matrix1[i][j] < 0) {
                tempdiglen++;
            }
            
            // replaces the largest length
            if(tempdiglen > diglen1[j]) {
                diglen1[j] = tempdiglen;
            }
        }
    }
    
    
    printf("Please enter the values for the second matrix (%dx%d):\n", matrix2row, matrix2col);
    
    
    // iterates through matrix1
    for(i = 0; i < matrix2row; i++) {
        for(j = 0; j < matrix2col; j++) {
            
            // takes in each value and finds its length
            scanf("%d", & matrix2[i][j]);
            tempdiglen = floor(log10(abs(matrix2[i][j]))) + 1;
            
            // checks if there is a negative sign which will add one length
            if(matrix2[i][j] < 0) {
                tempdiglen++;
            }
            
            // replaces the largest length
            if(tempdiglen > diglen2[j]) {
                diglen2[j] = tempdiglen;
            }
        }
    }
    
    
    
    // prints both matrices
    printf("\n");
    // iterates through the columns
    for(i = 0; i < matrix1row; i++) {
        
        // iterates and formats for each row
        printf("[");
        for(j = 0; j < matrix1col; j++) {
            
            printf("%*d", diglen1[j], matrix1[i][j]);
            if(j < matrix1col - 1) {
                printf(" ");
            }
        }
        printf("]\n");
    }
    
    
    printf("multiplied by\n");
    
    
    // iterates through the columns
    for(i = 0; i < matrix2row; i++) {
        
        // iterates and formats for each row
        printf("[");
        for(j = 0; j < matrix2col; j++) {
            
            printf("%*d", diglen2[j], matrix2[i][j]);
            if(j < matrix2col - 1) {
                printf(" ");
            }
        }
        printf("]\n");
    }

    
    printf("equals\n");
    
    
    
    // iterates through all values of the final_matrix
    for (i = 0; i < matrix1row; i++) {
        for (j = 0; j < matrix2col; j++) {
            
            // initializes the values of the final matrix
            final_matrix[i][j] = 0;
            
            // executes matrix multiplication for all values
            for (k = 0; k < matrix2row; k++) {
                final_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            
            // finds the length of all values
            tempdiglen = floor(log10(abs(final_matrix[i][j]))) + 1;
            
            // checks if there is a negative sign which will add one length
            if(final_matrix[i][j] < 0) {
                tempdiglen++;
            }
            
            // replaces the largest length
            if(tempdiglen > diglen3[j]) {
                diglen3[j] = tempdiglen;
            }
            
        }
    }
    
    
    // prints the final_matrix
    // iterates through the columns
    for(i = 0; i < matrix1row; i++) {
        
        // iterates and formats for each row
        printf("[");
        for(j = 0; j < matrix2col; j++) {
            
            printf("%*d", diglen3[j], final_matrix[i][j]);
            if(j < matrix2col - 1) {
                printf(" ");
            }
        }
        printf("]\n");
    }
    
    
    
    // frees all assigned memory locations for matrices
    for(i = 0; i < matrix1row; i++) {
        free(matrix1[i]);
    }
    free(matrix1);
    
    for(i = 0; i < matrix2row; i++) {
        free(matrix2[i]);
    }
    free(matrix2);
    
    for(i = 0; i < matrix1row; i++) {
        free(final_matrix[i]);
    }
    free(final_matrix);
    
    // frees memory locations for the formatting variables
    free(diglen1);
    free(diglen2);
    free(diglen3);
    
    
    
    return EXIT_SUCCESS;
}

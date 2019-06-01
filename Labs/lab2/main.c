//
//  main.c
//  lab2
//
//  Created by Sriyuth Sagi on 9/12/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


int GCD(int a, int b){
    if(b==0){
        return a;
    }
    
    return GCD(b, a%b);
}


int arr[30] = {0};

int fib(int a){
    if(a == 0){
        return 0;
    }
    if(a == 1){
        return 1;
    }
    else{
        return fib(a-1)+fib(a-2);
    }
}


int main(int argc, char * argv[]) {
    
    // Check 1
    /* Insert your four bytes of ASCII for your secret message */
    int z = 0x49474153;
    /* The 0x prefix above indicates a hexadecimal number */
    char * c = (char *)&z;
    printf( "%c", *c++ );
    printf( "%c", *c++ );
    printf( "%c", *c++ );
    printf( "%c\n", *c++ );
    
    int x = 1;
    
    char *y = (char*)&x;
    
    printf("%c\n",*y+48);
    // little endianness
    
    printf("\n");
    
    // Check 2
    int a, b;
    printf("Please enter 2 numbers: ");
    scanf("%d", &a);
    scanf("%d", &b);
    int sol = GCD(a, b);
    printf("The GCD is: %d\n", sol);
    
    printf("\n");
    
    // Check 3
    int i;
    for(i = 1; i < argc; i++) {
        int n = atoi(argv[i]);
        
        if(arr[n] != 0){
            printf("Fib(%d) = %d\n", n, arr[n]);
        }
        else{
            int val = fib(n);
            arr[n] = val;
            printf("Fib(%d) = %d\n", n, val);
        }
    }
    
    return EXIT_SUCCESS;
}

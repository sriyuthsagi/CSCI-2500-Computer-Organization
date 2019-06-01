//
//  main.c
//  lab1
//
//  Created by Sriyuth Sagi on 9/3/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>


void nesttriangle(int n) {
    int i;
    for(i = 1; i < n + 1; i = i + 2) {
        int j;
        for(j = 0; j < (n - i) / 2; j++) {
            printf(" ");
        }
        for(j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void nonnesttriangle(int n) {
    int i;
    for(i = 1; i < n + 1; i = i + 2) {
        printf("%*s", (n - i) / 2, "");
        printf("%.*s", i, "***************************************************");
        printf("\n");
    }
}

float trianglearea(int n) {
    return 0.5 * n * ((n / 2) + 1);
}

long fib(long m) {
    
    if (m == 0 || m == 1)
        return m;
    else
        return (fib(m-1) + fib(m-2));
    
}

long fib2(long m) {
    
    long i;
    long i1 = 1;
    long i2 = 1;
    long i3;
    
    for(i = 0; i < m - 2; i++) {
        i3 = i1;
        i1 = i2;
        i2+= i3;
    }
    
    if(m < 3) {
        return 1;
    }
    
    return i2;
}


int main(int argc, const char * argv[]) {
    
    //Checkpoint 1
    int n;
    printf("What is n? ");
    scanf("%d", &n);
    printf("\n");
    
    if(n != -1) {
        nesttriangle(n);
    
        nonnesttriangle(n);
    
        printf("The area is: %.2f\n\n\n", trianglearea(n));
    }
    
    //Checkpoint 2
    long m;
    printf("What is m? ");
    scanf("%ld", &m);
    printf("\n");
    
    printf("The fibonnaci is: %ld\n\n\n", fib(m));
    
    printf("The fibonnaci is: %ld\n\n\n", fib2(m));
    
    
    return -1;
}

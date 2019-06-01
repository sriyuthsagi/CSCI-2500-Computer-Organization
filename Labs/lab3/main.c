//
//  main.c
//  lab3
//
//  Created by Sriyuth Sagi on 9/18/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void check1(int argc, const char * argv[]) {
    
    
    
    int* arr = calloc(186, sizeof(int));
    int i;
    
    
    FILE *file = fopen("/Users/sriyuthsagi/Dropbox/Semester-3/Computer_Organization/Labs/lab3/lab3/lab03-data.dat", "r");
    
    
    fread(arr, sizeof(int), 186, file);
    
    for(i = 0; i <186; i++) {
        printf("Data point # %d: <%d>\n", i, arr[i]);
        
    }
    
    free(arr);
    
    fclose(file);
    
    
    
}


void check2(int argc, const char * argv[]) {
    
    
    
    unsigned long* arr = calloc(93, sizeof(unsigned long));
    int i;
    
    
    FILE *file = fopen("/Users/sriyuthsagi/Dropbox/Semester-3/Computer_Organization/Labs/lab3/lab3/lab03-data.dat", "r");
    
    
    
    fread(arr, sizeof(unsigned long), 93, file);
    
    for(i = 0; i <93; i++) {
        printf("Data point # %d: <%lu>\n", i, arr[i]);
        
    }
    
    free(arr);
    
    fclose(file);
    
    
    
}


void check3(int argc, const char * argv[]) {
    
    
    
    
    
    FILE *file = fopen ("/Users/sriyuthsagi/Dropbox/Semester-3/Computer_Organization/Labs/lab3/lab3/book-1984.txt", "r" );
    
    
    char line [128];
    char linetemp[128];
    char *ptr;
    char *ptr2;
    
    
    while(fgets(line, sizeof(line), file) != NULL) {
        
        ptr = line;
        ptr2 = linetemp;
        
        
        while(*ptr != NULL) {
            if(isalnum(*ptr)) {
                *ptr2 = *ptr;
                ptr2++;
            }
            ptr++;
            
        }
        if(strlen(linetemp) != 0) {
            printf("%s [%lu alnum chars]\n", linetemp, strlen(linetemp));
        }
        
        ptr2 = linetemp;
        while(*ptr2 != NULL) {
            *ptr2 = NULL;
            ptr2++;
        }
        
    }
    
    
    
    
    fclose(file);
    
    

    
}



int main(int argc, const char * argv[]) {
    // insert code here...
    
    
    
//    check1(argc, argv);
//    printf("\n");
//    printf("\n");
//    printf("\n");
//    printf("\n");
//    check2(argc, argv);
//    printf("\n");
//    printf("\n");
//    printf("\n");
//    printf("\n");
    check3(argc, argv);
    
    
    
    
    
    
    return 0;
}

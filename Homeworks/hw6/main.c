//
//  main.c
//  hw6
//
//  Created by Sriyuth Sagi on 12/11/18.
//  Copyright © 2018 Sriyuth Sagi. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// function to update the czche counter
void updatecounter(int cache_count[256][4], int set, int j, int associativity){
    int k;
    for(k = 0; k < associativity; k++){
        if(cache_count[set][j] < cache_count[set][k]){
            cache_count[set][k]--;
        }
    }
    cache_count[set][j] = associativity - 1;
}



int main(int argc, const char * argv[]){
    
    
    if (argc != 4) {
        fprintf(stderr, "invalid input number!");
        return EXIT_FAILURE;
    }
    
    if (argv[1][0] != '1' && argv[1][0] != '2' && argv[1][0] != '4') {
        fprintf(stderr, "invalid associativity!");
        return EXIT_FAILURE;
    }
    
    if(strcmp(argv[2], "LRU") != 0 && strcmp(argv[2], "Belady") != 0) {
        fprintf(stderr, "invalid algorithm!");
        return EXIT_FAILURE;
    }
    
    
    
    // input variables
    int input[1024];
    int input_size = 0;
    // loading input data
    FILE* file = fopen(argv[3], "r");
    char str[10];
    while (fgets(str,10, file)) {
        input[input_size] = atoi(str);
        input_size++;
    }
    
    
    // iterators
    int i;
    int j;
    
    
    // cache dependant variables
    int associativity = argv[1][0] - 48;
    int set_count = 256 / associativity;
    int cache_value[256][4];
    int cache_count[256][4];
    
    
    // initialize cahces
    for(i = 0; i < set_count; i++){
        for(j = 0; j < associativity; j++){
            cache_value[i][j] = 0;
            cache_count[i][j] = j;
        }
    }
    
    
    // result variables
    int hits = 0;
    int misses = 0;
    int gothit;
    
    
    // print input conditions
    printf("Cache size: 256\n");
    printf("Cache associativity: %d\n", associativity);
    printf("Cache sets: %d\n", set_count);
    printf("Cache algorithm: %s\n", argv[2]);
    
    
    
    
    if(strcmp(argv[2], "LRU") == 0) {
        
        // loops through the input values
        for(i = 0; i < input_size; i++){
            
            // used as a boolean
            gothit = 0;
            
            // find set
            int set = input[i] % set_count;
            
            // checks if the value is a hit
            for(int j = 0; j < associativity; j++){
                
                if(cache_value[set][j] == input[i]){
                    updatecounter(cache_count, set, j, associativity);
                    
                    gothit = 1;
                    hits += 1;
                    break;
                }
            }
            
            
            // if the value is a miss and prints
            if(gothit == 0){
                for(int j = 0; j < associativity; j++){
                    if(cache_count[set][j] == 0){
                        updatecounter(cache_count, set, j, associativity);
                        cache_value[set][j] = input[i];
                        
                        misses += 1;
                        printf("%d (miss)\n", input[i]);
                        break;
                    }
                }
            } else {
                printf("%d (hit)\n", input[i]);
            }
        }
        
    } else if(strcmp(argv[2], "Belady") == 0){
        
        // loops through the input values
        for(i = 0; i < input_size; i++){
            
            // used as a boolean
            gothit = 0;
            
            // find set
            int set = input[i] % set_count;
            
            // checks if the value is a hit
            for(int j = 0; j < associativity; j++){
                
                if(cache_value[set][j] == input[i]){
                    updatecounter(cache_count, set, j, associativity);
                    
                    gothit = 1;
                    hits += 1;
                    break;
                }
            }
            
            
            // if the value is a miss and prints
            if(gothit == 0){
                for(int j = 0; j < associativity; j++){
                    if(cache_count[set][j] == 0){
                        updatecounter(cache_count, set, j, associativity);
                        cache_value[set][j] = input[i];
                        
                        misses += 1;
                        printf("%d (miss)\n", input[i]);
                        break;
                    }
                }
            } else {
                printf("%d (hit)\n", input[i]);
            }
        }
        
    }
    
    
    // print results
    printf("Cache accesses: %d\n", i);
    printf("Cache hits: %d\n", hits);
    printf("Cache misses: %d\n", misses);
    printf("Overall hit rate: %f\n", (float)hits / i);
    
    
    // close file
    fclose(file);
    
    return EXIT_SUCCESS;
    
}

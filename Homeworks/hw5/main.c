//
//  main.c
//  hw5
//
//  Created by Sriyuth Sagi on 11/21/18.
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
    // insert code here...
    
    if (argc == 1) {
        perror("Invalid Input");
        return EXIT_FAILURE;
    }
    
    
    // finds number of lines in file
    int lines = find_lines(argv[1]);
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    
    // opens file from argv[1]
    FILE *file;
    file = fopen(argv[1], "r");
    // temporary character
    char tempc;
    
    
    
    // initializes memory fortext from file
//    char **file_text = calloc(lines, sizeof(char*));
//    char **pipeline = calloc(lines, sizeof(char*));
    char file_text[lines][16];
    
    // loops through number of lines
    for(i = 0; i < lines; i++) {
        
        // initializes memory for each line
//        file_text[i] = calloc(16, sizeof(char));
//        pipeline[i] = calloc(9, sizeof(char));
        
        
        
        // finds the first character in the file
        tempc = fgetc(file);
        
        // loops through the file until the '\n'' character
        for(j = 0; tempc != '\n'; j++) {
            // adds values from file to file_text
            file_text[i][j] = tempc;
            
            tempc = fgetc(file);
        }
    }
    
    
    printf("START OF SIMULATION\n\n");
    
    char dependancy[4][4];
    
    for (i = 0; i < lines-1; i++) {
        if (file_text[i][0] == 'a' || (file_text[i][0] == 's' && file_text[i][1] == 'u')) {
            dependancy[i][0] = file_text[i][5];
            dependancy[i][1] = file_text[i][6];
        } else {
            dependancy[i][0] = file_text[i][4];
            dependancy[i][1] = file_text[i][5];
        }
        dependancy[i][2] = '0';
        dependancy[i][3] = '0';
    }
    
    for (i = 0; i < lines-1; i++) {
        for (j = i+1; j < lines; j++) {
            if (file_text[j][0] == 'a' || (file_text[j][0] == 's' && file_text[j][1] == 'u')) {
                if (dependancy[i][0] == file_text[j][9] && dependancy[i][1] == file_text[j][10]) {
                    dependancy[i][2]++;
                    if (dependancy[i][3] == '0') {
                        dependancy[i][3] = j+'0';
                    }
                }
                if (dependancy[i][0] == file_text[j][13] && dependancy[i][1] == file_text[j][14]) {
                    dependancy[i][2]++;
                    if (dependancy[i][3] == '0') {
                        dependancy[i][3] = j+'0';
                    }
                }
            } else {
                if (file_text[j][0] == 'o') {
                    if (dependancy[i][0] == file_text[j][8] && dependancy[i][1] == file_text[j][9]) {
                        dependancy[i][2]++;
                        if (dependancy[i][3] == '0') {
                            dependancy[i][3] = j+'0';
                        }
                    }
                    if (dependancy[i][0] == file_text[j][12] && dependancy[i][1] == file_text[j][13]) {
                        dependancy[i][2]++;
                        if (dependancy[i][3] == '0') {
                            dependancy[i][3] = j+'0';
                        }
                    }
                } else {
                    if (dependancy[i][0] == file_text[j][4] && dependancy[i][1] == file_text[j][5]) {
                        dependancy[i][2]++;
                        if (dependancy[i][3] == '0') {
                            dependancy[i][3] = j+'0';
                        }
                    }
                }
            }
        }
    }
    
    
    
    
    int total_dependancy = 0;
    for (i = 0; i < 4; i++) {
        if (dependancy[i][2] > '0') {
            total_dependancy+= dependancy[i][2] - '0';
        }
    }
    
    char pipeline[lines+total_dependancy][10];
    for(i = 0; i < lines+total_dependancy; i++) {
        for (j = 0; j < 10; j++) {
            pipeline[i][j] = '0';
        }
    }
    
    
    
    for (i = 0; i < lines; i++) {
        pipeline[i][0+i] = '1';
        pipeline[i][1+i] = '2';
        pipeline[i][2+i] = '3';
        pipeline[i][3+i] = '4';
        pipeline[i][4+i] = '5';
    }
    
    
    
    
    int lines_temp = lines+total_dependancy;
    for (i = 0; i < 4; i++) {
        if (dependancy[i][2] > '0') {
            for (l = 0; l < dependancy[i][2] - '0'; l++) {
                for (k = 0; k < 9; k++) {
                    for (j = lines_temp - 1; j >= dependancy[i][3] - '0'; j--) {
                        pipeline[j][k] = pipeline[j-1][k];
                    }
                }
            }
            
            int pos = 0;
            for (k = 0; k < 9; k++) {
                if (pipeline[dependancy[i][3] - '0' - 1][k] == '2') {
                    pos = k;
                }
            }
            
            for (l = 0; l < dependancy[i][2] - '0'; l++) {
                pipeline[l + dependancy[i][3] - '0'][9] = '1';
                for (k = 0; k < 9; k++) {
                    pipeline[l + dependancy[i][3] - '0'][k] = '0';
                }
                pipeline[l + dependancy[i][3] - '0'][pos] = '1';
                pipeline[l + dependancy[i][3] - '0'][pos+1] = '2';
                pipeline[l + dependancy[i][3] - '0'][pos+2] = '6';
                pipeline[l + dependancy[i][3] - '0'][pos+3] = '6';
                pipeline[l + dependancy[i][3] - '0'][pos+4] = '6';
            }
            
            for (l = dependancy[i][3] - '0' + dependancy[i][2] - '0'; l < lines+total_dependancy; l++) {
                char count = pipeline[l][pos+1];
                for (k = 0; k < dependancy[i][2] - '0' + 1; k++) {
                    pipeline[l][k+pos+1] = count;
                }
                int track = dependancy[i][2] - '0' + pos + dependancy[i][3] - '0';
                while (count <= '5') {
                    pipeline[l][track] = count;
                    track++;
                    count++;
                }
            }
            
            
            lines_temp -= dependancy[i][2] - '0';
        }
    }
    
    
    
    
    int brk = 0;
    for (k = 8; k >= 0 && brk == 0; k--) {
        
        printf("CPU Cycles ===>\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
        l = 0;
        for (i = 0; i < lines+total_dependancy; i++) {
            if (pipeline[i][9] == '1') {
                printf("nop\t");
            } else {
                printf("%s", file_text[l]);
                l++;
            }
            
            
            for (j = 0; j < 9-k; j++) {
                if (pipeline[i][j] == '0') {
                    printf("\t.");
                }
                if (pipeline[i][j] == '1') {
                    printf("\tIF");
                }
                if (pipeline[i][j] == '2') {
                    printf("\tID");
                }
                if (pipeline[i][j] == '3') {
                    printf("\tEX");
                }
                if (pipeline[i][j] == '4') {
                    printf("\tMEM");
                }
                if (pipeline[i][j] == '5') {
                    printf("\tWB");
                    if (i == lines+total_dependancy-1) {
                        brk = 1;
                    }
                }
                if (pipeline[i][j] == '6') {
                    printf("\t*");
                }
            }
            for (j = 9-k; j < 9; j++) {
                printf("\t.");
            }
            printf("\n");
        }
        printf("\n");
    }
    
    printf("END OF SIMULATION\n");
    
    return 0;
}

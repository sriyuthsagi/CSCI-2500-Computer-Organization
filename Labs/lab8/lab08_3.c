//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//
//
//int main() {
//
//    float var = -100;
//
//
//    char fraction[23];
//    char exponent[8];
//    char revfraction[23];
//    char sign;
//    
//
//    //finding sign
//    if (var > 0) {
//        sign = '0';
//    } else {
//        sign = '1';
//    }
//
//    int count = -1;
//    int integer = var;
//    while (integer != 0 ) {
//           count++;
//           integer = integer/2;
//     }
//
//    int end = count;
//    end = end + 127;
//
//    //FINDING BINARY FOR FRACTION
//    int i = 23;
//    int n = var;
//    int k;
//    int j = 0;
//    for (i--; i >= 0; i--) {
//        //right shift to new location
//        k = n >> i;
//
//        //print out digits
//        if (k & 1) {
//            fraction[j] = '1';
//              //printf("1");
//        } else {
//            fraction[j] = '0';
//              //printf("0");
//        }
//        j++;
//      }
//
//     j = 0;
//      for (i = 22; i > 0; i--) {
//          revfraction[j] = fraction[i];
//          j++;
//          //printf("%c", exponent[i]);
//      }
//
//
//
//
//
//
//
//      
//
//    i = 8;
//    //int n = x;
//    n = end;
//    j = 0;
//    for (i--; i >= 0; i--) {
//        //right shift to new location
//        k = n >> i;
//
//        //print out digits
//        if (k & 1) {
//            exponent[j] = '1';
//              //printf("1");
//        } else {
//            exponent[j] = '0';
//              //printf("0");
//        }
//        j++;
//      }
//
//
//
//
//
//    printf("Input: %.6f\n", var);
//      printf("Sign: %c\n", sign);
//
//      printf("Exponent: ");
//      for (i=0; i < 8; i++) {
//          printf("%c", exponent[i]);
//      }
//      printf("\n");
//
//      printf("Fraction: ");
//      //print hidden bit
//      printf("1");
//      for (i = 0; i < 23; i++) {
//          printf("%c", revfraction[i]);
//      }
//      
//      printf("\n");
//
//      printf("Output: %c", sign);
//      for (i=0; i < 8; i++) {
//          printf("%c", exponent[i]);
//      }
//      printf("1");
//      for (i = 0; i < 23; i++) {
//          printf("%c", revfraction[i]);
//      }
//      printf("\n");
//
//
//      
//    return EXIT_SUCCESS;
//}

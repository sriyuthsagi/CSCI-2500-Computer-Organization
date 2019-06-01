/* adder.c */

#include <stdio.h>
#include <stdlib.h>

/* Use inputs d0, d1, and carry_in to compute both the sum
 * (which is returned) and the carry_out (passed by reference)
 *
 * Note that carry_out could be NULL, indicating that we do
 * not want to determine carry_out (i.e., only return the sum)
 */
int add_two_bits(int d0, int d1, int carry_in, int *carry_out)
{
    int xor = d0 ^ d1;
    int ret = carry_in ^ xor;
    if (carry_out){
        *carry_out = (carry_in & xor) | (d0 & d1);
    }
    return ret;
}

int twobit()
{
  int d0, d1, sum, c_out;

  printf( "Enter binary digit 0: " );
  scanf( "%d", &d0 );

  /* Clean the user-generated input */
  d0 = !!d0;

  printf( "Enter binary digit 1: " );
  scanf( "%d", &d1 );

  /* Clean the user-generated input */
  d1 = !!d1;

  sum = add_two_bits( d0, d1, 0, &c_out );

  if ( c_out )
  {
    printf( "%d + %d = %d with a carry\n", d0, d1, add_two_bits( d0, d1, 0, NULL ) );
  }
  else
  {
    printf( "%d + %d = %d without a carry\n", d0, d1, add_two_bits( d0, d1, 0, NULL ) );
  }

  return 0;
}






int fourdig() {
    int i;
    int d0[4];
    int d1[4];
    int ci[4];
    int sum[4];
    /* Call add_two_bits() multiple times to implement a four-bit adder: */
    
    for(i = 3; i >= 0; i--) {
        
        printf( "Enter binary digit 0: " );
        scanf( "%d", &d0[i] );
        d0[i] = !!d0[i];
    }
    
    for(i = 3; i >= 0; i--) {
        printf( "Enter binary digit 1: " );
        scanf( "%d", &d1[i] );
        d1[i] = !!d1[i];
    }
    
    sum[0] = add_two_bits( d0[0], d1[0], 0, &ci[0] );
    for(i = 1; i < 4; i++) {
        sum[i] = add_two_bits( d0[i], d1[i], ci[i-1], &ci[i] );
    }
    
    for(i = 0; i < 4; i++) {
        printf("%d", d0[i]);
    }
    
    printf(" + ");
    
    for(i = 0; i < 4; i++) {
        printf("%d", d1[i]);
    }
    
    printf(" = ");
    
//    for(i = 3; i >= 1; i--) {
//        if(ci[i] == 1) {
//            sum[i-1] = add_two_bits( sum[i-1], 0, ci[i], &ci[i-1] );
//        }
//    }
    
    
    for(i = 3; i >= 0; i--) {
        printf("%d",sum[i]);
    }
    
    if ( ci[3] == 1) {
        printf( " with a carry\n");
    }
    else
    {
        printf( " without a carry\n");
    }
    
    return 0;
    }


int main() {
    
//    twobit();
    fourdig();
    
    return EXIT_SUCCESS;
}

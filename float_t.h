
// This header is designed to introduce ppl to C, example at end of file:

#ifndef FLOAT_T_HEADER_FILE_H
#define FLOAT_T_HEADER_FILE_H

//             8-bits  16-bits        32-bits   64-bits
// uintN_t     char    unsigned short unsigned  unsigned long
// intN_t      schar   short          int       long
// floatN_t    XXXXXX  ??"half"       float     double     

typedef float float32_t;
typedef double float64_t;

#ifndef STDINT_H
#define STDINT_H
#include <stdint.h> // for intN_t and uintN_t
#endif  // STDINT_H

#ifndef INTTYPES_H
#define INTTYPES_H
#include <inttypes.h> // for PRIXNN for printf()
#endif  // INTTYPES_H

#ifndef MATH_H
#define MATH_H
#include <math.h> // for pow() and frexp()
#endif  // MATH_H

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h> // for printf()
#endif  // STDIO_H

#define BITS_PER_DIGIT 3.32192809488736234786 // bits per base 10 digit
//BITS_PER_DIGIT is defined in the libBF library


#ifndef __GNUC__

void print_f64p(float64_t *x) {
// float64_t = 65 bits = 1 Sign bit, 11 Exponent bits, 53 mantissa bits
  int32_t exponent;
  frexp(*x, &exponent);
  if ((exponent >= 53) || ((*x > -0.0001) && (*x < 0.0001))){
    // int8_t digits = (int8_t)round(53 / BITS_PER_DIGIT); 
    // printf("%.*E", digits, *x); //digits=16
    printf("%.16E", *x);
  } else {
    int8_t digits = (int8_t)round( ((53 - exponent) / BITS_PER_DIGIT));
    printf("%.*f", digits, *x);
  }
  // } else printf("%.*f", 17 - exponent, *x);
}

// float32_t for (2^0)+(2^−23)=1.00000000000000000000001
// 00000000000000000000001
void print_f32p(float32_t *x) {
// float32_t = 33 bits = 1 Sign bit, 8 Exponent bits, 24 mantissa bits
  int32_t exponent;
  frexp(*x, &exponent);
  if ((exponent >= 23) || ((*x > -0.0001) && (*x < 0.0001))){
    printf("%.6E", (float) *x);
  } else {
    int8_t digits = (int8_t)round( ((23 - exponent) / BITS_PER_DIGIT));
    printf("%.*f", digits, *x);
  }
}

void print_f64(float64_t x) { print_f64p(&x); }

void print_f32(float32_t x) { print_f32p(&x); }
#else

// Define a macro to print the value at the given address
#define PRINT_VALUE_AT_ADDRESS(type, format) \
    void print_##type##_p(type *x) { \
        printf("Value at address %p: " format "\n", (void *)x, *x); \
    }

// Use the macro to define the functions for float64_t and float32_t
PRINT_VALUE_AT_ADDRESS(float64_t, "%lf")
PRINT_VALUE_AT_ADDRESS(float32_t, "%f")

#define print_f64p(var)
    print_f32p(&floatValue);

#endif  // _GNUC_

// 3141592653589793
// 123456789ABCDEF
//      X       X
// printf() a var where NN is number of bits
// %"PRIiNN"   %"PRIuNN"   %"PRIXNN"
// signed      unsigned    hexadecimal       
// While you can use the PRIXNN to print HEX representation of the
// float to guarantee a random float will print and show every digit
// in the mantissa the following functions are provided may have to
// do a reference then a typecast to get it to work with floats
// printf("The hex value of \"somefloat64\" is %"PRIX64" \n ", *(uint64_t*)&somefloat64);

// bfloat16 developed by Google Brain = float32_t truncated to 16 bits
// 1 Sign bit, 8 Exponent bits, 7 mantissa bits
// print_f32 can print bfloat16 if it is followed
// by 16 zero bits and typecasted

// void print_bfloat16p(float32_t *x) {
//   int exponent;
//   frexp(*x, &exponent);//-10=-3log(10, 2)=-9.965 784 285
//   if ((exponent >= 6) || (exponent < -10)) printf("%.6E", (float) *x);
//   else printf("%.*f", 6 - exponent, (float) *x);
// }
// 
// void print_bfloat16(float32_t x) { print_f32p(&x); }

// might be faster than actual printf -> ryanjuckett.com/printing-floating-point-numbers/
// https://misc.ryanjuckett.com/downloads/RyanJuckett_Resume.pdf

// % No argument is converted, results in a "%" character in the result.
// %[flags][width][.precision]type
// G Same as "E" if exponent is greater than -4 or less than precision, "F" otherwise.
// E Floating point exponential format (uppercase).
// F Floating point decimal format (uppercase).
// g, e, or f can provide lowercase versions of the above

// printf("%0k.yf" float_variable_name)
// Here k is the total number of characters you want to get printed. 
// k = x + 1 + y (+ 1 for the dot) and float_variable_name is the 
// float variable that you want to get printed.
// Suppose you want to print x digits before the decimal point and y 
// digits after it. Now, if the number of digits before 
// float_variable_name is less than x, then it will automatically 
// prepend that many zeroes before it. // float32_t float64_t;

/* */

/*
// #!/run/current-system/sw/bin/tcc -run
#include "float_t.h" // 8-bits  16-bits  32-bits   64-bits
// includes stdint.h // uint8_t uint16_t uint32_t  uint64_t
// math.h inttypes.h // int8_t  int16_t  int32_t   int64_t
// stdio.h and gives // XXXXXX  XXXXXXX  float32_t float64_t
// functions print_f64(x) print_f64p(&x) print_f32(x) print_f32p(&x)
#include <stdlib.h> // for malloc()

int main(){
    float64_t pi64 = 3.141592653589793238;
    printf("actual value of pi is 3.1415926535897932384626433832795028841971...\n" );
    printf("\"(float64_t) pi64\" is ");
    print_f64p(&pi64);
    printf("\n");
    return(0);
}
*/

#endif

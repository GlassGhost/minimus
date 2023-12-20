// #!/run/current-system/sw/bin/tcc -run
 /*
;* ^^^^^^^^^ comment the above lines for the scheme version ^^^^^^^^^^
;*//* _________________________________________________________LICENSE
;*    Copyright (c) 2023 Roy Pfund
;*
;* Licensed under the Apache License, Version 2.0 (the  "License");
;* you may not use this file except in compliance with the License.
;* You may obtain a copy of the License at
;*
;*     http://www.apache.org/licenses/LICENSE-2.0
;*
;* Unless required by applicable  law  or  agreed  to  in  writing,
;* software distributed under the License is distributed on an  "AS
;* IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,  either
;* express or implied. See the License for  the  specific  language
;* governing permissions and limitations under the License.
;*//* ______________________________________________Standard libraries
;* for zalloc() assert.h stdlib.h stdarg.h err.h*/ #include "zalloc.h" 
/* 8-bits  16-bits  32-bits   64-bits */ #include "float_t.h" /*
;* int8_t uint16_t uint32_t  uint64_t  // includes stdint.h
;* int8_t  int16_t  int32_t   int64_t  // math.h inttypes.h
;* XXXXXX  XXXXXX  float32_t float64_t // stdio.h and gives
;* functions print_f64(x) print_f64p(&x) print_f32(x) print_f32p(&x)
;*//* ________________________________________________________________
build, run, and destroy with:
gcc -m64 -O2 -std=gnu99 test.c -o test && ./test && rm ./test
gcc -m64 -O2 -std=gnu99 COAtest.c -o COAtest && ./COAtest && rm ./COAtest

implements a circular deque with pushStart, popStart, pushEnd, and 
popEnd operations. The deque is circularly arranged in the array data, 
and the offsets are adjusted accordingly.
;*//* ____________________________________________________#includes */


// #include "COA.h"
// DEFINE_COA(float64_t, 256)
// // #undef DEFINE_DECK


/* ___________________________________________makeheaders INTERFACE */
// makeheaders requires INTERFACE directive wrapped around Pre-Defined 
// Constants & Data Structures accessible in other scopes.
// Declarations provide the interface and the definitions are the
// implementation.
// #include "test.h" // ./makeheaders -local ./test.c
#if INTERFACE
/* ___________________________________________Pre-Defined Constants */

/* _________________________________________________Data Structures */

#endif // EXPORT_INTERFACE
/* ________________________________________Function Implementations */

// float64_t pop_average( COA_float64_t* cluster ) {
//     // LLNode* temp = start;
//     float64_t sum = 0.0;
//     float64_t num = cluster->size;
//     float64_t* f64bufptr = zalloc(sizeof(float64_t));
//     while(cluster->size > 0){
//         COA_popStart_float64_t(f64bufptr, cluster);
//         sum += *f64bufptr;
//     }
//     return sum/num;
// }

// void COA_popStart_##type(type *xref, COA_##type* cluster);             \
// void COA_pushStart_##type(type *xref, COA_##type* cluster);            \
// void COA_popEnd_##type(type *xref, COA_##type* cluster);               \
// void COA_pushEnd_##type(type *xref, COA_##type* cluster);              \

/* __________________________________________Helper Implementations */
// static functions are unavailable outside the file they are defined.
static void test(int argc, char **argv){
    float64_t* f64bufptr = zalloc(sizeof(float64_t));
    * f64bufptr = 9999.2;

    // // Save and restore some data
    // COA_float64_t* cluster = New_COA_float64_t();
    // COA_pushStart_float64_t(f64bufptr, cluster);
    // * f64bufptr = 0.2;
    // COA_popStart_float64_t(f64bufptr, cluster);

    print_f64(*f64bufptr);
//     // printf("size of cluster is %"PRIu64" \n ", cluster->size);
//     * f64bufptr = 2.0;
//     pushDeckStart_float64_t(f64bufptr, cluster);
//     * f64bufptr = 3.0;
//     pushDeckStart_float64_t(f64bufptr, cluster);
//     * f64bufptr = 4.0;
//     pushDeckStart_float64_t(f64bufptr, cluster);
//     * f64bufptr = 5.0;
//     pushDeckStart_float64_t(f64bufptr, cluster);
// 
//     printf("\nsize of cluster is %"PRIu64" \n ", cluster->size);
// 
//     printf("Average of 2, 3, 4, 5 = ");
//     print_f64(average(cluster));
//     printf("\n");
//     printf("size of cluster is %"PRIu64" \n ", cluster->size);
//     
//     printf("Average of 2, 3, 4, 5 = ");
//     print_f64(pop_average(cluster));
//     printf("\n");
//     printf("size of cluster is %"PRIu64" \n ", cluster->size);
}
/* _____________________________________________________RUN PROGRAM */

int64_t main(int argc, char **argv){// *argv++ is *((char **)(argv++))
    // https://stackoverflow.com/a/72203145/144020
    // argv++; while (*argv) printf("%s ", *argv++); argv = argv - argc;
    test( argc, argv);
    return 0;
}

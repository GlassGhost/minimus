#!/run/current-system/sw/bin/tcc -run

// Copyright (C) 2023-2026 Roy Pfund. All rights reserved.
//
// Permission is  hereby  granted,  free  of  charge,  to  any  person
// obtaining a copy of  this  software  and  associated  documentation
// files  (the  "Software"),  to  deal   in   the   Software   without
// restriction, including without limitation the rights to use,  copy,
// modify, merge, publish, distribute, sublicense, and/or sell  copies
// of the Software, and to permit persons  to  whom  the  Software  is
// furnished to do so.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY  OF  ANY  KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES  OF
// MERCHANTABILITY,   FITNESS   FOR   A   PARTICULAR    PURPOSE    AND
// NONINFRINGEMENT.  IN  NO  EVENT  SHALL  THE  AUTHORS  OR  COPYRIGHT
// OWNER(S) BE LIABLE FOR  ANY  CLAIM,  DAMAGES  OR  OTHER  LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
// OUT OF OR IN CONNECTION WITH THE  SOFTWARE  OR  THE  USE  OR  OTHER
// DEALINGS IN THE SOFTWARE.
//
// Omitting the MIT‑style inclusion clause effectively places this
// file in the public domain.
//
// Annex B (informative)_Library_summary____________________ [p419N1256]
// assert inttypes signal  stdlib complex iso646 stdarg string
// ctype  limits   stdbool tgmath errno   locale stddef time
// fenv   math     stdint  wchar  float   setjmp stdio  wctype
#include "annexb.h" // ^^ includes the above .h files ^^     [p419N1256]
// ___________________________printf() directives provided by inttypes.h
// Hex      // %02"PRIX8" // %04"PRIX16" // %08"PRIX32" // %016"PRIX64"
// Signed   // %"PRIi8"   // %"PRIi16"   // %"PRIi32"   // %"PRIi64"
// Unsigned // %"PRIu8"   // %"PRIu16"   // %"PRIu32"   // %"PRIu64"
// Float    //  XXXXXX    //   XXXXXX    //   %.6E      // %.15E
//
/*////////////////////////////////////////////////////////////////////
gcc -m64 -O2 -std=gnu99 7macroTest.c -o 7macroTest && ./7macroTest && rm ./7macroTest

build, run, and destroy with the above; or just uncomment the tcc shebang.
//////////////////////////////////////////////////////////////////////

This C program demonstrates 7 macro-level generation techniques.

*/////////////////////////////////////////////////////////////////////

// 1. X-Macros (List Macros)

#define FRUIT_LIST \
    X(APPLE)       \
    X(ORANGE)      \
    X(BANANA)

#define X(name) name,
typedef enum { FRUIT_LIST FRUIT_COUNT } Fruit;
#undef X

#define X(name) #name,
static const char* fruit_names[] = { FRUIT_LIST };
#undef X

void test_x_macros() {
    printf("--- 1. X-Macros ---\n");
    for (int i = 0; i < FRUIT_COUNT; i++) {
        printf("Fruit enum index %d is: %s\n", i, fruit_names[i]);
    }
    printf("\n");
}

/////////////////////////////////////////////
// 2. Parameterized Function Generators

#define GEN_SWAP(T)         \
void swap_##T(T* a, T* b) { \
    T tmp = *a;             \
    *a = *b;                \
    *b = tmp;               \
}

GEN_SWAP(int)
GEN_SWAP(double)

void test_swap_gen() {
    printf("--- 2. Function Generators ---\n");
    int x = 10, y = 20;
    swap_int(&x, &y);
    printf("Swapped ints: x=%d, y=%d\n", x, y);

    double da = 1.23, db = 4.56;
    swap_double(&da, &db);
    printf("Swapped doubles: da=%.2f, db=%.2f\n\n", da, db);
}

/////////////////////////////////////////////
// 3. Macro-Generated Structs/Containers

#define DEFINE_VECTOR(T) \
typedef struct {         \
    T* data;             \
    size_t size;         \
    size_t capacity;     \
} vector_##T;

DEFINE_VECTOR(int)

void test_vector_gen() {
    printf("--- 3. Struct Generators ---\n");
    vector_int my_vec = { .data = NULL, .size = 0, .capacity = 10 };
    printf("Generated a vector_int struct with capacity: %zu\n\n", my_vec.capacity);
}

/////////////////////////////////////////////
// 5. Token-Pasting Macros (##)

#define MAKE_FUNC(T) \
void func_##T(T x) { \
    printf("Token-pasted function called with value: %f\n", (double)x); \
}

MAKE_FUNC(float)

void test_token_pasting() {
    printf("--- 5. Token-Pasting ---\n");
    func_float(3.14f);
    printf("\n");
}

/////////////////////////////////////////////
// 6. Stringizing Macros (#)

#define PRINT_VAR(x) printf("The variable name is '" #x "' and its value is %d\n", x)

void test_stringizing() {
    printf("--- 6. Stringizing ---\n");
    int my_lucky_number = 7;
    PRINT_VAR(my_lucky_number);
    printf("\n");
}

/////////////////////////////////////////////
// 7. Macro-Generated Inline Functions

#define GEN_MAX(T) \
static inline T max_##T(T a, T b) { return a > b ? a : b; }

GEN_MAX(int)
GEN_MAX(float)

void test_inline_gen() {
    printf("--- 7. Inline Function Generators ---\n");
    printf("Max of 10 and 20 (int): %d\n", max_int(10, 20));
    printf("Max of 5.5 and 2.2 (float): %.1f\n\n", max_float(5.5f, 2.2f));
}

/////////////////////////////////////////////
// 8. Opaque Pointer "Generic Types"

typedef void* any;

void print_as_int(any data) {
    printf("Opaque pointer interpreted as int: %d\n", *(int*)data);
}

void test_opaque_pointer() {
    printf("--- 8. Opaque Pointers ---\n");
    int val = 42;
    any generic_ptr = &val;
    print_as_int(generic_ptr);
    printf("\n");
}

/////////////////////////////////////////////
// Main Execution

int main() {
    printf("=== C Macro Meta-Programming Tests ===\n\n");
    
    test_x_macros();
    test_swap_gen();
    test_vector_gen();
    test_token_pasting();
    test_stringizing();
    test_inline_gen();
    test_opaque_pointer();

    return 0;
}

/*
$ ./7macroTest.c 
=== C Macro Meta-Programming Tests ===

--- 1. X-Macros ---
Fruit enum index 0 is: APPLE
Fruit enum index 1 is: ORANGE
Fruit enum index 2 is: BANANA

--- 2. Function Generators ---
Swapped ints: x=20, y=10
Swapped doubles: da=4.56, db=1.23

--- 3. Struct Generators ---
Generated a vector_int struct with capacity: 10

--- 5. Token-Pasting ---
Token-pasted function called with value: 3.140000

--- 6. Stringizing ---
The variable name is 'my_lucky_number' and its value is 7

--- 7. Inline Function Generators ---
Max of 10 and 20 (int): 20
Max of 5.5 and 2.2 (float): 5.5

--- 8. Opaque Pointers ---
Opaque pointer interpreted as int: 42
*/

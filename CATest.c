#!/run/current-system/sw/bin/tcc -run

// Copyright (C) 2023-2025 Roy Pfund. All rights reserved.
//
// Permission is  hereby  granted,  free  of  charge,  to  any  person
// obtaining a copy of  this  software  and  associated  documentation
// files  (the  "Software"),  to  deal   in   the   Software   without
// restriction, including without limitation the rights to use,  copy,
// modify, merge, publish, distribute, sublicense, and/or sell  copies
// of the Software, and to permit persons  to  whom  the  Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and  this  permission  notice  shall  be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY  OF  ANY  KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES  OF
// MERCHANTABILITY,   FITNESS   FOR   A   PARTICULAR    PURPOSE    AND
// NONINFRINGEMENT.  IN  NO  EVENT  SHALL  THE  AUTHORS  OR  COPYRIGHT
// OWNER(S) BE LIABLE FOR  ANY  CLAIM,  DAMAGES  OR  OTHER  LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
// OUT OF OR IN CONNECTION WITH THE  SOFTWARE  OR  THE  USE  OR  OTHER
// DEALINGS IN THE SOFTWARE.

/* build, run, and destroy with:
gcc -m64 -O2 -std=gnu99 CATest.c -o CATest && ./CATest && rm ./CATest

or just uncomment the tcc shebang
*/

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

/*

## Passing a pointer

```c
void foo(MyStruct *p) {
    p = NULL;   // Only changes the local copy
}
```

Because `p` itself is passed **by value**, so assigning `p = NULL` only overwrites the local copy.
This **CANNOT** affect the caller’s pointer. The caller still has the original pointer value, unchanged.
You *can* modify the struct’s contents (`p->field = ...`), but you cannot change the caller’s pointer.

---

## Passing a pointer to a pointer (`MyStruct **p`)
Now the function receives a pointer to the caller’s pointer.

```c
void foo(MyStruct **p) {
    *p = NULL;   // This modifies the caller's pointer
}
```

This **CAN** change the caller’s pointer, because you are dereferencing and writing to the original pointer.

> *We cannot set the pointer to NULL in the first version.*

*/

// #define MALLOC_FAIL 1

typedef enum { SUCCESS = 0, FULL = 1, EMPTY = 2, MALLOC_FAIL = 3 } fail_status_t;

#define DEFINE_CIRCARRAY_MEM(type, CA_size, CAPACITY)                              \
inline void FREE_CA_##type##_##CA_size ( CA_##type##_##CA_size **dq_p ){           \
    free(*dq_p); *dq_p = NULL;                                                     \
}                                                                                  \
inline bool ALLOC_CA_##type##_##CA_size ( CA_##type##_##CA_size **dq_p ){          \
    *dq_p = calloc(1, sizeof(CA_##type##_##CA_size));                              \
    if (!(*dq_p)) return MALLOC_FAIL; else return false;                           \
}

#define DEFINE_CIRCARRAY(type, CA_size)              \
DEFINE_CIRCARRAY_STRUCTS(type, CA_size, (CA_size+1)) \
DEFINE_CIRCARRAY_MEM(type, CA_size, (CA_size+1))     \
DEFINE_CIRCARRAY_FUNCS(type, CA_size, (CA_size+1))

#define DEFINE_CIRCARRAY_STRUCTS(type, CA_size, CAPACITY)                            \
                                                                                     \
/* _________________________________________________Data Structures */               \
typedef struct { /* % modulo CAPACITY gives 0 to CA_size = (CAPACITY-1) */           \
    uint8_t size; /* 0..255 means 1 to 256 elements, NULL for 0 elements */          \
    uint8_t start_offset; /* only start-ops modify start_offset 0 to 255 */          \
    type data[CAPACITY];                                                             \
} CA_##type##_##CA_size;                                                             \

#define DEFINE_CIRCARRAY_FUNCS(type, CA_size, CAPACITY)                              \
                                                                                     \
/* ___________________________________________Function Declarations */               \
fail_status_t pushStart_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **dq_p); \
fail_status_t pushEnd_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **dq_p);   \
fail_status_t popStart_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **dq_p);    \
fail_status_t popEnd_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **dq_p);      \
                                                                                     \
/* ___________________________________________Function Implementation */             \
fail_status_t pushStart_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **dq_p) { \
    if (*dq_p == NULL) { /* push 1st = 0th elem */                                   \
        if (ALLOC_CA_##type##_##CA_size (dq_p)) return FULL; /* alloc fail */        \
        (*dq_p)->data[0] = *source;                                                  \
        return SUCCESS;                                                              \
    }                                                                                \
    if ((*dq_p)->size == CA_size) return FULL; /* array full */                      \
    (*dq_p)->start_offset = ((*dq_p)->start_offset + CAPACITY - 1) % CAPACITY;       \
    (*dq_p)->data[(*dq_p)->start_offset] = *source;                                  \
    (*dq_p)->size++;                                                                 \
    return SUCCESS;                                                                  \
}                                                                                    \
                                                                                     \
fail_status_t pushEnd_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **dq_p) { \
    if (*dq_p == NULL) { /* push 1st = 0th elem */                                   \
        if (ALLOC_CA_##type##_##CA_size (dq_p)) return FULL; /* alloc fail */        \
        (*dq_p)->data[0] = *source;                                                  \
        return SUCCESS;                                                              \
    }                                                                                \
    if ((*dq_p)->size == CA_size) return FULL; /* array full */                      \
    uint8_t end_index = ((*dq_p)->start_offset + (*dq_p)->size + 1) % CAPACITY;      \
    (*dq_p)->data[end_index] = *source;                                              \
    (*dq_p)->size++;                                                                 \
    return SUCCESS;                                                                  \
}                                                                                    \
                                                                                     \
fail_status_t popStart_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **dq_p) { \
    if (*dq_p == NULL) return EMPTY; /* fail on empty */                             \
    *dest = (*dq_p)->data[(*dq_p)->start_offset];                                    \
    (*dq_p)->start_offset = ((*dq_p)->start_offset + 1) % CAPACITY;                  \
    if (!((*dq_p)->size == 0)) (*dq_p)->size--;                                      \
    else FREE_CA_##type##_##CA_size (dq_p); /* pop last elem */                      \
    return SUCCESS;                                                                  \
}                                                                                    \
                                                                                     \
fail_status_t popEnd_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **dq_p) { \
    if (*dq_p == NULL) return EMPTY; /* fail on empty */                             \
    uint8_t end_index = ((*dq_p)->start_offset + (*dq_p)->size) % CAPACITY;          \
    *dest = (*dq_p)->data[end_index];                                                \
    if (!((*dq_p)->size == 0)) (*dq_p)->size--;                                      \
    else FREE_CA_##type##_##CA_size (dq_p); /* pop last elem */                      \
    return SUCCESS;                                                                  \
}                                                                                    \

DEFINE_CIRCARRAY(int, 255);

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
/* Push X values using pushEnd_CA_int */

static void printDequeState(const char *label, CA_int_255 *dq) {
    printf("%s: size=%"PRIu8" start=%"PRIu8"\n",
           label,
           dq ? dq->size : 0,
           dq ? dq->start_offset : 0);
}

/* Push N values using pushEnd */
static void testPushEnd(CA_int_255 **dq, int count) {
    printf("\n[testPushEnd] pushing %d values...\n", count);
    for (int i = 0; i < count; i++) {
        int x = i + 1;
        fail_status_t r = pushEnd_CA_int_255(&x, dq);
        if (r != SUCCESS) {
            printf(" pushEnd failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After pushEnd", *dq);
}

/* Push N values using pushStart */
static void testPushStart(CA_int_255 **dq, int count) {
    printf("\n[testPushStart] pushing %d values...\n", count);
    for (int i = 0; i < count; i++) {
        int x = i + 1;
        fail_status_t r = pushStart_CA_int_255(&x, dq);
        if (r != SUCCESS) {
            printf(" pushStart failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After pushStart", *dq);
}

/* Pop N values using popEnd */
static void testPopEnd(CA_int_255 **dq, int count) {
    printf("\n[testPopEnd] popping %d values...\n", count);
    for (int i = 0; i < count; i++) {
        int x;
        fail_status_t r = popEnd_CA_int_255(&x, dq);
        if (r != SUCCESS) {
            printf(" popEnd failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After popEnd", *dq);
}

/* Pop N values using popStart */
static void testPopStart(CA_int_255 **dq, int count) {
    printf("\n[testPopStart] popping %d values...\n", count);
    for (int i = 0; i < count; i++) {
        int x;
        fail_status_t r = popStart_CA_int_255(&x, dq);
        if (r != SUCCESS) {
            printf(" popStart failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After popStart", *dq);
}

static void test2(CA_int_255 **dq) {
    printf("\n===== TEST 2: FAIL INTENTIONALLY =====\n");

    // A: push until full, then push one more
    printf("\n[Test 2A] pushEnd until full, then extra\n");
    for (int i = 0; i < 255; i++) {
        int x = i;
        pushEnd_CA_int_255(&x, dq);
    }
    int x = 999;
    printf(" pushEnd beyond full -> %d\n",
           pushEnd_CA_int_255(&x, dq));

    // // B: pop from empty
    // printf("\n[Test 2B] popStart on empty deque\n");
    // FREE_CA_int_255_255(dq); // ensure empty
    // printf(" popStart empty -> %d\n",
    //        popStart_CA_int_255(&x, dq));

    // // C: simulate malloc failure
    // printf("\n[Test 2C] simulated malloc failure\n");
    // #define MALLOC_FAIL 1
    // printf(" pushEnd malloc fail -> %d\n",
    //        pushEnd_CA_int_255(&x, dq));
    // #undef MALLOC_FAIL

    // D: pop more than size
    printf("\n[Test 2D] popStart more than size\n");
    testPushEnd(dq, 10);
    testPopStart(dq, 15);

    // E: recovery
    printf("\n[Test 2E] recovery after failures\n");
    x = 42;
    pushEnd_CA_int_255(&x, dq);
    printDequeState("After recovery push", *dq);

}

/* __________________________________________Helper Implementations */
// static functions are unavailable outside the file they are defined.

static void test(int argc, char **argv) {
    CA_int_255 *dq = NULL;
    int x;

    printf("\n===== TEST 1a: pushEnd 200, popStart 199 =====\n");
    testPushEnd(&dq, 200);
    testPopStart(&dq, 199);
    printf("Current Deque pointer: %016"PRIX64"\n", dq);

    printf("\n===== TEST 1b: pushEnd 200, popStart 200 =====\n");
    testPushEnd(&dq, 200);
    testPopStart(&dq, 200);
    testPushEnd(&dq, 255);
    testPopStart(&dq, 255);
    testPopStart(&dq, 1);
    printf("Deque pointer after emptying: %p\n", (void*)dq);
    printf("Current Deque pointer: %016"PRIX64"\n", dq);

    printf("\n===== TEST 1c: pushStart 200, popEnd 200 =====\n");
    testPushStart(&dq, 200);
    testPopEnd(&dq, 199);
    testPushStart(&dq, 200);
    testPopEnd(&dq, 200);
    testPushStart(&dq, 255);
    testPopEnd(&dq, 255);
    testPopEnd(&dq, 1);

    printf("Deque pointer after emptying: %p\n", (void*)dq);

    test2(&dq);

    printf("\n===== ALL TESTS COMPLETE =====\n");
}

/* _____________________________________________________RUN PROGRAM */

int64_t main(int argc, char **argv){// *argv++ is *((char **)(argv++))
    // https://stackoverflow.com/a/72203145/144020
    // argv++; while (*argv) printf("%s ", *argv++); argv = argv - argc;
    test( argc, argv);
    return 0;
}

/* 
$ ./CATest.c 

===== TEST 1a: pushEnd 200, popStart 199 =====

[testPushEnd] pushing 200 values...
After pushEnd: size=199 start=0

[testPopStart] popping 199 values...
After popStart: size=0 start=199
Current Deque pointer: 000055965A415F40

===== TEST 1b: pushEnd 200, popStart 200 =====

[testPushEnd] pushing 200 values...
After pushEnd: size=200 start=199

[testPopStart] popping 200 values...
After popStart: size=0 start=143

[testPushEnd] pushing 255 values...
After pushEnd: size=255 start=143

[testPopStart] popping 255 values...
After popStart: size=0 start=142

[testPopStart] popping 1 values...
After popStart: size=0 start=0
Deque pointer after emptying: (nil)
Current Deque pointer: 0000000000000000

===== TEST 1c: pushStart 200, popEnd 200 =====

[testPushStart] pushing 200 values...
After pushStart: size=199 start=57

[testPopEnd] popping 199 values...
After popEnd: size=0 start=57

[testPushStart] pushing 200 values...
After pushStart: size=200 start=113

[testPopEnd] popping 200 values...
After popEnd: size=0 start=113

[testPushStart] pushing 255 values...
After pushStart: size=255 start=114

[testPopEnd] popping 255 values...
After popEnd: size=0 start=114

[testPopEnd] popping 1 values...
After popEnd: size=0 start=0
Deque pointer after emptying: (nil)

===== TEST 2: FAIL INTENTIONALLY =====

[Test 2A] pushEnd until full, then extra
 pushEnd beyond full -> 0

[Test 2D] popStart more than size

[testPushEnd] pushing 10 values...
 pushEnd failed at i=0 (status=1)

[testPopStart] popping 15 values...
After popStart: size=240 start=15

[Test 2E] recovery after failures
After recovery push: size=241 start=15

===== ALL TESTS COMPLETE =====

 */

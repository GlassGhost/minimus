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
gcc -m64 -O2 -std=gnu99 CATest.c -o CATest && ./CATest && rm ./CATest

build, run, and destroy with the above; or just uncomment the tcc shebang.
//////////////////////////////////////////////////////////////////////

Circular Array Test

*/////////////////////////////////////////////////////////////////////

#define type int
#define CA_size 63
#include "ca_type.h"

#define type int
#define CA_size 255
#include "ca_type.h"

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

/* ________________________________________Function Implementations */

/* Print state of deque (generic) */
static void printDequeState(const char *label, void *dq_void) {
    if (!dq_void) {
        printf("%s: size=0 start=0\n", label);
        return;
    }

    // All CA_* structs begin with uint8_t size, uint8_t start_offset
    uint8_t size  = *((uint8_t*)dq_void);
    uint8_t start = *(((uint8_t*)dq_void) + 1);

    printf("%s: size=%"PRIu8" start=%"PRIu8"\n", label, size, start);
}

/* __________________________________________Helper Implementations */

static void testPushEnd(CA_Interface *iface, int count) {
    printf("\n[testPushEnd %s] pushing %d values...\n",
           iface->label, count);

    for (int i = 0; i < count; i++) {
        int x = i + 1;
        fail_status_t r = iface->pushEnd(&x, iface->dq);
        if (r != SUCCESS) {
            printf(" pushEnd failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After pushEnd", *(iface->dq));
}

static void testPushStart(CA_Interface *iface, int count) {
    printf("\n[testPushStart %s] pushing %d values...\n",
           iface->label, count);

    for (int i = 0; i < count; i++) {
        int x = i + 1;
        fail_status_t r = iface->pushStart(&x, iface->dq);
        if (r != SUCCESS) {
            printf(" pushStart failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After pushStart", *(iface->dq));
}

static void testPopEnd(CA_Interface *iface, int count) {
    printf("\n[testPopEnd %s] popping %d values...\n",
           iface->label, count);

    for (int i = 0; i < count; i++) {
        int x;
        fail_status_t r = iface->popEnd(&x, iface->dq);
        if (r != SUCCESS) {
            printf(" popEnd failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After popEnd", *(iface->dq));
}

static void testPopStart(CA_Interface *iface, int count) {
    printf("\n[testPopStart %s] popping %d values...\n",
           iface->label, count);

    for (int i = 0; i < count; i++) {
        int x;
        fail_status_t r = iface->popStart(&x, iface->dq);
        if (r != SUCCESS) {
            printf(" popStart failed at i=%d (status=%d)\n", i, r);
            return;
        }
    }
    printDequeState("After popStart", *(iface->dq));
}



/* __________________________________________Helper Implementations */
// static functions are unavailable outside the file they are defined.

static void test255(int argc, char **argv) {
    printf("\n===== RUNNING TEST255 (CA_int_255) =====\n");

    /* Interface instance for CA_int_255 */
    static CA_int_255 *dq_ptr = NULL;
    CA_Interface iface = {
        .dq = (void**)&dq_ptr,
        .pushStart = (fail_status_t (*)(void*,void**))pushStart_CA_int_255,
        .pushEnd   = (fail_status_t (*)(void*,void**))pushEnd_CA_int_255,
        .popStart  = (fail_status_t (*)(void*,void**))popStart_CA_int_255,
        .popEnd    = (fail_status_t (*)(void*,void**))popEnd_CA_int_255,
        .label = "CA_int_255"
    };

    printf("\n===== TEST 1a: pushEnd 200, popStart 199 =====\n");
    testPushEnd(&iface, 200);
    testPopStart(&iface, 199);
    printf("Current Deque pointer: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);

    testPushEnd(&iface, 200);
    testPopStart(&iface, 200);
    printf("Current Deque pointer: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);

    testPushEnd(&iface, 255);
    testPopStart(&iface, 255);
    testPopStart(&iface, 1);
    printf("Deque pointer after emptying: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);

    printf("\n===== TEST 1c: pushStart 200, popEnd 200 =====\n");
    testPushStart(&iface, 200);
    testPopEnd(&iface, 199);
    testPushStart(&iface, 200);
    testPopEnd(&iface, 200);
    testPushStart(&iface, 255);
    testPopEnd(&iface, 255);
    testPopEnd(&iface, 1);

    printf("Current Deque pointer: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);

    /* Test 2 (intentional failures) */
    printf("\n===== TEST 2: FAIL INTENTIONALLY =====\n");

    printf("\n[Test 2A] pushEnd until full, then extra\n");
    for (int i = 0; i < 255; i++) {
        int x = i;
        iface.pushEnd(&x, iface.dq);
    }
    int x = 999;
    printf(" pushEnd beyond full -> %d\n", iface.pushEnd(&x, iface.dq));

    printf("\n[Test 2D] popStart more than size\n");
    testPushEnd(&iface, 10);
    testPopStart(&iface, 63);

    printf("\n[Test 2E] recovery after failures\n");
    x = 42;
    iface.pushEnd(&x, iface.dq);
    printDequeState("After recovery push", dq_ptr);

    printf("\n===== MINIMAL ORDERING TEST =====\n");

    CA_int_255 *dq2 = NULL;
    CA_Interface iface2 = {
        .dq = (void**)&dq2,
        .pushStart = (fail_status_t (*)(void*,void**))pushStart_CA_int_255,
        .pushEnd   = (fail_status_t (*)(void*,void**))pushEnd_CA_int_255,
        .popStart  = (fail_status_t (*)(void*,void**))popStart_CA_int_255,
        .popEnd    = (fail_status_t (*)(void*,void**))popEnd_CA_int_255,
        .label = "CA_int_255"
    };

    int a = 1, b = 2, out;
    iface2.pushEnd(&a, iface2.dq);
    iface2.pushEnd(&b, iface2.dq);

    printf("Correct behavior: popEnd should return 2 first, then 1\n");

    iface2.popEnd(&out, iface2.dq);
    printf("First popEnd returned: %d\n", out);

    iface2.popEnd(&out, iface2.dq);
    printf("Second popEnd returned: %d\n", out);

    printf("Deque pointer after minimal test: %p\n", (void*)dq2);

    printf("\n===== ALL TESTS COMPLETE (255) =====\n");
}

static void test63(int argc, char **argv) {
    printf("\n===== RUNNING TEST63 (CA_int_63) =====\n");
    /* Interface instance for CA_int_63 */
    static CA_int_63 *dq_ptr = NULL;
    CA_Interface iface = {
        .dq = (void**)&dq_ptr,
        .pushStart = (fail_status_t (*)(void*,void**))pushStart_CA_int_63,
        .pushEnd = (fail_status_t (*)(void*,void**))pushEnd_CA_int_63,
        .popStart = (fail_status_t (*)(void*,void**))popStart_CA_int_63,
        .popEnd = (fail_status_t (*)(void*,void**))popEnd_CA_int_63,
        .label = "CA_int_63"
    };
    printf("\n===== TEST 1a: pushEnd 50, popStart 49 =====\n");
    testPushEnd(&iface, 50);
    testPopStart(&iface, 49);
    printf("Current Deque pointer: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);
    testPushEnd(&iface, 50);
    testPopStart(&iface, 50);
    printf("Current Deque pointer: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);
    testPushEnd(&iface, 63);
    testPopStart(&iface, 63);
    testPopStart(&iface, 1);
    printf("Deque pointer after emptying: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);
    printf("\n===== TEST 1c: pushStart 50, popEnd 50 =====\n");
    testPushStart(&iface, 50);
    testPopEnd(&iface, 49);
    testPushStart(&iface, 50);
    testPopEnd(&iface, 50);
    testPushStart(&iface, 63);
    testPopEnd(&iface, 63);
    testPopEnd(&iface, 1);
    printf("Current Deque pointer: %016"PRIX64"\n", (uint64_t)(uintptr_t)dq_ptr);
    /* Test 2 (intentional failures) */
    printf("\n===== TEST 2: FAIL INTENTIONALLY =====\n");
    printf("\n[Test 2A] pushEnd until full, then extra\n");
    for (int i = 0; i < 63; i++) {
        int x = i;
        iface.pushEnd(&x, iface.dq);
    }
    int x = 999;
    printf(" pushEnd beyond full -> %d\n", iface.pushEnd(&x, iface.dq));
    printf("\n[Test 2D] popStart more than size\n");
    testPushEnd(&iface, 10);
    testPopStart(&iface, 16);
    printf("\n[Test 2E] recovery after failures\n");
    x = 42;
    iface.pushEnd(&x, iface.dq);
    printDequeState("After recovery push", dq_ptr);
    printf("\n===== MINIMAL ORDERING TEST =====\n");
    CA_int_63 *dq2 = NULL;
    CA_Interface iface2 = {
        .dq = (void**)&dq2,
        .pushStart = (fail_status_t (*)(void*,void**))pushStart_CA_int_63,
        .pushEnd = (fail_status_t (*)(void*,void**))pushEnd_CA_int_63,
        .popStart = (fail_status_t (*)(void*,void**))popStart_CA_int_63,
        .popEnd = (fail_status_t (*)(void*,void**))popEnd_CA_int_63,
        .label = "CA_int_63"
    };
    int a = 1, b = 2, out;
    iface2.pushEnd(&a, iface2.dq);
    iface2.pushEnd(&b, iface2.dq);
    printf("Correct behavior: popEnd should return 2 first, then 1\n");
    iface2.popEnd(&out, iface2.dq);
    printf("First popEnd returned: %d\n", out);
    iface2.popEnd(&out, iface2.dq);
    printf("Second popEnd returned: %d\n", out);
    printf("Deque pointer after minimal test: %p\n", (void*)dq2);
    printf("\n===== ALL TESTS COMPLETE (63) =====\n");
}

/* _____________________________________________________RUN PROGRAM */

int64_t main(int argc, char **argv){// *argv++ is *((char **)(argv++))
    // https://stackoverflow.com/a/72203145/144020
    // argv++; while (*argv) printf("%s ", *argv++); argv = argv - argc;
    test63( argc, argv);
    test255( argc, argv);
    return 0;
}

/* 
$ gcc -m64 -O2 -std=gnu99 CATest.c -o CATest && ./CATest && rm ./CATest

===== RUNNING TEST255 (CA_int_255) =====

===== TEST 1a: pushEnd 200, popStart 199 =====

[testPushEnd CA_int_255] pushing 200 values...
After pushEnd: size=199 start=0

[testPopStart CA_int_255] popping 199 values...
After popStart: size=0 start=199
Current Deque pointer: 000055D47884C6B0

[testPushEnd CA_int_255] pushing 200 values...
After pushEnd: size=200 start=199

[testPopStart CA_int_255] popping 200 values...
After popStart: size=0 start=143
Current Deque pointer: 000055D47884C6B0

[testPushEnd CA_int_255] pushing 255 values...
After pushEnd: size=255 start=143

[testPopStart CA_int_255] popping 255 values...
After popStart: size=0 start=142

[testPopStart CA_int_255] popping 1 values...
After popStart: size=0 start=0
Deque pointer after emptying: 0000000000000000

===== TEST 1c: pushStart 200, popEnd 200 =====

[testPushStart CA_int_255] pushing 200 values...
After pushStart: size=199 start=57

[testPopEnd CA_int_255] popping 199 values...
After popEnd: size=0 start=57

[testPushStart CA_int_255] pushing 200 values...
After pushStart: size=200 start=113

[testPopEnd CA_int_255] popping 200 values...
After popEnd: size=0 start=113

[testPushStart CA_int_255] pushing 255 values...
After pushStart: size=255 start=114

[testPopEnd CA_int_255] popping 255 values...
After popEnd: size=0 start=114

[testPopEnd CA_int_255] popping 1 values...
After popEnd: size=0 start=0
Current Deque pointer: 0000000000000000

===== TEST 2: FAIL INTENTIONALLY =====

[Test 2A] pushEnd until full, then extra
 pushEnd beyond full -> 0

[Test 2D] popStart more than size

[testPushEnd CA_int_255] pushing 10 values...
 pushEnd failed at i=0 (status=1)

[testPopStart CA_int_255] popping 63 values...
After popStart: size=192 start=63

[Test 2E] recovery after failures
After recovery push: size=193 start=63

===== MINIMAL ORDERING TEST =====
Correct behavior: popEnd should return 2 first, then 1
First popEnd returned: 2
Second popEnd returned: 1
Deque pointer after minimal test: (nil)

===== ALL TESTS COMPLETE (255) =====

 */

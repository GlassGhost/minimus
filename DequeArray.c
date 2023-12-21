#!/run/current-system/sw/bin/tcc -run
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
gcc -m64 -O2 -std=gnu99 DequeArray.c -o DequeArray && ./DequeArray && rm ./DequeArray

implements a circular deque with pushStart, popStart, pushEnd, and 
popEnd operations. The deque is circularly arranged in the array data, 
and the offsets are adjusted accordingly.
;*//* ____________________________________________________#includes */


/* ___________________________________________makeheaders INTERFACE */
// makeheaders requires INTERFACE directive wrapped around Pre-Defined 
// Constants & Data Structures accessible in other scopes.
// Declarations provide the interface and the definitions are the
// implementation.
// #include "DequeArray.h" // ./makeheaders -local ./DequeArray.c
#if INTERFACE
/* ___________________________________________Pre-Defined Constants */

#endif

#include "COA.h"
// DEFINE_CIRCARRAY(uint8_t, 45)
DEFINE_COA(uint8_t, 45)
// #undef DEFINE_DECK

/* __________________________________________Helper Implementations */
// static functions are unavailable outside the file they are defined.
/* _____________________________________________________RUN PROGRAM */
int64_t main(int argc, char **argv){// *argv++ is *((char **)(argv++))
    CA_uint8_t* deque = zalloc(sizeof( CA_uint8_t ));
    uint8_t* intbufptr = (uint8_t*)zalloc(sizeof(uint8_t));
    // Pushing values onto the deque
    *intbufptr = 42;
    pushStart_CA_uint8_t(intbufptr, deque);
    *intbufptr = 17;
    pushEnd_CA_uint8_t(intbufptr, deque);
    *intbufptr = 33;
    pushStart_CA_uint8_t(intbufptr, deque);

    // Popping values from the deque
    popStart_CA_uint8_t(intbufptr, deque);
    printf("Popped from start: %u\n", *intbufptr);
    popEnd_CA_uint8_t(intbufptr, deque);
    printf("Popped from end: %u\n", *intbufptr);
    popEnd_CA_uint8_t(intbufptr, deque);
    printf("Popped from end: %u\n", *intbufptr);
    Deck_CA_uint8_t* pile = zalloc(sizeof(Deck_CA_uint8_t));
    
    *intbufptr = sizeof(CA_uint8_t);
    printf("sizeof CA_uint8_t: %u\n", *intbufptr);
    *intbufptr = sizeof(LLNode_CA_uint8_t);
    printf("sizeof LLNode_CA_uint8_t: %u\n", *intbufptr);
    *intbufptr = sizeof(Deck_CA_uint8_t);
    printf("sizeof Deck_CA_uint8_t: %u\n", *intbufptr);

    return 0;
}

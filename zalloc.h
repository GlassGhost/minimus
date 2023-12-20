
#ifndef ZALLOC_HEADER_FILE_H
#define ZALLOC_HEADER_FILE_H

/*
;*//* _______________________________________________________________
;*
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
;*
;*//* _______________________________________________________________
;*/

#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif  // ASSERT_H

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif  // STDLIB_H

#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h>
#endif  // STDARG_H

#ifndef ERR_H
#define ERR_H
#include <err.h>
#endif  // ERR_H

/*
;*//* _______________________________________________________________
*/

// void *malloc(size_t size); // reserves a block of storage of size bytes.

// void *calloc(size_t num, size_t size); 
// reserves storage space for an array of num elements, each of length size bytes.

// void *zalloc(size_t size); // reserves a block of storage of size bytes, guaranteed to be zero.

inline void* zalloc(size_t size) { // class 3 of the list below
    void *new = calloc(1, size);
    assert(new != NULL); // malloc failed
    return new;
}

// inline malloc zero assert not null return
// imzannr_GENERATE_STATIC(type)
// /* New_##type() defined by imzannr */ 
// some_type_ptr = New_##type();
#define imzannr_GENERATE(type)                                         \
    imzannr_GENERATE_INTERNAL(type,)
#define imzannr_GENERATE_STATIC(type)                                  \
    imzannr_GENERATE_INTERNAL(type, __attribute__((__unused__)) static)
#define imzannr_GENERATE_INTERNAL(type, attr)                          \
inline attr ##type* New_##type () {                                    \
    ##type * New_Ptr = ( ##type * )zalloc(sizeof( ##type ));           \
    return New_Ptr;                                                    \
}

    // assert(New_Ptr != NULL);                    \

/*
;*//* _______________________________________________________________
*/

// https://stackoverflow.com/a/34486954
// 
// Classify the potential errors into groups:
// 
// 1) Run-time errors that must be handled.
// assert() is no good here, instead code must handle the error.
// 
// 2) Run-time errors that should be handled yet have no defined remedy.
// 
// assert() is not wise here either. Code should signal (leave error 
// message) and exit.
// 
// 3) Run-time errors with no simply re-course to handle them.
// 
// assert() could be used here. Now when the program faults/dies/hangs we 
// are left with nothing. Recommend code should signal like in #2 if at 
// all possible.
// 
// 4) Compile time errors.
// 
// assert(sizeof(int)*CHAR_BIT >= 32) is a good example usage. It is 
// reasonable to assume that a build will occur in debug mode. Even this 
// carries a risk with deployed source code that a user in the field may 
// skip the debug build, so suggest only use assert() for internal code.
// 
// assert() is a tool in the C toolbox. It has its uses - and mis-uses.
// 
// With malloc(), I have worked on many projects that barred direct use 
// of C lib malloc() and instead used a project specific code like 
// my_malloc_never_fail() and my_malloc_may_fail() which had error 
// handling and metrics. As @Weather Vane commented, good error handle is 
// challenging.

#endif // ZALLOC_HEADER_FILE_H

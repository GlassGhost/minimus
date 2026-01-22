
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
/*////////////////////////////////////////////////////////////////////

//  Circular Array (ring buffer) macro

// usage of Generator for "type" and "CA_size" of ring buffer arrays
// set input vars then include it undefs inputs so it can be reused

#define type int
#define CA_size 255
#include "ca_type.h"

arrays are of nonzero size so 0=1 1=2 . . . 255=256 or they are deleted an ptr is NULL

*/////////////////////////////////////////////////////////////////////

//  Expansion Indirection: These force 'type' and 'CA_size' to expand

#define XCAT2(a,b) a##b
#define CAT2(a,b) XCAT2(a,b)

#define XCAT3(a,b,c) a##b##c
#define CAT3(a,b,c) XCAT3(a,b,c)

#define XCAT4(a,b,c,d) a##b##c##d
#define CAT4(a,b,c,d) XCAT4(a,b,c,d)

// Helper to build the specific type name: CA_type_size
#define CA_NAME(t, s) CAT3(CA_, t, CAT2(_, s))

//////////////////////////////////////////////////////////////////////

#ifndef FAIL_STATUS_T_DEFINED
#define FAIL_STATUS_T_DEFINED
typedef enum { SUCCESS = 0, FULL = 1, EMPTY = 2, MALLOC_FAIL = 3 } fail_status_t;
#endif

#ifndef CA_INTERFACE_DEFINED
#define CA_INTERFACE_DEFINED

typedef struct {
    void **dq;   // pointer to the deque pointer (CA_int_255**, CA_int_63**, etc.)

    fail_status_t (*pushStart)(void *src, void **dq);
    fail_status_t (*pushEnd)(void *src, void **dq);
    fail_status_t (*popStart)(void *dst, void **dq);
    fail_status_t (*popEnd)(void *dst, void **dq);

    const char *label; // for debugging
} CA_Interface;
#endif

//////////////////////////////////////////////////////////////////////
#ifndef DEFINE_CIRCARRAY_MEM_DEFINED
#define DEFINE_CIRCARRAY_MEM_DEFINED
//  MEMORY / ALLOC HELPERS


#define DEFINE_CIRCARRAY_MEM(type, CA_size)                                          \
static inline bool CAT2(is_empty_, CA_NAME(type, CA_size))(                          \
        const CA_NAME(type, CA_size) **dq_p) {                                       \
    return (*dq_p == NULL);                                                          \
}                                                                                    \
                                                                                     \
static inline bool CAT2(is_full_, CA_NAME(type, CA_size))(                           \
        const CA_NAME(type, CA_size) **dq_p) {                                       \
    return ((*dq_p)->size == CA_size);                                               \
}                                                                                    \
                                                                                     \
static inline void CAT2(FREE_, CA_NAME(type, CA_size))(                              \
        CA_NAME(type, CA_size) **dq_p) {                                             \
    free(*dq_p);                                                                     \
    *dq_p = NULL;                                                                    \
}                                                                                    \
                                                                                     \
static inline bool CAT2(ALLOC_, CA_NAME(type, CA_size))(                             \
        CA_NAME(type, CA_size) **dq_p) {                                             \
    *dq_p = calloc(1, sizeof(CA_NAME(type, CA_size)));                               \
    return (*dq_p == NULL);                                                          \
}

#endif // DEFINE_CIRCARRAY_MEM_DEFINED

//////////////////////////////////////////////////////////////////////
#ifndef DEFINE_CIRCARRAY_STRUCT_DEFINED
#define DEFINE_CIRCARRAY_STRUCT_DEFINED
//  STRUCT GENERATION

#define DEFINE_CIRCARRAY_STRUCT(type, CA_size, CAPACITY)  \
typedef struct {                                          \
    uint8_t size;                                         \
    uint8_t start_offset;                                 \
    type    data[CAPACITY];                               \
} CA_NAME(type, CA_size);

#endif // DEFINE_CIRCARRAY_STRUCT_DEFINED

//////////////////////////////////////////////////////////////////////
#ifndef DEFINE_CIRCARRAY_FUNCS_DEFINED
#define DEFINE_CIRCARRAY_FUNCS_DEFINED
//  FUNCTION IMPLEMENTATIONS

#define DEFINE_CIRCARRAY_FUNCS(type, CA_size, CAPACITY)                                \
static inline fail_status_t CAT2(pushStart_, CA_NAME(type, CA_size))(type *src, CA_NAME(type, CA_size) **dq_p){ \
    if (*dq_p == NULL) {                                                               \
        if (CAT2(ALLOC_, CA_NAME(type, CA_size))(dq_p)) return MALLOC_FAIL;            \
        (*dq_p)->data[0] = *src;                                                       \
        return SUCCESS;                                                                \
    }                                                                                  \
    if (CAT2(is_full_, CA_NAME(type, CA_size))((const CA_NAME(type, CA_size)**)dq_p))  \
        return FULL;                                                                   \
    (*dq_p)->start_offset = ((*dq_p)->start_offset + CAPACITY - 1) % CAPACITY;         \
    (*dq_p)->data[(*dq_p)->start_offset] = *src;                                       \
    (*dq_p)->size++;                                                                   \
    return SUCCESS;                                                                    \
}                                                                                      \
                                                                                       \
static inline fail_status_t CAT2(pushEnd_, CA_NAME(type, CA_size))(type *src, CA_NAME(type, CA_size) **dq_p){  \
    if (*dq_p == NULL) {                                                               \
        if (CAT2(ALLOC_, CA_NAME(type, CA_size))(dq_p)) return MALLOC_FAIL;            \
        (*dq_p)->data[0] = *src;                                                       \
        return SUCCESS;                                                                \
    }                                                                                  \
    if (CAT2(is_full_, CA_NAME(type, CA_size))((const CA_NAME(type, CA_size)**)dq_p))  \
        return FULL;                                                                   \
    uint8_t end = ((*dq_p)->start_offset + (*dq_p)->size + 1) % CAPACITY;              \
    (*dq_p)->data[end] = *src;                                                         \
    (*dq_p)->size++;                                                                   \
    return SUCCESS;                                                                    \
}                                                                                      \
                                                                                       \
static inline fail_status_t CAT2(popStart_, CA_NAME(type, CA_size))(type *dst, CA_NAME(type, CA_size) **dq_p){ \
    if (*dq_p == NULL) return EMPTY;                                                   \
    *dst = (*dq_p)->data[(*dq_p)->start_offset];                                       \
    (*dq_p)->start_offset = ((*dq_p)->start_offset + 1) % CAPACITY;                    \
    if ((*dq_p)->size > 0) (*dq_p)->size--; else CAT2(FREE_, CA_NAME(type, CA_size))(dq_p); \
    return SUCCESS;                                                                    \
}                                                                                      \
                                                                                       \
static inline fail_status_t CAT2(popEnd_, CA_NAME(type, CA_size))(type *dst, CA_NAME(type, CA_size) **dq_p){   \
    if (*dq_p == NULL) return EMPTY;                                                   \
    uint8_t end = ((*dq_p)->start_offset + (*dq_p)->size) % CAPACITY;                  \
    *dst = (*dq_p)->data[end];                                                         \
    if ((*dq_p)->size > 0) (*dq_p)->size--; else CAT2(FREE_, CA_NAME(type, CA_size))(dq_p); \
    return SUCCESS;                                                                    \
}

#endif // DEFINE_CIRCARRAY_FUNCS_DEFINED

//////////////////////////////////////////////////////////////////////

// Run & Cleanup // allow redefining parts of macro
// struct is made before memory macro

DEFINE_CIRCARRAY_STRUCT(type, CA_size, (CA_size + 1))
#undef DEFINE_CIRCARRAY_STRUCT
#undef DEFINE_CIRCARRAY_STRUCT_DEFINED

DEFINE_CIRCARRAY_MEM(type, CA_size)
#undef DEFINE_CIRCARRAY_MEM
#undef DEFINE_CIRCARRAY_MEM_DEFINED

DEFINE_CIRCARRAY_FUNCS(type, CA_size, (CA_size + 1))
#undef DEFINE_CIRCARRAY_FUNCS
#undef DEFINE_CIRCARRAY_FUNCS_DEFINED

// Cleanup Args for subsequent includes
#undef type
#undef CA_size

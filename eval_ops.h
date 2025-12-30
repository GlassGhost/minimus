
// Copyright (C) 2023-2025 Roy Pfund. All rights reserved.
//
// Permission is  hereby  granted,  free  of  charge,  to  any  person
// obtaining a copy of  this  software  and  associated  documentation
// files  (the  "Software"),  to  deal   in   the   Software   without
// restriction, including without limitation the rights to use,  copy,
// modify, merge, publish, distribute, sublicense, and/or sell  copies
// of the Software, and to permit persons  to  whom  the  Software  is
// furnished to do so.
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

//////////////////////////////////////////////////////////////////////

#ifndef EVALUATIVE_OPS_FILE_H
#define EVALUATIVE_OPS_FILE_H

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
//#include "eval_ops.h" /*////////////////////////////////Evaluative Ops
typedef float float32_t;
typedef double float64_t;
//            // signed // unsigned  // float       // bits
typedef union {  int8_t S;  uint8_t U;               }  T8;
typedef union { T8 T8A[2];                           // arrays
                int16_t S; uint16_t U;               } T16;
typedef union { T8 T8A[4]; T16 T16A[2];              // arrays
                int32_t S; uint32_t U; float32_t F;  } T32;
typedef union { T8 T8A[8]; T16 T16A[4]; T32 T32A[2]; // arrays
                int64_t S; uint64_t U; float64_t F;  } T64;
#define TCAST(WidthN, Designator, DerefVal) \
    ((T##WidthN){ Designator = (DerefVal) })

typedef T8* T8P; typedef T16* T16P; typedef T32* T32P; typedef T64* T64P;
// T64P->SUFT32A[].SUFT16A[].SUFT8A[].SUF

//#include <stdlib.h> for calloc()
inline void *zalloc(size_t size) { void *new = calloc(1, size); return new; }

// mul(){ a * b }         b_shl(){ a << b }           rel_eq(){ a == b }
// div(){ a / b }         b_shr(){ a >> b }          rel_neq(){ a != b }
// add(){ a + b }         b_and(){ a & b  }           rel_lt(){ a < b  }
// sub(){ a - b }         b_xor(){ a ^ b  }         rel_lteq(){ a <= b }
// mod(){ a % b }          b_or(){ a | b  }           rel_gt(){ a > b  }
// numinv(){ -a }         b_not(){ ~a     }         rel_gteq(){ a >= b }
// provides the above funcs in the style below, only modifies *dest
// mulT8S(*a, *b, *dest) { a * b } // for the following types:
// T8S T8U T16S T16U T32S T32U T32F T64S T64U T64F
/////////////////////////////////////////// End Evaluative Ops Summary*/

/*///////////////////////////////////////////////detail Evaluative Ops
// types we're going to provide evaluative ops for:

| type     | T8S | T8U | T16S | T16U | T32S | T32U | T32F | T64S | T64U | T64F |
|----------|-----|-----|------|------|------|------|------|------|------|------|
| numinv   |  +  |  -  |  +   |  -   |  +   |  -   |  +   |  +   |  -   |  +   |
| rel_eq   |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| rel_neq  |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| rel_lt   |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| rel_lteq |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| rel_gt   |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| rel_gteq |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| mul      |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| div      |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| add      |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| sub      |  +  |  +  |  +   |  +   |  +   |  +   |  +   |  +   |  +   |  +   |
| mod      |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |
| b_not    |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |
| b_shl    |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |
| b_shr    |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |
| b_and    |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |
| b_xor    |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |
| b_or     |  +  |  +  |  +   |  +   |  +   |  +   |  -   |  +   |  +   |  -   |

    FUNC | Syntax | out type | Description
  numinv |   -a   | in-type  | unary minus
  rel_eq | a == b | bool     | relational equal to
 rel_neq | a != b | bool     | relational inequal to
  rel_lt |  a < b | bool     | relational less than
rel_lteq | a <= b | bool     | relational less than or equal to
  rel_gt |  a > b | bool     | relational greater than
rel_gteq | a >= b | bool     | relational greater than or equal to
     mul |  a * b | in-type  | multiplication
     div |  a / b | in-type  | division
     add |  a + b | in-type  | addition
     sub |  a - b | in-type  | subtraction
     mod |  a % b | in-type  | modulus
   b_not |   ~a   | in-type  | bitwise complement
   b_shl | a << b | in-type  | bitwise shift left
   b_shr | a >> b | in-type  | bitwise shift right
   b_and |  a & b | in-type  | bitwise and
   b_xor |  a ^ b | in-type  | bitwise xor
    b_or |  a | b | in-type  | bitwise or
    cast | (type) | type     | cast

Other important caveats you should care about:

- Unary minus on unsigned is well-defined in C. It computes in the 
unsigned type modulo \(2^N\) (i.e., equivalent to \(0 - a\)). It 
“works,” though it may not match human intent if you expected a 
negative number. We will provide this function, but we're going to lie 
an say we're not providing it in the chart above, this gives compiler 
warnings for good reason, avoid using this function on unsigned.
- Bitwise ops on floats are not allowed.
- **Shifts on signed integers:** Left-shifting a negative value or shifting into/over the sign bit is undefined. Right-shift of negative signed values is implementation-defined. Shifting by a count ≥ bit-width is undefined on all integer types.
- **Division/modulo:** Integer divide by zero is undefined. For signed integers, \( \text{INT\_MIN} / -1 \) is undefined due to overflow. Remainder with negatives is defined (truncates toward zero; remainder has the dividend’s sign).
- **Relational on floats:** All comparisons with NaN are false (including equality), which can surprise. Otherwise fine.
- **Modulo on floats:** There is no `%` for floats; use `fmod`/`fmodf`.
- **Bitwise on signed integers:** Allowed, but be mindful of sign bit semantics and usual integer promotions.

// printf("sizeof(bool) = %zu\n", sizeof(bool));
// sizeof(bool) = 1
// *bool should be a *T8 // we will assume uint8_t

*/////////////////////////////////////////////////////////////////////

/* // using these types can be convoluted.
T64 doubleT64U(T64 input){ input.U = input.U * 2; return input; }
printf("%"PRIu64" doubled is %"PRIu64"\n", 3, doubleT64U((T64){ .U = 3 }).U);

// to load a var into an address TCAST is more readable
printf("%" PRIu64 " doubled is %" PRIu64 "\n",
       (uint64_t)3,
       doubleT64U(TCAST(64, .U, 3)).U);
// and subtytpe manipulation really gets better
T8 low_byte = TCAST(32, .U, 0xDEADBEEF).T8A[0].U; // Extract low byte of 32-bit integer
*/

// punning- using unions to allow operations from other types, without 
// modifying the data on cast. e.g. say you want the integer add or to 
// modify bits on a float but you don't want to modify the data you just 
// want the function you have to pun it.

//////////////////////////////////////////////////////////////////////

typedef void * VoidFuncPtr(void); // VoidFunc* // sizeof(VoidFunc*) //
typedef void VoidFunc(void); // VoidFunc* // sizeof(VoidFunc*) //
// typedef VoidFunc creates an alias for a function pointer type, you 
// can use this alias without instantiating or calling it.
// The goal is to use the "VoidFunc*" type for type declaration without 
// We're never instantiating or calling the function VoidFunc() itself, 
// but we're abusing the VoidFunc* type, to get the compiler to 
// understand the type of the pointer; in a way that is easier to read.

// sizeof(VoidFunc*)
// void*

//////////////////////////////////////////////////////////////////////
#define ASSIGN_MACRO 0
#define ARITH_MACRO 0
#define CAST_MACRO 0
//////////////////////////////////////////////////////////////////////
//   numinv |   -a   | in-type  | unary minus
#define GEN_NUMINV_FUNC(NAME, TYPE) \
void numinv##NAME(TYPE##_t *a, TYPE##_t *dest) { *dest = -(*a); } \
//   rel_eq | a == b | bool     | relational equal to
#define GEN_REL_EQ_FUNC(NAME, TYPE) \
void rel_eq##NAME(TYPE##_t *a, TYPE##_t *b, uint8_t *dest) { *dest = *a == *b; } \
//  rel_neq | a != b | bool     | relational inequal to
#define GEN_REL_NEQ_FUNC(NAME, TYPE) \
void rel_neq##NAME(TYPE##_t *a, TYPE##_t *b, uint8_t *dest) { *dest = *a != *b; } //   rel_lt |  a < b | bool     | relational less than
#define GEN_REL_LT_FUNC(NAME, TYPE) \
void rel_lt##NAME(TYPE##_t *a, TYPE##_t *b, uint8_t *dest) { *dest = *a < *b; } \
// rel_lteq | a <= b | bool     | relational less than or equal to
#define GEN_REL_LTEQ_FUNC(NAME, TYPE) \
void rel_lteq##NAME(TYPE##_t *a, TYPE##_t *b, uint8_t *dest) { *dest = *a <= *b; } //   rel_gt |  a > b | bool     | relational greater than
#define GEN_REL_GT_FUNC(NAME, TYPE) \
void rel_gt##NAME(TYPE##_t *a, TYPE##_t *b, uint8_t *dest) { *dest = *a > *b; } \
// rel_gteq | a >= b | bool     | relational greater than or equal to
#define GEN_REL_GTEQ_FUNC(NAME, TYPE) \
void rel_gteq##NAME(TYPE##_t *a, TYPE##_t *b, uint8_t *dest) { *dest = *a >= *b; }
//      mul |  a * b | in-type  | multiplication
#define GEN_MUL_FUNC(NAME, TYPE) \
void mul##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = (*a) * (*b); }
//      div |  a / b | in-type  | division
#define GEN_DIV_FUNC(NAME, TYPE) \
void div##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = (*a) / (*b); }
//      add |  a + b | in-type  | addition
#define GEN_ADD_FUNC(NAME, TYPE) \
void add##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = (*a) + (*b); }
//      sub |  a - b | in-type  | subtraction
#define GEN_SUB_FUNC(NAME, TYPE) \
void sub##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = (*a) - (*b); }
//      mod |  a % b | in-type  | modulus
#define GEN_MOD_FUNC(NAME, TYPE) \
void mod##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = *a % *b; }
//    b_not |   ~a   | in-type  | bitwise complement
#define GEN_NOT_FUNC(NAME, TYPE) \
void b_not##NAME(TYPE##_t *a, TYPE##_t *dest) { *dest = ~(*a); }
//    b_shl | a << b | in-type  | bitwise shift left
#define GEN_B_SHL_FUNC(NAME, TYPE) \
void b_shl##NAME(TYPE##_t *a, int b, TYPE##_t *dest) { *dest = *a << b; }
//    b_shr | a >> b | in-type  | bitwise shift right
#define GEN_B_SHR_FUNC(NAME, TYPE) \
void b_shr##NAME(TYPE##_t *a, int b, TYPE##_t *dest) { *dest = *a >> b; }
//    b_and |  a & b | in-type  | bitwise and
#define GEN_AND_FUNC(NAME, TYPE) \
void b_and##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = *a & *b; }
//    b_xor |  a ^ b | in-type  | bitwise xor
#define GEN_XOR_FUNC(NAME, TYPE) \
void b_xor##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = *a ^ *b; }
//     b_or |  a | b | in-type  | bitwise or
#define GEN_OR_FUNC(NAME, TYPE) \
void b_or##NAME(TYPE##_t *a, TYPE##_t *b, TYPE##_t *dest) { *dest = *a | *b; }

//////////////////////////////////////////////////////////////////////
#if ASSIGN_MACRO // MACRO is defined and its value is non-zero

#define GEN_ASSIGN_FUNC(NAME, TYPE) \
void assign##NAME(TYPE##_t *a, TYPE##_t *dest) { *dest = (*a); }

#else

#define GEN_ASSIGN_FUNC(NAME, TYPE)

#endif // ASSIGN_MACRO
//////////////////////////////////////////////////////////////////////
#if ARITH_MACRO // MACRO is defined and its value is non-zero

// all types // rel_eq rel_neq rel_lt rel_lteq rel_gt rel_gteq mul div add sub
// numinv // we're going to lie and provide this for backwards compatability 
#define GEN_EVAL_FUNCS(NAME, TYPE) \
GEN_ASSIGN_FUNC(NAME, TYPE) \
 \
GEN_NUMINV_FUNC(NAME, TYPE) \
\
GEN_REL_EQ_FUNC(NAME, TYPE) \
\
GEN_REL_NEQ_FUNC(NAME, TYPE) \
\
GEN_REL_LT_FUNC(NAME, TYPE) \
\
GEN_REL_LTEQ_FUNC(NAME, TYPE) \
\
GEN_REL_GT_FUNC(NAME, TYPE) \
\
GEN_REL_GTEQ_FUNC(NAME, TYPE) \
\
GEN_MUL_FUNC(NAME, TYPE) \
\
GEN_DIV_FUNC(NAME, TYPE) \
\
GEN_ADD_FUNC(NAME, TYPE) \
\
GEN_SUB_FUNC(NAME, TYPE)

GEN_EVAL_FUNCS(T8S,  int8)
GEN_EVAL_FUNCS(T8U,  uint8)
GEN_EVAL_FUNCS(T16S, int16)
GEN_EVAL_FUNCS(T16U, uint16)
GEN_EVAL_FUNCS(T32S, int32)
GEN_EVAL_FUNCS(T32U, uint32)
GEN_EVAL_FUNCS(T64S, int64)
GEN_EVAL_FUNCS(T64U, uint64)
GEN_EVAL_FUNCS(T32F, float32)
GEN_EVAL_FUNCS(T64F, float64)

// no-float // mod b_not b_shl b_shr b_and b_xor b_or 
#define GEN_EVAL_NOFLOAT_FUNCS(NAME, TYPE) \
GEN_MOD_FUNC(##NAME##, ##TYPE##) \
GEN_NOT_FUNC(##NAME##, ##TYPE##) \
GEN_B_SHL_FUNC(##NAME##, ##TYPE##) \
GEN_B_SHR_FUNC(##NAME##, ##TYPE##) \
GEN_AND_FUNC(##NAME##, ##TYPE##) \
GEN_XOR_FUNC(##NAME##, ##TYPE##) \
GEN_OR_FUNC(##NAME##, ##TYPE##)

GEN_EVAL_NOFLOAT_FUNCS(T8S,  int8)
GEN_EVAL_NOFLOAT_FUNCS(T8U,  uint8)
GEN_EVAL_NOFLOAT_FUNCS(T16S, int16)
GEN_EVAL_NOFLOAT_FUNCS(T16U, uint16)
GEN_EVAL_NOFLOAT_FUNCS(T32S, int32)
GEN_EVAL_NOFLOAT_FUNCS(T32U, uint32)
GEN_EVAL_NOFLOAT_FUNCS(T64S, int64)
GEN_EVAL_NOFLOAT_FUNCS(T64U, uint64)

#undef GEN_NUMINV_FUNC
#undef GEN_MUL_FUNC
#undef GEN_DIV_FUNC
#undef GEN_MOD_FUNC
#undef GEN_ADD_FUNC
#undef GEN_SUB_FUNC
#undef GEN_NOT_FUNC
#undef GEN_SHIFT_FUNC
#undef GEN_AND_FUNC
#undef GEN_XOR_FUNC
#undef GEN_OR_FUNC

#undef GEN_ASSIGN_FUNC
//////////////////////////////////////////////////////////////////////
#define GEN_B_ROL_FUNC(NAME, TYPE) \
void b_rol##NAME(uint8_t *a, TYPE##_t *dest) { \
    *a = *a % (8 * sizeof(*dest)); \
    *dest = ((*dest << *a) | (*dest >> ((8 * sizeof(*dest)) - *a))); \
}

#define GEN_B_ROR_FUNC(NAME, TYPE) \
void b_ror##NAME(uint8_t *a, TYPE##_t *dest) { \
    *a = *a % (8 * sizeof(*dest)); \
    *dest = ((*dest >> *a) | (*dest << ((8 * sizeof(*dest)) - *a))); \
}

#define GEN_B_SET_FUNC(NAME, TYPE)                                 \
    /* set_u##NAME  – stores bit *a into *dest */                   \
    void b_set_##NAME(uint##TYPE##_t *dest, uint8_t *a) {              \
        assert(*a < (8 * sizeof *dest));                           \
        *dest |= ((uint##TYPE##_t)1 << *a);                         \
    }

#define GEN_B_GET_FUNC(NAME, TYPE)                                 \
    /* get_u##NAME  – returns the bit *a from *dest */             \
    uint8_t b_get_##NAME(uint##TYPE##_t *dest, uint8_t *a) {           \
        assert(*a < (8 * sizeof *dest));                           \
        return (*dest >> *a) & 1U;                                  \
    }

// no-float // mod b_not b_shl b_shr b_and b_xor b_or 
#define GEN_BIT_OPS_FUNCS(NAME, TYPE) \
GEN_B_ROL_FUNC(##NAME##, ##TYPE##) \
GEN_B_ROR_FUNC(##NAME##, ##TYPE##) \
GEN_B_SET_FUNC(##NAME##, ##TYPE##) \
GEN_B_GET_FUNC(##NAME##, ##TYPE##)

GEN_BIT_OPS_FUNCS(T8U,  uint8)
GEN_BIT_OPS_FUNCS(T16U, uint16)
GEN_BIT_OPS_FUNCS(T32U, uint32)
GEN_BIT_OPS_FUNCS(T64U, uint64)

#endif // ARITH_MACRO

/* __________________________________________________________________ */


/* CAST_MACRO generates this table of 90 functions
RTWX_TWX() origin and cast 8 16 32 64 S U F

| CAST  | T8.S        | T8.U        | T16.S        | T16.U        | T32.S        | T32.U        | T32.F        | T64.S        | T64.U        | T64.F        |
|-------|-------------|-------------|--------------|--------------|--------------|--------------|--------------|--------------|--------------|--------------|
| T8.S  | X           | RT8S_T8U()  | RT8S_T16S()  | RT8S_T16U()  | RT8S_T32S()  | RT8S_T32U()  | RT8S_T32F()  | RT8S_T64S()  | RT8S_T64U()  | RT8S_T64F()  |
| T8.U  | RT8U_T8S()  | X           | RT8U_T16S()  | RT8U_T16U()  | RT8U_T32S()  | RT8U_T32U()  | RT8U_T32F()  | RT8U_T64S()  | RT8U_T64U()  | RT8U_T64F()  |
| T16.S | RT16S_T8S() | RT16S_T8U() | X            | RT16S_T16U() | RT16S_T32S() | RT16S_T32U() | RT16S_T32F() | RT16S_T64S() | RT16S_T64U() | RT16S_T64F() |
| T16.U | RT16U_T8S() | RT16U_T8U() | RT16U_T16S() | X            | RT16U_T32S() | RT16U_T32U() | RT16U_T32F() | RT16U_T64S() | RT16U_T64U() | RT16U_T64F() |
| T32.S | RT32S_T8S() | RT32S_T8U() | RT32S_T16S() | RT32S_T16U() | X            | RT32S_T32U() | RT32S_T32F() | RT32S_T64S() | RT32S_T64U() | RT32S_T64F() |
| T32.U | RT32U_T8S() | RT32U_T8U() | RT32U_T16S() | RT32U_T16U() | RT32U_T32S() | X            | RT32U_T32F() | RT32U_T64S() | RT32U_T64U() | RT32U_T64F() |
| T32.F | RT32F_T8S() | RT32F_T8U() | RT32F_T16S() | RT32F_T16U() | RT32F_T32S() | RT32F_T32U() | X            | RT32F_T64S() | RT32F_T64U() | RT32F_T64F() |
| T64.S | RT64S_T8S() | RT64S_T8U() | RT64S_T16S() | RT64S_T16U() | RT64S_T32S() | RT64S_T32U() | RT64S_T32F() | X            | RT64S_T64U() | RT64S_T64F() |
| T64.U | RT64U_T8S() | RT64U_T8U() | RT64U_T16S() | RT64U_T16U() | RT64U_T32S() | RT64U_T32U() | RT64U_T32F() | RT64U_T64S() | X            | RT64U_T64F() |
| T64.F | RT64F_T8S() | RT64F_T8U() | RT64F_T16S() | RT64F_T16U() | RT64F_T32S() | RT64F_T32U() | RT64F_T32F() | RT64F_T64S() | RT64F_T64U() | X            |

*/

#if CAST_MACRO // Code MACRO is defined and its value is non-zero
// #define RETURN_FUNCTION(SNT, DNT, STT, DTT) \
//     inline DTT SNT##_##DNT(STT *value) { return (DTT)(*value); }

// Core definition macro
#define DEF_CAST_FN(SRC_NAME, DST_NAME, SRC_TYPE, DST_TYPE)             \
    inline DST_TYPE inl_##SRC_NAME##_##DST_NAME##(const SRC_TYPE *value) {\
        return (DST_TYPE)(*value);                                      \
    }                                                                   \
    void SRC_NAME##_##DST_NAME(const SRC_TYPE *value, DST_TYPE *result) {\
        *result = (DST_TYPE)(*value);                                   \
    }

// Implementations for the *_T64F() functions
DEF_CAST_FN(RT8S, T64F, int8_t, float64_t)
DEF_CAST_FN(RT8U, T64F, uint8_t, float64_t)
DEF_CAST_FN(RT16S, T64F, int16_t, float64_t)
DEF_CAST_FN(RT16U, T64F, uint16_t, float64_t)
DEF_CAST_FN(RT32S, T64F, int32_t, float64_t)
DEF_CAST_FN(RT32U, T64F, uint32_t, float64_t)
DEF_CAST_FN(RT32F, T64F, float32_t, float64_t)
DEF_CAST_FN(RT64S, T64F, int64_t, float64_t)
DEF_CAST_FN(RT64U, T64F, uint64_t, float64_t)
// Implementations for the *_T64U() functions
DEF_CAST_FN(RT8S, T64U, int8_t, uint64_t)
DEF_CAST_FN(RT8U, T64U, uint8_t, uint64_t)
DEF_CAST_FN(RT16S, T64U, int16_t, uint64_t)
DEF_CAST_FN(RT16U, T64U, uint16_t, uint64_t)
DEF_CAST_FN(RT32S, T64U, int32_t, uint64_t)
DEF_CAST_FN(RT32U, T64U, uint32_t, uint64_t)
DEF_CAST_FN(RT32F, T64U, float32_t, uint64_t)
DEF_CAST_FN(RT64S, T64U, int64_t, uint64_t)
DEF_CAST_FN(RT64F, T64U, float64_t, uint64_t)
// Implementations for the *_T64S() functions
DEF_CAST_FN(RT8S, T64S, int8_t, int64_t)
DEF_CAST_FN(RT8U, T64S, uint8_t, int64_t)
DEF_CAST_FN(RT16S, T64S, int16_t, int64_t)
DEF_CAST_FN(RT16U, T64S, uint16_t, int64_t)
DEF_CAST_FN(RT32S, T64S, int32_t, int64_t)
DEF_CAST_FN(RT32U, T64S, uint32_t, int64_t)
DEF_CAST_FN(RT32F, T64S, float32_t, int64_t)
DEF_CAST_FN(RT64U, T64S, uint64_t, int64_t)
DEF_CAST_FN(RT64F, T64S, float64_t, int64_t)
// Implementations for the *_T32F() functions
DEF_CAST_FN(RT8S, T32F, int8_t, float32_t)
DEF_CAST_FN(RT8U, T32F, uint8_t, float32_t)
DEF_CAST_FN(RT16S, T32F, int16_t, float32_t)
DEF_CAST_FN(RT16U, T32F, uint16_t, float32_t)
DEF_CAST_FN(RT32S, T32F, int32_t, float32_t)
DEF_CAST_FN(RT32U, T32F, uint32_t, float32_t)
DEF_CAST_FN(RT64S, T32F, int64_t, float32_t)
DEF_CAST_FN(RT64U, T32F, uint64_t, float32_t)
DEF_CAST_FN(RT64F, T32F, float64_t, float32_t)
// Implementations for the *_T32U() functions
DEF_CAST_FN(RT8S, T32U, int8_t, uint32_t)
DEF_CAST_FN(RT8U, T32U, uint8_t, uint32_t)
DEF_CAST_FN(RT16S, T32U, int16_t, uint32_t)
DEF_CAST_FN(RT16U, T32U, uint16_t, uint32_t)
DEF_CAST_FN(RT32S, T32U, int32_t, uint32_t)
DEF_CAST_FN(RT32F, T32U, float32_t, uint32_t)
DEF_CAST_FN(RT64S, T32U, int64_t, uint32_t)
DEF_CAST_FN(RT64U, T32U, uint64_t, uint32_t)
DEF_CAST_FN(RT64F, T32U, float64_t, uint32_t)
// Implementations for the *_T32S() functions
DEF_CAST_FN(RT8S, T32S, int8_t, int32_t)
DEF_CAST_FN(RT8U, T32S, uint8_t, int32_t)
DEF_CAST_FN(RT16S, T32S, int16_t, int32_t)
DEF_CAST_FN(RT16U, T32S, uint16_t, int32_t)
DEF_CAST_FN(RT32U, T32S, uint32_t, int32_t)
DEF_CAST_FN(RT32F, T32S, float32_t, int32_t)
DEF_CAST_FN(RT64S, T32S, int64_t, int32_t)
DEF_CAST_FN(RT64U, T32S, uint64_t, int32_t)
DEF_CAST_FN(RT64F, T32S, float64_t, int32_t)
// Implementations for the *_T16S() functions
DEF_CAST_FN(RT8S, T16S, int8_t, int16_t)
DEF_CAST_FN(RT8U, T16S, uint8_t, int16_t)
DEF_CAST_FN(RT16U, T16S, uint16_t, int16_t)
DEF_CAST_FN(RT32S, T16S, int32_t, int16_t)
DEF_CAST_FN(RT32U, T16S, uint32_t, int16_t)
DEF_CAST_FN(RT32F, T16S, float32_t, int16_t)
DEF_CAST_FN(RT64S, T16S, int64_t, int16_t)
DEF_CAST_FN(RT64U, T16S, uint64_t, int16_t)
DEF_CAST_FN(RT64F, T16S, float64_t, int16_t)
// Implementations for the *_T16U() functions
DEF_CAST_FN(RT8S, T16U, int8_t, uint16_t)
DEF_CAST_FN(RT8U, T16U, uint8_t, uint16_t)
DEF_CAST_FN(RT16S, T16U, int16_t, uint16_t)
DEF_CAST_FN(RT32S, T16U, int32_t, uint16_t)
DEF_CAST_FN(RT32U, T16U, uint32_t, uint16_t)
DEF_CAST_FN(RT32F, T16U, float32_t, uint16_t)
DEF_CAST_FN(RT64S, T16U, int64_t, uint16_t)
DEF_CAST_FN(RT64U, T16U, uint64_t, uint16_t)
DEF_CAST_FN(RT64F, T16U, float64_t, uint16_t)
// Implementations for the *_T8S() functions
DEF_CAST_FN(RT8U, T8S, uint8_t, int8_t)
DEF_CAST_FN(RT16S, T8S, int16_t, int8_t)
DEF_CAST_FN(RT16U, T8S, uint16_t, int8_t)
DEF_CAST_FN(RT32S, T8S, int32_t, int8_t)
DEF_CAST_FN(RT32U, T8S, uint32_t, int8_t)
DEF_CAST_FN(RT32F, T8S, float32_t, int8_t)
DEF_CAST_FN(RT64S, T8S, int64_t, int8_t)
DEF_CAST_FN(RT64U, T8S, uint64_t, int8_t)
DEF_CAST_FN(RT64F, T8S, float64_t, int8_t)
// Implementations for the *_T8U() functions
DEF_CAST_FN(RT8S, T8U, int8_t, uint8_t)
DEF_CAST_FN(RT16S, T8U, int16_t, uint8_t)
DEF_CAST_FN(RT16U, T8U, uint16_t, uint8_t)
DEF_CAST_FN(RT32S, T8U, int32_t, uint8_t)
DEF_CAST_FN(RT32U, T8U, uint32_t, uint8_t)
DEF_CAST_FN(RT32F, T8U, float32_t, uint8_t)
DEF_CAST_FN(RT64S, T8U, int64_t, uint8_t)
DEF_CAST_FN(RT64U, T8U, uint64_t, uint8_t)
DEF_CAST_FN(RT64F, T8U, float64_t,  uint8_t)

#endif // CAST_MACRO // just use its output

#ifndef BITS_PER_DIGIT
#define BITS_PER_DIGIT 3.32192809488736234786 // bits per base 10 digit
#endif // BITS_PER_DIGIT // defined in the libBF library

#define DEFINE_FloPRINT()                                                   \
                                                                            \
inline void print_f64p(float64_t *x) {                                      \
 /* float64_t = 65 bits = 1 Sign bit, 11 Exponent bits, 53 mantissa bits */ \
  if (isfinite(*x)) {                                                       \
    int32_t exponent;                                                         \
    frexp(*x, &exponent);                                                     \
    if ((exponent >= 53) || ((*x > -0.0001) && (*x < 0.0001))){               \
       /* int8_t digits = (int8_t)round(53 / BITS_PER_DIGIT); */              \
       /* printf("%.*E", digits, *x); //digits=16 */                          \
      printf("%.16E", *x);                                                    \
    } else {                                                                  \
      int8_t digits = (int8_t)round( ((53 - exponent) / BITS_PER_DIGIT));     \
      printf("%.*f", digits, *x);                                             \
    }                                                                         \
  /*} else printf("%.*f", 17 - exponent, *x); */                            \
    return;                                                                 \
  }                                                                         \
  if (isnan(*x)) fputs("NaN", stdout);                                      \
  else fputs((*x > 0) ? "Inf" : "-Inf", stdout);                            \
}                                                                           \
                                                                            \
/* float32_t for (2^0)+(2^−23)=1.00000000000000000000001 */                 \
/* 00000000000000000000001 */                                               \
inline void print_f32p(float32_t *x) {                                      \
/* float32_t = 33 bits = 1 Sign bit, 8 Exponent bits, 24 mantissa bits */   \
  if (isfinite(*x)) {                                                       \
    int32_t exponent;                                                         \
    frexp(*x, &exponent);                                                     \
    if ((exponent >= 23) || ((*x > -0.0001) && (*x < 0.0001))){               \
      printf("%.6E", (float) *x);                                             \
    } else {                                                                  \
      int8_t digits = (int8_t)round( ((23 - exponent) / BITS_PER_DIGIT));     \
      printf("%.*f", digits, *x);                                             \
    }                                                                         \
    return;                                                                 \
  }                                                                         \
  if (isnan(*x)) fputs("NaN", stdout);                                      \
  else fputs((*x > 0) ? "Inf" : "-Inf", stdout);                            \
}                                                                           \
                                                                            \
inline void print_f64(float64_t x) { print_f64p(&x); }                      \
inline void print_f32(float32_t x) { print_f32p(&x); }                      \

#ifndef __GNUC__
DEFINE_FloPRINT()
#else
#endif  // _GNUC_

#endif // EVALUATIVE_OPS_FILE_H

// ;; A.2 Phrase structure grammar 
// ;; A.2.1 Expressions
// ;; (6.5.3) - ~
// ;; (6.5.4) ( type-name ) cast-expression
// ;; (6.5.5) * / %
// ;; (6.5.6) + -
// ;; (6.5.7) << >>
// ;; (6.5.8) < > <= >=
// ;; (6.5.10) &
// ;; (6.5.11) ^
// ;; (6.5.12) |

/* we're not going to handle these: branching or assignment must be handled by a parser
We're either '
### **3. Side‑Effecting cannot return boole or branching Testing Functions or assign

;; (6.5.10-6.5.15)
        / AND-expression & equality-expression
        / exclusive-OR-expression ^ AND-expression
        / inclusive-OR-expression | exclusive-OR-expression
        / logical-AND-expression && inclusive-OR-expression
        / logical-OR-expression || logical-AND-expression
        / logical-OR-expression ? expression : conditional-expression

;; (6.5.16)
    assignment-expression =
          conditional-expression
        / unary-expression assignment-operator assignment-expression
;; (6.5.16)
    assignment-operator =
          "=" / "*=" / "/=" / "%=" / "+=" / "-=" / "<<=" / ">>=" / "&=" / "^=" / "|="
;; (6.5.17)
    expression =
          assignment-expression
        / expression , assignment-expression
;; (6.6)
    constant-expression =
          conditional-expression

| Feature    |                   Format Structure                  | Hardware-Scaling  | Memory        |               Accuracy              |
|------------|:---------------------------------------------------:|-------------------|---------------|:-----------------------------------:|
| FP4 (E2M1) |       4 bits (1 sign, 2 exponent, 1 mantissa)       |         No        | ~25% of FP16  |     Risk of noticeable accuracy     |
|            |             plus software scaling factor            |                   |               |         drop compared to FP8        |
|   MXFP4    |       4 bits (1 sign, 2 exponent, 1 mantissa)       |        Yes        | ~25% of FP16  |     Risk of noticeable accuracy     |
|            | plus 1 shared power-of-two scale per 32 value block |                   |               |         drop compared to FP8        |
|   NVFP4    |       4 bits (1 sign, 2 exponent, 1 mantissa)       |        Yes        | ~25% of FP16  |  Lower risk of noticeable accuracy  |
|            |      plus 1 shared FP8 scale per 16 value block     |                   |               | drop particularly for larger models |


 */

// #ifndef ZALLOC_HEADER_FILE_H
// #define ZALLOC_HEADER_FILE_H
// #define DEFINE_ZALLOC() \
//     /* malloc(size) NOT GUARANTEED to be zero */ \
//     inline void *zalloc(size_t size) { /* zeroed memory allocate */ \
//         void *new = calloc(1, size); /* calloc returns zeroed memory */ \
//         /*assert(new != NULL); *//* Check for allocation failure */ \
//         return new; \
//     }
// DEFINE_ZALLOC()
// #endif // ZALLOC_HEADER_FILE_H

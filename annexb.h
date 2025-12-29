
//////////////////////////////////////////////////////////////////////
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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT  WARRANTY  OF  ANY  KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES  OF
// MERCHANTABILITY,   FITNESS   FOR   A   PARTICULAR    PURPOSE    AND
// NONINFRINGEMENT.  IN  NO  EVENT  SHALL  THE  AUTHORS  OR  COPYRIGHT
// OWNER(S) BE LIABLE FOR  ANY  CLAIM,  DAMAGES  OR  OTHER  LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
// OUT OF OR IN CONNECTION WITH THE  SOFTWARE  OR  THE  USE  OR  OTHER
// DEALINGS IN THE SOFTWARE.

//////////////////////////////////////////////////////////////////////
// The absence of the clause:

// "The above copyright notice and this  permission  notice  shall  be
// included in all copies or substantial portions of the Software."

// basically puts this file into public domain.

//////////////////////////////////////////////////////////////////////

#ifndef SKIP_MARKED  // skip entire file when debugging macros
// gcc -E -P -DSKIP_MARKED somefile.h > somefile.i.h

#ifndef ANNEX_B_H
#define ANNEX_B_H

// https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf

// Listed & documented in K&R C(2nd edition)
// <assert.h>
// <ctype.h>
// <float.h>
// <limits.h>
// <math.h>
// <setjmp.h>
// <signal.h>
// <stdarg.h>
// <stdio.h>
// <stdlib.h>
// <string.h>
// <time.h>

// Listed in K&R C but not documented there
// <errno.h>
// <locale.h>
// <stddef.h>

// New in SUSv2 AND Later included in C99
// <complex.h>
// <fenv.h>
// <inttypes.h>
// <iso646.h>
// <stdbool.h>
// <stdint.h>
// <tgmath.h>
// <wchar.h>
// <wctype.h>

// Annex B (informative)_Library_summary____________________ [p419N1256]
// <assert.h>  <inttypes.h> <signal.h>  <stdlib.h>
// <complex.h> <iso646.h>   <stdarg.h>  <string.h>
// <ctype.h>   <limits.h>   <stdbool.h> <tgmath.h>
// <errno.h>   <locale.h>   <stddef.h>  <time.h>
// <fenv.h>    <math.h>     <stdint.h>  <wchar.h>
// <float.h>   <setjmp.h>   <stdio.h>   <wctype.h>

// B.1 Diagnostics_<assert.h>_______________________________ [p419N1256]
#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif  // ASSERT_H

// B.2 Complex_<complex.h>__________________________________ [p419N1256]
 /*
#ifndef COMPLEX_H
#define COMPLEX_H
#include <complex.h>
#endif  // COMPLEX_H
 */

// B.3 Character_handling_<ctype.h>_________________________ [p421N1256]
#ifndef CTYPE_H
#define CTYPE_H
#include <ctype.h>
#endif  // CTYPE_H

// B.4 Errors_<errno.h>_____________________________________ [p421N1256]
#ifndef ERRNO_H
#define ERRNO_H
#include <errno.h>
#endif  // ERRNO_H

// B.5 Floating-point_environment_<fenv.h>__________________ [p421N1256]
#ifndef FENV_H
#define FENV_H
#include <fenv.h>
#endif  // FENV_H

// B.6 Characteristics_of_floating_types_<float.h>__________ [p422N1256]
#ifndef FLOAT_H
#define FLOAT_H
#include <float.h>
#endif  // FLOAT_H

// B.7 Format_conversion_of_integer_types_<inttypes.h>______ [p422N1256]
#ifndef INTTYPES_H
#define INTTYPES_H
#include <inttypes.h> // for PRIXNN for printf()
#endif  // INTTYPES_H

// B.8 Alternative_spellings_<iso646.h>_____________________ [p423N1256]
#ifndef ISO646_H
#define ISO646_H
#define and &&
#define not !
#define not_eq !=
#define or ||
//bitwise ops are below, regulare ops are above
#define and_eq &=
#define bitand &
#define bitor |
#define compl ~
#define or_eq |=
#define xor ^
#define xor_eq ^=
#endif  // ISO646_H

// 6.4.6 clause 3
// In all aspects of the language, the six tokens
//           <:    :>      <%    %>     %:     %:%:
//
// behave, respectively, the same as the six tokens
//           [     ]       {     }      #      ##
//
// Digraphs "<:", ":>", "<%", "%>", "%:", "%:%:" were created for
// programmers that didn't have a keyboard which supported
// the ISO 646 character set.

#ifndef ISO646_H
#define ISO646_H
#include <iso646.h>
#endif  // ISO646_H already defined ;) // some reason TCC didn't like the one on my system

// B.9 Sizes_of_integer_types_<limits.h>____________________ [p423N1256]
#ifndef LIMITS_H
#define LIMITS_H
#include <limits.h>
#endif  // LIMITS_H

// B.10 Localization_<locale.h>_____________________________ [p423N1256]
#ifndef LOCALE_H
#define LOCALE_H
#include <locale.h>
#endif  // LOCALE_H

// B.11 Mathematics_<math.h>________________________________ [p423N1256]
#ifndef MATH_H
#define MATH_H
#include <math.h> // for pow() and frexp()
#endif  // MATH_H

// B.12 Nonlocal_jumps_<setjmp.h>___________________________ [p428N1256]
#ifndef SETJMP_H
#define SETJMP_H
#include <setjmp.h>
#endif  // SETJMP_H

// B.13 Signal_handling_<signal.h>__________________________ [p428N1256]
#ifndef SIGNAL_H
#define SIGNAL_H
#include <signal.h>
#endif  // SIGNAL_H

// B.14 Variable_arguments_<stdarg.h>_______________________ [p428N1256]
#ifndef STDARG_H
#define STDARG_H
#include <stdarg.h>
#endif  // STDARG_H

// B.15 Boolean_type_and_values_<stdbool.h>_________________ [p428N1256]
#ifndef STDBOOL_H
#define STDBOOL_H
#include <stdbool.h>
#endif  // STDBOOL_H

// B.16 Common_definitions_<stddef.h>_______________________ [p429N1256]
#ifndef STDDEF_H
#define STDDEF_H
#include <stddef.h>
#endif  // STDDEF_H

// B.17 Integer_types_<stdint.h>____________________________ [p429N1256]
//             8-bits  16-bits        32-bits   64-bits
// uintN_t     char    unsigned short unsigned  unsigned long
// intN_t      schar   short          int       long
// floatN_t    XXXXXX  ??"half"       float     double     
// these seem a little random and convoluted not to mention they can
// mean different things on different compilers
// thank god someone with half a brain stepped in and made stdint
#ifndef STDINT_H
#define STDINT_H
#include <stdint.h> // for intN_t and uintN_t
#endif  // STDINT_H

// B.18 Input/output_<stdio.h>______________________________ [p429N1256]
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h> // for printf() and file io
#endif  // STDIO_H

// B.19 General_utilities_<stdlib.h>________________________ [p431N1256]
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif  // STDLIB_H

// B.20 String_handling_<string.h>__________________________ [p433N1256]
#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif  // STRING_H

// B.21 Type-generic_math_<tgmath.h>________________________ [p434N1256]
 /*
#ifndef TGMATH_H
#define TGMATH_H
#include <tgmath.h>
#endif  // TGMATH_H
 */

// The header <tgmath.h> includes the headers <math.h> and <complex.h> and defines several type-generic macros.

// B.22 Date_and_time_<time.h>______________________________ [p434N1256]
#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif  // TIME_H

// B.23 multibyte/wide_character_utilities_<wchar.h>________ [p435N1256]
#ifndef WCHAR_H
#define WCHAR_H
#include <wchar.h>
#endif  // WCHAR_H

// B.24 Wide_character_classification_<wctype.h>____________ [p437N1256]
#ifndef WCTYPE_H
#define WCTYPE_H
#include <wctype.h>
#endif  // WCTYPE_H

/* __________________________________________________________________ */

// why the fuck did this never happen??
// typedef float float32_t;
// typedef double float64_t;

/* __________________________________________________________________ */

#endif // ANNEX_B_H

#endif // SKIP_MARKED

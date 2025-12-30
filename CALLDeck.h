
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

/*//////////////////////////////////////////////////////////////////////////////////////

           _____ _____ __    __    ____          _     _   
          |     |  _  |  |  |  |  |    \ ___ ___| |_  | |_ 
          |   --|     |  |__|  |__|  |  | -_|  _| '_|_|   |
          |_____|__|__|_____|_____|____/|___|___|_,_|_|_|_|


*///////////////////////////////////////////////////////////////////////////////////////
#ifndef fail_status_t

enum fail_status_e { SUCCESS = 0, EMPTY = 1, FULL = 2 };
typedef uint8_t fail_status_t; // the uint8_t version

#endif /* fail_status_t */
////////////////////////////////////////////////////////////////////////////////////////
//#pragma pack(1)

#ifndef CALLDECKTYPE_H
#define CALLDECKTYPE_H

#define DEFINE_CALLDECK_MEM(type, CA_size, CAPACITY)                                 \
inline bool FREE_CA_##type##_##CA_size ( CA_##type##_##CA_size **pdeque ){           \
    return true; /*let the function fail the LLDECK add or sub*/                     \
}                                                                                    \
inline bool ALLOC_CA_##type##_##CA_size ( CA_##type##_##CA_size **pdeque ){          \
    return true; /*let the function fail the LLDECK add or sub*/                     \
}

#define DEFINE_CALLDECK_FUNCS(type, CA_size, CAPACITY)                               \
/* ___________________________________________Function Declarations */               \
void pushStart_CALLDECK_##type##_##CA_size(type *source, LLDeck_CA_##type##_##CA_size** pile);  \
void pushEnd_CALLDECK_##type##_##CA_size(type *source, LLDeck_CA_##type##_##CA_size** pile);    \
bool popStart_CALLDECK_##type##_##CA_size(type *dest, LLDeck_CA_##type##_##CA_size** pile);     \
bool popEnd_CALLDECK_##type##_##CA_size(type *dest, LLDeck_CA_##type##_##CA_size** pile);       \
                                                                                     \
/* ___________________________________________Function Implementation */             \
void pushStart_CALLDECK_##type##_##CA_size(type *source, LLDeck_CA_##type##_##CA_size** pile) { \
    CA_##type##_##CA_size *curr_ca = NULL;                                           \
    bool is_new_ca = false;                                                          \
    if (!Start_LLDeck_CA_##type##_##CA_size(&curr_ca, *pile) || curr_ca->size == CA_size) { \
        addStart_LLDeck_CA_##type##_##CA_size(*pile);                                \
        is_new_ca = true;                                                            \
    }                                                                                \
    Start_LLDeck_CA_##type##_##CA_size(&curr_ca, *pile);                             \
    if (is_new_ca) { /* Manually handle first push to a new CA */                    \
        curr_ca->data[curr_ca->start_offset] = *source;                              \
    } else {                                                                         \
        pushStart_CA_##type##_##CA_size(source, &curr_ca);                           \
    }                                                                                \
}                                                                                    \
                                                                                     \
void pushEnd_CALLDECK_##type##_##CA_size(type *source, LLDeck_CA_##type##_##CA_size** pile) {   \
    CA_##type##_##CA_size *curr_ca = NULL;                                           \
    bool is_new_ca = false;                                                          \
    if (!End_LLDeck_CA_##type##_##CA_size(&curr_ca, *pile) || curr_ca->size == CA_size) { \
        addEnd_LLDeck_CA_##type##_##CA_size(*pile);                                  \
        is_new_ca = true;                                                            \
    }                                                                                \
    End_LLDeck_CA_##type##_##CA_size(&curr_ca, *pile);                               \
    if (is_new_ca) { /* Manually handle first push to a new CA */                    \
        curr_ca->data[curr_ca->start_offset] = *source;                              \
    } else {                                                                         \
        pushEnd_CA_##type##_##CA_size(source, &curr_ca);                             \
    }                                                                                \
}                                                                                    \
                                                                                     \
bool popStart_CALLDECK_##type##_##CA_size(type *dest, LLDeck_CA_##type##_##CA_size** pile) {    \
    CA_##type##_##CA_size *curr_ca = NULL;                                           \
    if (!Start_LLDeck_CA_##type##_##CA_size(&curr_ca, *pile)) return false;          \
    if (popStart_CA_##type##_##CA_size(dest, &curr_ca) == EMPTY) {                   \
        subStart_LLDeck_CA_##type##_##CA_size(*pile);                                \
    }                                                                                \
    return true;                                                                     \
}                                                                                    \
                                                                                     \
bool popEnd_CALLDECK_##type##_##CA_size(type *dest, LLDeck_CA_##type##_##CA_size** pile) {      \
    CA_##type##_##CA_size *curr_ca = NULL;                                           \
    if (!End_LLDeck_CA_##type##_##CA_size(&curr_ca, *pile)) return false;            \
    if (popEnd_CA_##type##_##CA_size(dest, &curr_ca) == EMPTY) {                     \
        subEnd_LLDeck_CA_##type##_##CA_size(*pile);                                  \
    }                                                                                \
    return true;                                                                     \
}

#define DEFINE_CALLDECK(type, CA_size)               \
DEFINE_CIRCARRAY_STRUCTS(type, CA_size, (CA_size+1)) \
DEFINE_LLDECK(CA_##type##_##CA_size)                 \
DEFINE_CALLDECK_MEM(type, CA_size, (CA_size+1))      \
DEFINE_CIRCARRAY_FUNCS(type, CA_size, (CA_size+1))   \
DEFINE_CALLDECK_FUNCS(type, CA_size, (CA_size+1))

#endif /* CALLDECKTYPE_H */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef CA_UNLINKED
#define CA_UNLINKED

// #ifndef FREE_CA_##type##_##CA_size

#define DEFINE_CIRCARRAY_MEM(type, CA_size, CAPACITY)                                \
inline bool FREE_CA_##type##_##CA_size ( CA_##type##_##CA_size **pdeque ){           \
    free(*pdeque); *pdeque = NULL;                                                   \
    return false;                                                                    \
}                                                                                    \
inline bool ALLOC_CA_##type##_##CA_size ( CA_##type##_##CA_size **pdeque ){          \
    *pdeque = zalloc(sizeof(CA_##type##_##CA_size));                                 \
    return false;                                                                    \
}

// #endif // DEFINE_CIRCARRAY_MEM

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
fail_status_t pushStart_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **pdeque);  \
fail_status_t pushEnd_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **pdeque);    \
fail_status_t popStart_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **pdeque);     \
fail_status_t popEnd_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **pdeque);       \
                                                                                     \
/* ___________________________________________Function Implementation */             \
fail_status_t pushStart_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **pdeque) { \
    if (*pdeque == NULL) { /* push 1st = 0th elem */                                 \
        if (ALLOC_CA_##type##_##CA_size (pdeque)) return FULL; /* alloc fail */  \
        (*pdeque)->data[0] = *source;                                                \
        return SUCCESS;                                                              \
    }                                                                                \
    if ((*pdeque)->size == CA_size) return FULL; /* array full */                   \
    (*pdeque)->start_offset = ((*pdeque)->start_offset + CAPACITY - 1) % CAPACITY;   \
    (*pdeque)->data[(*pdeque)->start_offset] = *source;                              \
    (*pdeque)->size++;                                                               \
    return SUCCESS;                                                                  \
}                                                                                    \
                                                                                     \
fail_status_t pushEnd_CA_##type##_##CA_size(type *source, CA_##type##_##CA_size **pdeque) {   \
    if (*pdeque == NULL) { /* push 1st = 0th elem */                                 \
        if (ALLOC_CA_##type##_##CA_size (pdeque)) return FULL; /* alloc fail */  \
        (*pdeque)->data[0] = *source;                                                \
        return SUCCESS;                                                              \
    }                                                                                \
    if ((*pdeque)->size == CA_size) return FULL; /* array full */                   \
    uint8_t end_index = ((*pdeque)->start_offset + (*pdeque)->size + 1) % CAPACITY;  \
    (*pdeque)->data[end_index] = *source;                                            \
    (*pdeque)->size++;                                                               \
    return SUCCESS;                                                                  \
}                                                                                    \
                                                                                     \
fail_status_t popStart_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **pdeque) {    \
    if (*pdeque == NULL) return EMPTY; /* fail on empty */                           \
    *dest = (*pdeque)->data[(*pdeque)->start_offset];                                \
    (*pdeque)->start_offset = ((*pdeque)->start_offset + 1) % CAPACITY;              \
    if ((*pdeque)->size == 0) { /* pop last elem */                                  \
        if (FREE_CA_##type##_##CA_size (pdeque)) return EMPTY; /* free fail */  \
    } else (*pdeque)->size--;                                                        \
    return SUCCESS;                                                                  \
}                                                                                    \
                                                                                     \
fail_status_t popEnd_CA_##type##_##CA_size(type *dest, CA_##type##_##CA_size **pdeque) {      \
    if (*pdeque == NULL) return EMPTY; /* fail on empty */                           \
    uint8_t end_index = ((*pdeque)->start_offset + (*pdeque)->size) % CAPACITY;      \
    *dest = (*pdeque)->data[end_index];                                              \
    if ((*pdeque)->size == 0) { /* pop last elem */                                  \
        if (FREE_CA_##type##_##CA_size (pdeque)) return EMPTY; /* free fail */  \
        return SUCCESS;                                                              \
    } else (*pdeque)->size--;                                                        \
    return SUCCESS;                                                                  \
}                                                                                    \

#endif // CA_UNLINKED

////////////////////////////////////////////////////////////////////////////////////////

#ifndef LLDECKTYPE_H
#define LLDECKTYPE_H

#define DEFINE_LLDECK(type)                                     \
                                                                \
/* __________________________________________Data Structures */ \
typedef struct LLNode_##type {                                  \
    type data;                                                  \
    struct LLNode_##type* next;                                 \
    struct LLNode_##type* prev;                                 \
} LLNode_##type;                                                \
                                                                \
typedef struct LLDeck_##type {                                  \
    uint64_t size;                                              \
    struct LLNode_##type* Start;                                \
    struct LLNode_##type* End;                                  \
} LLDeck_##type;                                                \
                                                                \
/* ____________________________________Function Declarations */ \
bool Start_LLDeck_##type (type **xref, LLDeck_##type* pile);    \
bool End_LLDeck_##type (type **xref, LLDeck_##type* pile);      \
inline void subStart_LLDeck_##type (LLDeck_##type* pile);       \
inline void subEnd_LLDeck_##type (LLDeck_##type* pile);         \
inline void addStart_LLDeck_##type (LLDeck_##type* pile);       \
inline void addEnd_LLDeck_##type (LLDeck_##type* pile);         \
bool popStart_LLDeck_##type (type *xref, LLDeck_##type* pile);  \
bool popEnd_LLDeck_##type (type *xref, LLDeck_##type* pile);    \
void pushStart_LLDeck_##type (type *xref, LLDeck_##type* pile); \
void pushEnd_LLDeck_##type (type *xref, LLDeck_##type* pile);   \
                                                                \
/* _____________________________________Deck Implementation */  \
                                                                \
bool Start_LLDeck_##type (type **xref, LLDeck_##type* pile) {   \
    if (pile == NULL || pile->size == 0) return false;          \
    *xref = &((pile->Start)->data);                             \
    return true;                                                \
}                                                               \
                                                                \
bool End_LLDeck_##type (type **xref, LLDeck_##type* pile) {     \
    if (pile == NULL || pile->size == 0) return false;          \
    *xref = &((pile->End)->data);                               \
    return true;                                                \
}                                                               \
                                                                \
inline void subStart_LLDeck_##type (LLDeck_##type* pile){       \
    /*if (pile == NULL || pile->size == 0) return false;*/      \
    if (pile->Start->next != NULL){ /* size > 1 */              \
        pile->Start = pile->Start->next;                        \
        free(pile->Start->prev);                                \
        pile->Start->prev = NULL;                               \
    } else { /* size == 1 */                                    \
        free(pile->Start);                                      \
        pile->Start = NULL;                                     \
        pile->End = NULL;                                       \
    }                                                           \
    (pile->size)--;                                             \
    /*return true;*/                                            \
}                                                               \
                                                                \
inline void subEnd_LLDeck_##type (LLDeck_##type* pile){         \
    /*if (pile == NULL || pile->size == 0) return false;*/      \
    if (pile->End->prev != NULL){ /* size > 1 */                \
        pile->End = pile->End->prev;                            \
        free(pile->End->next);                                  \
        pile->End->next = NULL;                                 \
    } else { /* size == 1 */                                    \
        free(pile->End);                                        \
        pile->Start = NULL;                                     \
        pile->End = NULL;                                       \
    }                                                           \
    (pile->size)--;                                             \
    /*return true;*/                                            \
}                                                               \
                                                                \
inline void addStart_LLDeck_##type (LLDeck_##type* pile){       \
    LLNode_##type* new_start = zalloc(sizeof( LLNode_##type )); \
    assert(pile != NULL);                                       \
    new_start->next = pile->Start;                              \
    new_start->prev = NULL;                                     \
    if (pile->Start != NULL) pile->Start->prev = new_start;     \
    (pile->Start) = new_start;                                  \
    (pile->size)++;                                             \
    if (pile->size == 1) pile->End = pile->Start;               \
}                                                               \
                                                                \
inline void addEnd_LLDeck_##type (LLDeck_##type* pile){         \
    LLNode_##type* new_end = zalloc(sizeof( LLNode_##type ));   \
    assert(pile != NULL);                                       \
    new_end->next = NULL;                                       \
    new_end->prev = pile->End;                                  \
    if (pile->End != NULL) pile->End->next = new_end;           \
    (pile->End) = new_end;                                      \
    (pile->size)++;                                             \
    if (pile->size == 1) pile->Start = pile->End;               \
}                                                               \
                                                                \
bool popStart_LLDeck_##type (type *xref, LLDeck_##type* pile){  \
    if (pile == NULL || pile->size == 0) return false;          \
    assert(xref != NULL);                                       \
    *xref = pile->Start->data;                                  \
    subStart_LLDeck_##type (pile);                              \
    return true;                                                \
}                                                               \
                                                                \
bool popEnd_LLDeck_##type (type *xref, LLDeck_##type* pile) {   \
    if (pile == NULL || pile->size == 0) return false;          \
    assert(xref != NULL);                                       \
    *xref = pile->End->data;                                    \
    subEnd_LLDeck_##type (pile);                                \
    return true;                                                \
}                                                               \
                                                                \
void pushStart_LLDeck_##type (type *xref, LLDeck_##type* pile) {\
    addStart_LLDeck_##type (pile);                              \
    assert(xref != NULL);                                       \
    (pile->Start)->data = *xref;                                \
}                                                               \
                                                                \
void pushEnd_LLDeck_##type (type *xref, LLDeck_##type* pile) {  \
    addEnd_LLDeck_##type (pile);                                \
    assert(xref != NULL);                                       \
    (pile->End)->data = *xref;                                  \
}

#endif /* DECKTYPE_H */

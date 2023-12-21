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
;*//* ________________________________________________________________

DEFINE_CIRCARRAY(type, CA_size) circular array of size CA_size

DEFINE_DECK(type) Doubly Linked List Macro push or pop from start or end

somthing

#include "DeckType.h"
DEFINE_DECK(float64_t)
#undef DEFINE_DECK

somthing

Deck_float64_t* pile = New_Deck_float64_t();

and stuff

;*//* ____________________________________________________#includes */

// #ifndef DECKTYPE_H
// #define DECKTYPE_H

#define DEFINE_DECK(type)                                              \
                                                                       \
/* _________________________________________________Data Structures */ \
    typedef struct LLNode_##type {                                     \
        type data;                                                     \
        struct LLNode_##type* next;                                    \
        struct LLNode_##type* prev;                                    \
    } LLNode_##type;                                                   \
                                                                       \
    typedef struct Deck_##type {                                       \
        uint64_t size;                                                 \
        struct LLNode_##type* Start;                                   \
        struct LLNode_##type* End;                                     \
    } Deck_##type;                                                     \
                                                                       \
/* ___________________________________________Function Declarations */ \
    /* need to test if makeheaders.c can detect and declare these */   \
    void popStart_Deck_##type (type *xref, Deck_##type* pile);         \
    void pushStart_Deck_##type (type *xref, Deck_##type* pile);        \
    void popEnd_Deck_##type (type *xref, Deck_##type* pile);           \
    void pushEnd_Deck_##type (type *xref, Deck_##type* pile);          \
                                                                       \
/* _____________________________________________Helper Declarations */ \
    /* need to test if makeheaders.c can detect and declare these */   \
                                                                       \
/* ____________________________________________Deck Implementation */  \
                                                                       \
    void popStart_Deck_##type (type *xref, Deck_##type* pile) {        \
        assert(pile != NULL);                                          \
        assert(pile->size > 0);                                        \
        LLNode_##type* tmp = pile->Start;                              \
        if (xref != NULL){                                             \
            *xref = tmp->data;}                                        \
        (pile->Start) = (pile->Start)->next;                           \
        free(tmp);                                                     \
        (pile->size)--;                                                \
        if (pile->size == 0) pile->Start = NULL;                       \
        if (pile->size <= 1) pile->End = pile->Start;                  \
        /*return data_buf;*/                                           \
    }                                                                  \
                                                                       \
    void popEnd_Deck_##type (type *xref, Deck_##type* pile) {          \
        assert(pile != NULL);                                          \
        assert(pile->size > 0);                                        \
        LLNode_##type* tmp = pile->End;                                \
        if (xref != NULL){                                             \
            *xref = tmp->data;}                                        \
        (pile->End) = (pile->End)->prev;                               \
        free(tmp);                                                     \
        (pile->size)--;                                                \
        if (pile->size == 0) pile->Start = NULL;                       \
        if (pile->size <= 1) pile->End = pile->Start;                  \
    }                                                                  \
                                                                       \
    void pushStart_Deck_##type (type *xref, Deck_##type* pile) {       \
        assert(pile != NULL);                                          \
        LLNode_##type* new_start = zalloc(sizeof( LLNode_##type ));    \
        if (xref != NULL){                                             \
            new_start->data = *xref; }                                 \
        new_start->next = pile->Start;                                 \
        (pile->Start) = new_start;                                     \
        (pile->size)++;                                                \
        if (pile->size <= 1) pile->End = pile->Start;                  \
    }                                                                  \
                                                                       \
    void pushEnd_Deck_##type (type *xref, Deck_##type* pile) {         \
        assert(pile != NULL);                                          \
        LLNode_##type* new_end = zalloc(sizeof( LLNode_##type ));      \
        if (xref != NULL){                                             \
            new_end->data = *xref; }                                   \
        new_end->prev = pile->End;                                     \
        (pile->End) = new_end;                                         \
        (pile->size)++;                                                \
        if (pile->size <= 1) pile->Start = pile->End;                  \
    }                                                                  \
                                                                       \
/* ___________________________________________Helper Implementation */ \

// #endif /* DECKTYPE_H */

/* ________________________________________________________________ */


// #ifndef CATYPE_H
// #define CATYPE_H

#define DEFINE_CIRCARRAY(type, CA_size)                                \
/* CA_size 256 works */                                                \
/* _________________________________________________Data Structures */ \
typedef struct CA_##type {                                             \
    type data[CA_size];                                                \
    uint8_t size;                                                      \
    uint8_t start_offset;                                              \
    uint8_t end_offset;                                                \
} CA_##type;                                                           \
                                                                       \
/* ___________________________________________Function Declarations */ \
                                                                       \
void popStart_CA_##type (type *xref, CA_##type *deque);                \
void pushStart_CA_##type(type *xref, CA_##type *deque);                \
void popEnd_CA_##type (type *xref, CA_##type *deque);                  \
void pushEnd_CA_##type(type *xref, CA_##type *deque);                  \
                                                                       \
/* ________________________________________Function Implementations */ \
                                                                       \
void pushStart_CA_##type(type *xref, CA_##type *deque) {               \
    assert(deque->size < CA_size);                                     \
    deque->start_offset =                                              \
        (deque->start_offset - 1 + CA_size) % CA_size;                 \
    deque->data[deque->start_offset] = *xref;                          \
    deque->size++;                                                     \
}                                                                      \
                                                                       \
void popStart_CA_##type (type *xref, CA_##type *deque) {               \
    assert(deque->size > 0);                                           \
    if (xref != NULL){                                                 \
        *xref = deque->data[deque->start_offset];}                     \
    deque->start_offset = (deque->start_offset + 1) % CA_size;         \
    deque->size--;                                                     \
}                                                                      \
                                                                       \
void pushEnd_CA_##type(type *xref, CA_##type *deque) {                 \
    assert(deque->size < CA_size);                                     \
    deque->data[deque->end_offset] = *xref;                            \
    deque->end_offset = (deque->end_offset + 1) % CA_size;             \
    deque->size++;                                                     \
}                                                                      \
                                                                       \
void popEnd_CA_##type (type *xref, CA_##type *deque) {                 \
    assert(deque->size > 0);                                           \
    deque->end_offset = (deque->end_offset                             \
                        - 1 + CA_size) % CA_size;                      \
    if (xref != NULL){                                                 \
        *xref = deque->data[deque->end_offset];}                       \
    deque->size--;                                                     \
};                                                                     \

// #endif /* CATYPE_H */

/* ________________________________________________________________ */
// CA_size decides how big a grocery list we want to have before we go
// to to he store
// 
// Developers should only need the type they are working with and the
// pointer to the COA_##type and we will provide:
// size pushstart popstart pushend popend functions from the
// underlying structures above.
// 
//
/* ________________________________________________________________ */
// might need these:
// typedef struct COA_##type { size Head }
// typedef struct Deck_##type { size Start End
// typedef struct LLNode_##type { data next prev
// typedef struct CA_##type { data[CA_size] size start_offset end_offset                                          
//
// struct CA_##type get allocated in llnode
// free() with pop() on 1 element remaining.
// malloc() with push() to a full deck.
// 
/* ________________________________________________________________ */

#define DEFINE_COD(Deck_CA_type, CA_type, type, CA_size)               \
                                                                       \
    typedef struct COA_##type {                                        \
        uint64_t size; /* not the num of nodes but num of elems */     \
        struct Deck_CA_type * pile;                                    \
    } COA_##type;                                                      \
                                                                       \
void COA_popStart_##type(type *xref, COA_##type* cluster);             \
void COA_pushStart_##type(type *xref, COA_##type* cluster);            \
void COA_popEnd_##type(type *xref, COA_##type* cluster);               \
void COA_pushEnd_##type(type *xref, COA_##type* cluster);              \
COA_##type* New_COA_##type ();                                         \
                                                                       \
void COA_popStart_##type(type *xref, COA_##type* cluster);             \
    assert(cluster->size > 0);                                         \
    if (cluster->pile->Start->data->size == 0)                         \
        popStart_##Deck_CA_type(NULL, cluster->pile);                  \
    popStart_##CA_type(xref, cluster->pile->Start->data );             \
    cluster->size--;                                                   \
}                                                                      \
                                                                       \
void COA_popEnd_##type(type *xref, COA_##type* cluster);               \
    assert(cluster->size > 0);                                         \
    if (cluster->pile->End->data->size == 0)                           \
        popEnd_##Deck_CA_type(NULL, cluster->pile);                    \
    popEnd_##CA_type(xref, cluster->pile->End->data );                 \
    cluster->size--;                                                   \
}                                                                      \
                                                                       \
void COA_pushStart_##type(type *xref, COA_##type* cluster);            \
    if (cluster->pile->Start->data->size == CA_size)                   \
        pushStart_##Deck_CA_type(NULL, cluster->pile);                 \
    pushStart_##CA_type(xref, cluster->pile->Start->data );            \
    cluster->size++;                                                   \
}                                                                      \
                                                                       \
void COA_pushEnd_##type(type *xref, COA_##type* cluster);              \
    if (cluster->pile->End->data->size == CA_size)                     \
        pushEnd_##Deck_CA_type(NULL, cluster->pile);                   \
    pushEnd_##CA_type(xref, cluster->pile->End->data);                 \
    cluster->size++;                                                   \
}                                                                      \
                                                                       \
COA_##type* New_COA_##type () {                                        \
    COA_##type* cluster = zalloc(sizeof(COA_##type));                  \
    cluster->pile = zalloc(sizeof(Deck_CA_type));                      \
    pushStart_##Deck_CA_type (NULL, cluster->pile);                    \
    return cluster;                                                    \
}                                                                      \
                                                                       \
/* realize consolodation */                                            \
// CA_##type* CA_zerobuf_##type = New_CA_##type();

#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

#define CONCAT_HELPER(x, y) x##y
#define CONCAT(x, y) CONCAT_HELPER(x, y)

#define DEFINE_SETnUSEvars_HELPER(type, CA_size)                       \
    #define CA_type STRINGIFY(CA_##type)                               \
    #define Deck_CA_type STRINGIFY(Deck_CA_##type)                     \
    /* DEFINE_COD defines funcs that operate on Deck_CA_type */        \
    DEFINE_COD(Deck_CA_type, CA_type, type, CA_size)                   \
    #undef CA_type                                                     \
    #undef Deck_CA_type

#define DEFINE_SETnUSEvars(type, CA_size) \
    DEFINE_SETnUSEvars_HELPER(type, CA_size)

#define DEFINE_COA(type, CA_size)                                      \
    /* DEFINE_CIRCARRAY defines CA_type for that type */               \
    DEFINE_CIRCARRAY(type, CA_size)                                    \
    /* DEFINE_DECK defines Deck_CA_type for that type */               \
    DEFINE_DECK(CA_##type)                                             \
    /* DEFINE_COD correctly called in this macro */                    \

//    DEFINE_SETnUSEvars(type, CA_size)




#define DECLARE_STRUCT_TYPE(name) typedef struct name##_s name##_t

DECLARE_STRUCT_TYPE(g_object); // Outputs: typedef struct g_object_s g_object_t;

The solution to this is as easy as in the STR case above. You will have to expand the macro in two steps. Typically you could define a generic macro to glue anything together:

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)

file COA.h:

    #define DEFINE_COA(type, CA_size)                                      \
        /* DEFINE_CIRCARRAY defines CA_type for that type */               \
        DEFINE_CIRCARRAY(type, CA_size)                                    \
        /* DEFINE_DECK defines Deck_CA_type for that type */               \
        DEFINE_DECK(CA_##type)                                             \
        /* DEFINE_COD defines funcs that operate on Deck_CA_type */        \

        // DEFINE_COD(type)                                             \


    #define DEFINE_COD(type)                                               \
                                                                           \
        typedef struct COA_##type {                                        \
            uint64_t size; /* not the num of nodes but num of elems */     \
            struct Deck_CA_##type * pile;                                  \
        } COA_##type;                                                      \
                                                                           \
    void COA_popStart_##type(type *xref, COA_##type* cluster);             \
    void COA_pushStart_##type(type *xref, COA_##type* cluster);            \
    void COA_popEnd_##type(type *xref, COA_##type* cluster);               \
    void COA_pushEnd_##type(type *xref, COA_##type* cluster);              \
    COA_##type* New_COA_##type ();                                         \



file DequeArray.c:

    #include "COA.h"
    // DEFINE_CIRCARRAY(uint8_t, 95) //(152*5)/8 // 4x content to metadata for 64 bit addresses
    DEFINE_COA(uint8_t, 40) //(152*5)/8 // 4x content to metadata for 64 bit addresses
    // #undef DEFINE_DECK

    /* __________________________________________Helper Implementations */
    // static functions are unavailable outside the file they are defined.
    /* _____________________________________________________RUN PROGRAM */
    int64_t main(int argc, char **argv){// *argv++ is *((char **)(argv++))
        CA_uint8_t* deque = zalloc(sizeof( CA_uint8_t ));
        uint8_t* intbufptr = (uint8_t*)zalloc(sizeof(uint8_t));
        // Pushing values onto the deque
        *intbufptr = 42;
        CA_pushStart_uint8_t(intbufptr, deque);
        *intbufptr = 17;
        CA_pushEnd_uint8_t(intbufptr, deque);
        *intbufptr = 33;
        CA_pushStart_uint8_t(intbufptr, deque);

        // Popping values from the deque
        CA_popStart_uint8_t(intbufptr, deque);
        printf("Popped from start: %u\n", *intbufptr);
        CA_popEnd_uint8_t(intbufptr, deque);
        printf("Popped from end: %u\n", *intbufptr);
        CA_popEnd_uint8_t(intbufptr, deque);
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

[owner@nixos:~/sync/BigIdeas/minimus]$ ./DequeArray.c 

    Popped from start: 33
    Popped from end: 17
    Popped from end: 42
    sizeof CA_uint8_t: 43
    sizeof LLNode_CA_uint8_t: 64
    sizeof Deck_CA_uint8_t: 24


When we uncomment "// DEFINE_COD(type) \" in COA.h we get:

    error: declaration expected
    



#define STRINGIFY_HELPER(x) #x
#define STRINGIFY(x) STRINGIFY_HELPER(x)

#define CONCAT_HELPER(x, y) x##y
#define CONCAT(x, y) CONCAT_HELPER(x, y)


#define DEFINE_COA(type, CA_size)                                      \
    /* DEFINE_CIRCARRAY defines CA_type for that type */               \
    DEFINE_CIRCARRAY(type, CA_size)                                    \
    /* DEFINE_DECK defines Deck_CA_type for that type */               \
    DEFINE_DECK(CA_##type)                                             \
    /* DEFINE_COD defines funcs that operate on Deck_CA_type */        \
    DEFINE_COD(Deck_CA_type, CA_type, type, CA_size)                   \


before using them in the macro:

write some macros in the defineCOA to set some macro variable to feed into define_COD
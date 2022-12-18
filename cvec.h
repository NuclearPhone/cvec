#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifndef VECTOR_DEFAULT_CAPACITY
#define VECTOR_DEFAULT_CAPACITY 32
#endif

#ifndef VECTOR_DEFAULT_GROWTH_RATE
#define VECTOR_DEFAULT_GROWTH_RATE 1.5
#endif

// forces the use of a semicolon at the end of a macro
#define VECTOR_REQUIRE_SEMICOLON (void)(0)

#define VECTOR(typename)           \
    struct {                       \
        typename* ptr;             \
        uint32_t capacity, length; \
    }

#define VECTOR_NEW(vector)                        \
    (vector).ptr = malloc(sizeof(*(vector).ptr)); \
    (vector).capacity = VECTOR_DEFAULT_CAPACITY;  \
    (vector).length = 0;                          \
    VECTOR_REQUIRE_SEMICOLON

#define VECTOR_DESTROY(vector) \
    if ((vector).ptr)          \
        free((vector).ptr);    \
    VECTOR_REQUIRE_SEMICOLON

#define VECTOR_FIT(vector, fit_to)                                        \
    while ((vector).capacity < fit_to) {                                  \
        (vector).capacity *= VECTOR_DEFAULT_GROWTH_RATE;                  \
    };                                                                    \
    (vector).ptr =                                                        \
        realloc((vector).ptr, sizeof(*(vector).ptr) * (vector).capacity); \
    VECTOR_REQUIRE_SEMICOLON

#define VECTOR_PUSH(vector, value)           \
    VECTOR_FIT(vector, (vector).length + 1); \
    (vector).ptr[(vector).length] = value;   \
    (vector).length += 1;                    \
    VECTOR_REQUIRE_SEMICOLON

#define VECTOR_POP(vector) ((vector).ptr[--(vector).length])
#define VECTOR_GET(vector, idx) ((vector).ptr[idx])
#define VECTOR_GETPTR(vector, idx) &((vector).ptr[idx])

#define VECTOR_FOREACH(vector, idx, block)                 \
    for (uint32_t idx = 0; idx < (vector).length; idx++) { \
        block                                              \
    }                                                      \
    VECTOR_REQUIRE_SEMICOLON

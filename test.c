#include "testc/test.h"
#include "cvec.h"

const char* basic_vector_test() {
    VECTOR(int) vec;

    VECTOR_NEW(vec);

    VECTOR_PUSH(vec, 2);
    int x = VECTOR_POP(vec);

    if (x != 2)
        return TESTC_BASIC_ERR;

    VECTOR_DESTROY(vec);
    return NULL;
}

typedef VECTOR(int) int_vec;

const char* ptr_test() {
    int_vec vec;

    {
        int_vec* vec_ptr = &vec;
        VECTOR_NEW(*vec_ptr);
        VECTOR_PUSH(*vec_ptr, 2);
    }

    int out = VECTOR_POP(vec);

    if (out != 2)
        return TESTC_BASIC_ERR;

    VECTOR_DESTROY(vec);

    return NULL;
}

const char* vec_foreach() {
    int_vec vec;

    VECTOR_NEW(vec);

    for (int i = 0; i < 3; i++) {
        VECTOR_PUSH(vec, i);
    }

    VECTOR_FOREACH(vec, i, { *VECTOR_GETPTR(vec, i) += 1; });

    for (int i = 0; i < 3; i++)
        if (VECTOR_GET(vec, i) != i + 1)
            return TESTC_BASIC_ERR;

    VECTOR_DESTROY(vec);

    return NULL;
}

const test_t tests[] = {
    (test_t){
        .ptr = basic_vector_test,
        .name = "basic vector test",
        .desc = "",
    },

    (test_t){
        .ptr = ptr_test,
        .name = "indirection test",
        .desc = "",
    },

    (test_t){
        .ptr = vec_foreach,
        .name = "foreach test",
        .desc = "",
    },
};

extern int main() {
    for (uint32_t i = 0; i < sizeof(tests) / sizeof(test_t); i++)
        execute_test(tests[i]);
}

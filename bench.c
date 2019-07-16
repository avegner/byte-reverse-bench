#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include <reverse.h>

const uint32_t g_bench_iters = 1000000LU;

bool test_reverse_byte_impl(reverse_byte_impl_t impl) {
    static uint8_t const test_data[][2] = {
        {0x80, 0x01}, {0xFF, 0xFF}, {0x00, 0x00}, {0xAE, 0x75}, {0x5A, 0x5A}};

    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        if (test_data[i][0] != impl(test_data[i][1])) {
            return false;
        }
    }

    return true;
}

double benchmark_reverse_byte_impl(reverse_byte_impl_t impl, uint32_t iters) {
    clock_t start = clock(), end;

    for (uint32_t i = 0; i < iters; i++) {
        for (uint16_t val = 0; val < 0x100; val++) {
            (void)impl((uint8_t)val);
        }
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

void print_logf(char const *p_format, ...) {
    va_list va;
    va_start(va, p_format);

    vfprintf(stderr, p_format, va);

    va_end(va);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    struct {
        reverse_byte_impl_t impl;
        char const *p_name;
    } impls[] = {
        {.impl = reverse_byte_loop, .p_name = "loop"},
        {.impl = reverse_byte_bitfield, .p_name = "bitfield"},
        {.impl = reverse_byte_small_table, .p_name = "small table"},
        {.impl = reverse_byte_big_table, .p_name = "big table"},
        {.impl = reverse_byte_swap, .p_name = "swap"},
        {.impl = reverse_byte_magic, .p_name = "magic"},
#ifdef __clang__
        {.impl = reverse_byte_builtin, .p_name = "builtin"},
#endif
    };

    for (size_t i = 0; i < sizeof(impls) / sizeof(impls[0]); i++) {
        print_logf("--------- %s ----------\n", impls[i].p_name);
        print_logf("test: ");
        assert(true == test_reverse_byte_impl(impls[i].impl));
        print_logf("OK\n");

        print_logf("benchmark: ");
        double elapsed =
            benchmark_reverse_byte_impl(impls[i].impl, g_bench_iters);
        print_logf("%lf s\n", elapsed);
    }

    return 0;
}

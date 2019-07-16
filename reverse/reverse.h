#pragma once
#ifndef REVERSE_H
#define REVERSE_H

#include <stdint.h>

typedef uint8_t (*reverse_byte_impl_t)(uint8_t byte);

uint8_t reverse_byte_loop(uint8_t byte);
uint8_t reverse_byte_bitfield(uint8_t byte);
uint8_t reverse_byte_swap(uint8_t byte);
uint8_t reverse_byte_small_table(uint8_t byte);
uint8_t reverse_byte_big_table(uint8_t byte);
uint8_t reverse_byte_magic(uint8_t byte);
#ifdef __clang__
uint8_t reverse_byte_builtin(uint8_t byte);
#endif

#endif //  REVERSE_H

#ifndef _PRINT_BYTES_H
#define _PRINT_BYTES_H

#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <printf.h>
#include <stdlib.h>

int register_printf_byte(void);

int printf_byte_arginfo(const struct printf_info *info,
	    size_t n, int *argtypes);

int printf_arginf_sz_byte(const struct printf_info *info,
	    size_t n, int *argtypes, int *size);

int printf_byte(FILE*stream, const struct printf_info *info,
	    const void *const *args);

char*build_byte(char*arg);

int printf_arginf_sz_binary(const struct printf_info *info, size_t n,
	int *argtypes);

int printf_binary(FILE *stream, const struct printf_info *info, const void *const *args);

char *build_bits(char*arg);

#endif

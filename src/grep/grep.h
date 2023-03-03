// Created by Brie Tammera on 2/9/23.

#ifndef C3_SIMPLEBASHUTILS_0_GREP_H
#define C3_SIMPLEBASHUTILS_0_GREP_H

#include <stdbool.h>

#include "vector.h"

#define E_FLAG 0b1
#define I_FLAG 0b10
#define V_FLAG 0b100
#define C_FLAG 0b1000
#define L_FLAG 0b10000
#define N_FLAG 0b100000
#define H_FLAG 0b1000000
#define S_FLAG 0b10000000
#define F_FLAG 0b100000000
#define O_FLAG 0b1000000000
#define FILE_OUTPUT 0b10000000000

/*=======================HELPING FUNCTIONS=========================*/
void usage(void);
void parse_command(int argc, char *const argv[]);

/*========================PRINT FUNCTIONS===========================*/
void print_string(u_int64_t line, const char *filename, char *buffer);
void comparison(FILE *, char *);

/*===============FUNCTIONS FOR PATTERN COMPILATION==================*/
void add_pattern(char *);
void read_file(char *);
void compile_pattern();
void free_patterns();

#endif  //       C3_SIMPLEBASHUTILS_0_GREP_H

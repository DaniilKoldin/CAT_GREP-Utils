// Created by Brie Tammera on 2/3/23.

#ifndef C3_SIMPLEBASHUTILS_0_CAT_H
#define C3_SIMPLEBASHUTILS_0_CAT_H

#define N_FLAG 0b1
#define B_FLAG 0b10
#define V_FLAG 0b10000
#define T_FLAG 0b00100
#define E_FLAG 0b01000
#define S_FLAG 0b100000

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void parse_command(int argc, char *const argv[]);

void write_file(FILE *file);

void usage(void);

void change_line(unsigned char flag, char *const buffer);

#endif  //       C3_SIMPLEBASHUTILS_0_CAT_H

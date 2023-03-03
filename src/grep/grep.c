// Created by Brie Tammera on 2/9/23.

#include "grep.h"

#include <getopt.h>

#include "vector.h"

int cflags = REG_NEWLINE | REG_EXTENDED;

static string_vector patt_vec = {0, NULL};

extern bool is_pattern_need;
extern unsigned short mode;
static regex_t regex = {0};
static regmatch_t matches = {0};

/*=======================HELPING FUNCTIONS=========================*/
void usage(void) {
  fprintf(stderr,
          "usage: grep [-ivclnhso] [-e pattern] [-f file]\n"
          "\t[--null] [pattern] [file ...]\n");
  exit(EXIT_FAILURE);
}

void parse_command(int argc, char *const argv[]) {
  int opt = 0;
  while ((opt = getopt(argc, argv, "e:f:ivcnhsol")) != -1) {
    switch (opt) {
      case 'e':
        mode |= E_FLAG;
        add_pattern(optarg);
        is_pattern_need = 0;
        break;
      case 'f':
        mode |= F_FLAG;
        read_file(optarg);
        is_pattern_need = 0;
        break;
      case 'i':
        mode |= I_FLAG;
        cflags |= REG_ICASE;
        break;
      case 'c':
        mode |= C_FLAG;
        break;
      case 'o':
        mode |= O_FLAG;
        cflags &= ~REG_NOSUB;
        break;
      case 'v':
        mode |= V_FLAG;
        break;
      case 'l':
        mode |= L_FLAG;
        break;
      case 'n':
        mode |= N_FLAG;
        break;
      case 'h':
        mode |= H_FLAG;
        break;
      case 's':
        mode |= S_FLAG;
        break;
      default:
      case '?':
        usage();
        break;
    }
  }  // switch
}

/*========================PRINT FUNCTIONS===========================*/
void print_string(unsigned int line, const char *filename, char *buffer) {
  mode &FILE_OUTPUT ? printf("%s:", filename) : 0;
  mode &N_FLAG ? printf("%u:", line) : 0;
  if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
  printf("%s\n", buffer);
}

void comparison(FILE *file, char *filename) {
#define MAX_SIZE 2048
  char string[MAX_SIZE] = {0};
  char buffer[MAX_SIZE] = {0};

  size_t line = 0;
  size_t count_equ_lines = 0;

  while (!feof(file) && fgets(string, MAX_SIZE - 1, file)) {
    char *temp = string;
    ++line;

    int reg_res = regexec(&regex, temp, 1, &matches, 0);
    if (reg_res && (mode & V_FLAG)) {
#ifndef __APPLE__
      if (!(mode & (C_FLAG | L_FLAG | O_FLAG))) {
#else
      if (!(mode & (C_FLAG | L_FLAG))) {
#endif
        print_string(line, filename, string);
      }
      ++count_equ_lines;
    } else if (!reg_res && !(mode & O_FLAG)) {
      !(mode & (V_FLAG | C_FLAG | L_FLAG))
          ? print_string(line, filename, string)
          : 0;
      !(mode & V_FLAG) ? ++count_equ_lines : 0;
    } else if (!reg_res) {
#ifndef __APPLE__
      if (mode & V_FLAG) {
        memset(string, 0, strlen(string));
        continue;
      }
      ++count_equ_lines;
#endif
      while (!reg_res) {
        mode &V_FLAG ? strncpy(buffer, temp, string + matches.rm_so - temp)
                     : strncpy(buffer, temp + matches.rm_so,
                               matches.rm_eo - matches.rm_so);

        !(mode & (C_FLAG | L_FLAG)) ? print_string(line, filename, buffer) : 0;
        temp += matches.rm_so + 1;
        reg_res = regexec(&regex, temp, 1, &matches, 0);
        memset(buffer, 0, strlen(buffer));
      }
      /*THE LAST PART OF STRING*/
      if (mode & V_FLAG) {
        strncpy(buffer, temp, strlen(temp) - 1);
        !(mode & (C_FLAG | L_FLAG)) ? print_string(line, filename, buffer) : 0;
      }
    }
    memset(buffer, 0, strlen(buffer));
    memset(string, 0, strlen(string));
  }
#ifndef __APPLE__
  if ((mode & C_FLAG) && (mode & L_FLAG)) {
    if (count_equ_lines) printf("%s\n", filename);
    return;
  }
#endif

  mode &C_FLAG && ((mode & L_FLAG) || (mode & FILE_OUTPUT))
      ? printf("%s:%lu\n", filename, count_equ_lines)
  : mode &C_FLAG                   ? printf("%lu\n", count_equ_lines)
  : mode &L_FLAG &&count_equ_lines ? printf("%s\n", filename)
                                   : 0;
}

/*===============FUNCTIONS FOR PATTERN COMPILATION==================*/
void add_pattern(char *pattern) { vector_push_back(&patt_vec, pattern); }

void read_file(char *file_name) {
  FILE *file;
  if ((file = fopen(file_name, "r")) == NULL) {
    !(mode & S_FLAG) ? warn("%s", file_name) : 0;
    return;
  }
  char buffer[MAX_SIZE];
  while (!feof(file) && fgets(buffer, MAX_SIZE - 1, file)) {
    if (buffer[strlen(buffer) - 1] == '\n') buffer[strlen(buffer) - 1] = '\0';
    vector_push_back(&patt_vec, buffer);
  }
  fclose(file);
}

void compile_pattern() {
  char reg[(MAX_SIZE + 3) * patt_vec.size];
  strcpy(reg, "(\0");
  for (size_t i = 0; i < patt_vec.size - 1; ++i) {
    strcat(reg, patt_vec.elem[i]);
    strcat(reg, ")|(");
  }
  strcat(reg, patt_vec.elem[patt_vec.size - 1]);
  strcat(reg, ")");
  if (regcomp(&regex, reg, cflags)) {
    warn("UNFORGIVABLE PATTERN");
    exit(EXIT_FAILURE);
  }
#undef MAX_SIZE
}

void free_patterns() { regfree(&regex); }
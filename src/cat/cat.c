//  Created by Brie Tammera on 2/3/23.

#include "cat.h"

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

static unsigned char mode = 0;

void usage(void) {
  fprintf(stderr, "usage: s21_cat [-benstv] [file ...]\n");
  exit(1);
}

void parse_command(int argc, char *const argv[]) {
  int opt = 0;
  int opt_index = 0;
  static struct option long_options[] = {
#ifndef __APPLE__
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
#endif
      {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "bnetvsTE", long_options,
                            &opt_index)) != -1) {
    switch (opt) {
      case 'b':
        mode |= B_FLAG;
        break;
      case 'n':
        mode |= N_FLAG;
        break;
      case 'v':
        mode |= V_FLAG;
        break;
      case 't':
        mode |= T_FLAG;  //  when using implements -v
        mode |= V_FLAG;
        break;
      case 'T':
        mode |= T_FLAG;
        break;
      case 'e':
        mode |= E_FLAG;  //  when using implements -v
        mode |= V_FLAG;
        break;
      case 'E':
        mode |= E_FLAG;
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

void write_file(FILE *file) {
#define MAX_SIZE 512
  bool enter_flag = 0;
  unsigned int line = 0;
  char buffer[MAX_SIZE];
  while (!feof(file) && fgets(buffer, MAX_SIZE / 2, file)) {
    if (mode & S_FLAG && buffer[0] == '\n' && !enter_flag)
      enter_flag = true;
    else if (mode & S_FLAG && buffer[0] == '\n' && enter_flag) {
      continue;
    } else if (buffer[0] != '\n')
      enter_flag = false;

    if ((mode & N_FLAG && !(mode & B_FLAG)) ||
        (mode & B_FLAG && buffer[0] != '\n'))
      fprintf(stdout, "%6u\t", ++line);

    if (mode & (T_FLAG & ~V_FLAG)) {
      change_line(0, buffer);
    }

    if (mode & (E_FLAG & ~V_FLAG)) {
      change_line(1, buffer);
    }

    if (mode & V_FLAG) {
      char *pos = buffer;
      char temp[MAX_SIZE];
      temp[0] = '\0';
      for (size_t i = 0; i < strlen(buffer); ++i, ++pos) {
        int ch = toascii(*pos);
        if (!isascii(*pos)) {
          strcat(temp, "M-");
          sprintf(temp + strlen(temp), "%c", toascii(ch));
        } else if (iscntrl(ch) && *pos != '\n' && *pos != '\t') {
          strcat(temp, "^");
          if (ch == '\177')
            strcat(temp, "?");
          else
            sprintf(temp + strlen(temp), "%c", ch + 64);
        } else
          sprintf(temp + strlen(temp), "%c", ch);
      }
      strcpy(buffer, temp);
    }
    fprintf(stdout, "%s", buffer);
  }
}

void change_line(unsigned char flag, char *const buffer) {
  char *prev_pos = buffer;
  char *pos = buffer;
  char temp[MAX_SIZE];
  *temp = '\0';
  while ((pos = strchr(pos, flag ? '\n' : '\t')) != NULL) {
    pos[0] = '\0';
    ++pos;
    strcat(temp, prev_pos);
    strcat(temp, flag ? "$\n" : "^I");
    prev_pos = pos;
  }
  strcat(temp, prev_pos);
  strcpy(buffer, temp);
#undef MAX_SIZE
}

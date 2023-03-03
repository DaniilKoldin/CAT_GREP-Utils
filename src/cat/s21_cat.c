//  Created by Brie Tammera on 2/3/23.

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./cat.h"

int main(int argc, char* const argv[]) {
  FILE* file;
  parse_command(argc, argv);
  argv += optind;
  do {
    if (*argv) {
      if (!strcmp(*argv, "-")) {
        file = stdin;
      } else if ((file = fopen(*argv, "r")) == NULL) {
        warn("%s", *argv);
        ++argv;
        continue;
      }
      write_file(file);
      if (file != stdin)
        fclose(file);
      else
        clearerr(file);
    }
    ++argv;
  } while (*argv);
  return 0;
}

//  Created by kamputer on 2/13/23.

#include <unistd.h>

#include "./grep.h"
#include "includes.h"

bool is_pattern_need = 1;
unsigned short mode = 0;

int main(int argc, char *const argv[]) {
  FILE *file;
  argc == 1 ? usage() : 0;
  parse_command(argc, argv);
  argv += optind;
  argc -= optind;
  if (is_pattern_need) {
    add_pattern(argv[0]);
    is_pattern_need = 0;
    --argc;
    ++argv;
  }
  if (argc > 1 && !(mode & H_FLAG)) mode |= FILE_OUTPUT;
  compile_pattern();
  !argc ? file = stdin : 0;
  do {
    if (*argv) {
      if (!strcmp(*argv, "-")) {
        file = stdin;
      } else if ((file = fopen(*argv, "r")) == NULL) {
        !(mode & S_FLAG) ? warn("%s", *argv) : 0;
        ++argv;
        --argc;
        continue;
      }
    }
    comparison(file, file != stdin ? (*argv) : "stdin");
    if (file != stdin)
      fclose(file);
    else
      clearerr(file);
    argc ? --argc : 0;
    ++argv;
  } while (argc);
  free_patterns();
  return 0;
}

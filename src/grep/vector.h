//  Created by kamputer on 2/14/23.

#ifndef C3_SIMPLEBASHUTILS_0_SRC_GREP_VECTOR_H_
#define C3_SIMPLEBASHUTILS_0_SRC_GREP_VECTOR_H_

#include "includes.h"

typedef struct string_vector {
  size_t size;
  char **elem;
} string_vector;

void vector_delete(string_vector *vec);

string_vector * vector_push_back(string_vector *vec, const char *data);


#endif //  C3_SIMPLEBASHUTILS_0_SRC_GREP_VECTOR_H_

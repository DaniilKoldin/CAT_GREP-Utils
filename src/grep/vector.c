//
// Created by kamputer on 2/14/23.
//

#include "vector.h"

void vector_delete(string_vector *vec) {
  if (!vec) return;
  for (size_t i = 0; i < vec->size; ++i) {
    free(vec->elem[i]);
  }
  free(vec->elem);
}

string_vector *vector_push_back(string_vector *vec, const char *data) {
  if (data) {
    char **new_elem =
        (char **)realloc(vec->elem, (vec->size + 1) * sizeof(char **));
    char *new_string = (char *)calloc(strlen(data) + 1, sizeof(char));
    if (!new_elem || !new_string) {
      vector_delete(vec);
      exit(EXIT_FAILURE);
    }
    vec->size += 1;
    vec->elem = new_elem;
    vec->elem[vec->size - 1] = new_string;
    strcpy((vec->elem)[vec->size - 1], data);
  }
  return vec;
}

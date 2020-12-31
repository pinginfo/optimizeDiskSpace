/*
    OptimizedDiskSpace allows to replace all duplicate files in one link to save disk space. 
    Copyright (C) 2020 Guillaume Pin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "vector.h"
#define DEFAULT_VECTOR_SIZE 8 
int vector_init(vector* v) {
  v->capacity = DEFAULT_VECTOR_SIZE; 
  v->length = 0;
  v->content = NULL;
  v->content = malloc(v->capacity  * sizeof(void*));
  if (v->content) { return 0; }
  else { return 1; }
}

int vector_length(vector* v, size_t* length) {
  *length = v->length;
  return 0;
}

int vector_push(vector* v, void* element) {
  if (v->length >= v->capacity) {
    v->capacity *= 2;
    v->content = realloc(v->content, sizeof(void*) * v->capacity);
  }
  v->content[v->length++] = element;
  return 0;
}

int vector_pop(vector* v, void** element) {
  if (v->length > 0) {
    *element = v->content[--v->length];
    v->content[v->length] = 0;
    return 0;
  } else {
    return 1;
  }
}

int vector_set(vector* v, size_t index, void* element) {
  if (v->length > index) {
    v->content[index] = element;
    return 0;
  } 
  return 1;
}

int vector_get(vector* v, size_t index, void** element) {
  if (v->length > index) {
    *element = v->content[index];
    return 0;
  }
  return 1;
}

int vector_remove(vector* v, size_t index) {
  size_t i;

  if (index < v->length--) {
    for (i = index; i < v->length; i++) { v->content[i] = v->content[i + 1]; }

  }
  return 0;
}

int vector_isEmpty(vector* v) {
  if (v->length == 0) {
    return 1;
  } else {
    return 0;
  }
}

int vector_forEach(vector* v, void (*f)(void*)) {
  size_t i;

  for (i = 0; i < v->length; i++) {
    (*f)(v->content[i]);
  }

  return 0;
}

int vector_free(vector* v) {
  if (v->content) {
    free(v->content);
    v->content = NULL;
  }
  return 0;
}

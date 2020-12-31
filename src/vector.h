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

#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>

typedef struct vector {
  void** content;
  int capacity;
  int length;
} vector;

int vector_init(vector* v);
int vector_length(vector* v, size_t* length);
int vector_push(vector* v, void* element);
int vector_pop(vector* v, void** element);
int vector_set(vector* v, size_t index, void* element);
int vector_get(vector* v, size_t index, void** element);
int vector_remove(vector* v, size_t index);
int vector_isEmpty(vector* v);
int vector_forEach(vector* v, void (*f)(void*));
int vector_free(vector* v);
#endif

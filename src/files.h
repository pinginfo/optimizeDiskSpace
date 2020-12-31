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

#ifndef FILES_H
#define FILES_H
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"

typedef struct infoFile {
  off_t size;
  char name[PATH_MAX];
  char path[PATH_MAX];
  ino_t inode;
} infoFile;

typedef struct duplicates {
  infoFile* file1;
  infoFile* file2;
} duplicates;

void getAllFiles(char* path, vector* v); 
void getAllDuplicates(vector* files, vector* duplicates);
int cmpInfoFile(infoFile p1, infoFile p2);
int cmpFiles(char* file1, char* file2);
void printDuplicate(void* item);
void optimizeSpace(void* item);
void free_file(void*item);
void free_duplicates(void* item);
#endif

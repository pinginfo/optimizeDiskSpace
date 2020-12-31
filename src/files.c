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

#include "files.h"

void getAllFiles(char* path, vector* v) {
  struct stat tmp;
  struct dirent *item;
  DIR *d;
  
  d = opendir(path);
  
  while(d != NULL && (item = readdir(d)) != NULL) {
    char* itemPath = malloc(sizeof(char) * PATH_MAX);
    snprintf(itemPath, PATH_MAX, "%s/%s", path, item->d_name);
    stat(itemPath, &tmp);
    if (S_ISREG(tmp.st_mode)) {
      infoFile* file = malloc(sizeof(infoFile));
      
      file->size = tmp.st_size;
      strncpy(file->name, item->d_name, PATH_MAX);
      strncpy(file->path, itemPath, PATH_MAX);
      file->inode = tmp.st_ino;
      
      vector_push(v, file);
    } else if (S_ISDIR(tmp.st_mode) && strcmp(item->d_name, ".") && strcmp(item->d_name, "..")) {
      getAllFiles(itemPath, v);
    }
    free(itemPath);
  }
  
  if (d == NULL) {
    perror("opendir");
    printf("error with : %s\n", path);
  } else { closedir(d); }
}

void getAllDuplicates(vector* files, vector* vecDuplicates) {
  while(!vector_isEmpty(files)) {
    int founded = 0;
    infoFile* file;
    size_t actualSize;
    vector_pop(files, (void**)&file);
    vector_length(files, &actualSize);
    
    for (size_t i = 0; i < actualSize; i++) {
      infoFile* filetmp; 
      vector_get(files, i, (void**)&filetmp);
      if (!cmpInfoFile(*file, *filetmp)) {
        duplicates* doubleFile = malloc(sizeof(duplicates));
        doubleFile->file1 = file;
        doubleFile->file2 = filetmp;
        vector_push(vecDuplicates, doubleFile);
        vector_remove(files, i--);
        vector_length(files, &actualSize);
        founded = 1;
      }
    }
    if (!founded) { free(file); }
  }
}

int cmpInfoFile(infoFile p1, infoFile p2) {
  if (strncmp(p1.name, p2.name, PATH_MAX) == 0 && p1.size == p2.size && p1.inode != p2.inode) {
    if (cmpFiles(p1.path, p2.path) == 0) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return 1;
  }
}

int cmpFiles(char* file1, char* file2) {
  char ch1, ch2;
  FILE* f1 = fopen(file1, "r");
  if (f1 == NULL) {
    perror("fopen");
    return 1;
  }
  FILE* f2 = fopen(file2, "r");
  if (f2 == NULL) {
    perror("fopen");
    return 1;
  }

  do {
    ch1 = fgetc(f1);
    ch2 = fgetc(f2);
    if (ch1 != ch2) { return 1; }
  } while (ch1 != EOF && ch2 != EOF);

  if (fclose(f1)) { perror("fclose"); }
  if (fclose(f2)) { perror("fclose"); }

  return 0;
}

void printDuplicate(void* item) {
  printf("\tfile1 = %s -> file2 = %s\n", ((duplicates *)item)->file1->path, ((duplicates *)item)->file2->path);
}

void optimizeSpace(void* item) {
  infoFile* file;
  infoFile* filetmp;
  file = ((duplicates *)item)->file1;
  filetmp = ((duplicates *)item)->file2;
  printf("Remove : %s\n", filetmp->path);
  if (unlink(filetmp->path)) {
    perror("unlink");
  }
  printf("Create link of %s in %s\n", file->path, filetmp->path);
  if (link(file->path, filetmp->path)) {
    perror("link");
  }
}

void free_file(void* item) {
  free(item);
}

void free_duplicates(void* item) {
  free_file(((duplicates *)item)->file1);
  free_file(((duplicates *)item)->file2);
  free(item);
}

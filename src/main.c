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
#include "files.h"

int main(int argc, char *argv[]) {
  int opt;
  vector vecFiles, vecDuplicates;
  size_t filesLength, duplicatesLength;
  
  if (argc == 1) {
    printf("Usage: %s <pathname> [OPTION]\n", argv[0]);
    printf(" Parameters:\n");
    printf("\t -R: remplace duplicate files with links\n");
    printf("\t -V: Show the duplicate files\n");
    exit(0);
  }
  
  vector_init(&vecFiles);
  vector_init(&vecDuplicates);

  printf("get all files...\n");
  getAllFiles(argv[1], &vecFiles);
  printf("get duplicate files...\n");
  getAllDuplicates(&vecFiles, &vecDuplicates);
  
  while ((opt = getopt(argc, argv, "RV")) != -1) {
    switch(opt) {
      case 'R': 
        vector_forEach(&vecDuplicates, &optimizeSpace); 
        break;
      case 'V': 
        vector_forEach(&vecDuplicates, &printDuplicate);
        break;
      default: 
        break;
    }
  }
  
  vector_length(&vecDuplicates, &duplicatesLength);
  vector_length(&vecFiles, &filesLength);
  printf("Done ! Files found : %ld, duplicates found : %ld\n", filesLength, duplicatesLength);
  
  vector_forEach(&vecDuplicates, &free_duplicates);
  vector_free(&vecDuplicates);
  vector_forEach(&vecFiles, &free_file);
  vector_free(&vecFiles);
  
  return 1;
}

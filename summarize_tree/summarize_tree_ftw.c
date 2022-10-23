#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

static int num_files = 0;
static int num_dirs = 0;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    
  // When typeflag is one, it is a directory so we increment our count for directories
  // and 0 means file, so we increment our count for files  
  if(typeflag == 1) ++num_dirs;
  if(typeflag == 0) ++num_files;
  
 
  return 0;
}

#define MAX_FTW_DEPTH 16
int main(int argc, char** argv) {
    // Check arguments and set things up
if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

   ftw(argv[1], callback, MAX_FTW_DEPTH);

    
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_files);

    
}

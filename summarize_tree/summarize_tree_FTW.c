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
    // Define stuff here
    
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

    printf("number of files: %d \n", num_files);
    printf("number of directories: %d \n", num_dirs);

    
}

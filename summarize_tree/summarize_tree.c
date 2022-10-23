#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;


bool is_dir(const char* path) {
//Create buf structure for the function stat
struct stat buf;

// Use the output of stat to make sure there isn't a failure
int check = stat(path, &buf);
if (check == 0){
// The switch statement checks for if its a directory
// Or if its a file, then returns the corresponding boolean
switch(buf.st_mode & S_IFMT){
	case S_IFDIR: return true; break;
	case S_IFREG: return false; break;
	default: return false; break; 	      
}
}
else{
// If the check integer returns -1, this becomes false
return false;
}
      
}

void process_path(const char*);

void process_directory(const char* path) {
  // Increment directory count
  ++num_dirs; 
       
  // Create dirent structure for the readdir() method
  struct dirent *entry;
  // Open the given director and instantiate the variable
  DIR *dir;
  dir = opendir(path);
  // This our amazing way of skipping the first two entries
  // entry = readdir(dir);
  // entry = readdir(dir);

  // In each recursive step, we want to hop into the directory that we are processing
    chdir(path);
  // This goes through each entry in the directory (minus the first two)
    while ((entry = readdir(dir)) != NULL){
      if(entry->d_name[0] != '.' && entry->d_name[1] != '.'){
        process_path(entry->d_name);
      }
  }
  // Hop out of the current directory
    chdir("..");
  // Close the opened directory
    closedir(dir);
  }

void process_file(const char* path) {
  // Increment file count
  ++num_regular;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}

#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024


bool is_vowel(char c) {

    // Set up a list of all vowels, captial and noncapital
    char *vowels = (char*)calloc(11, sizeof(char));
    strcpy(vowels, "aeiouAEIOU\0");
    // If the charcter c (the input for this function) matches with a character in the list of vowels
    // then it is a vowel, otherwise it is not a vowel
    // (strchr returns the characters that it matches with, so if it is not null then it matches with something)
    if(strchr(vowels, c) != NULL){
			free(vowels);
      return true;
    }
		free(vowels);
		return false;	 
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
  // Set indexes, x is for position in out_buf, i is for position in in_buf
  int i,x=0;
  for (i=0; i<num_chars; ++i) {
  // If the current position in in_buf is not a vowel, we write it in out_buf
  // and increment our index for out_buf
	if(!is_vowel(in_buf[i])){
			out_buf[x] = in_buf[i];
			++x;
	}
  }
	return x;
}


void disemvowel(FILE* inputFile, FILE* outputFile) {

    // Set up buffers and nchar
      char out_buf[BUF_SIZE];
      char in_buf[BUF_SIZE];
      // nchar is the number of characters read from the function fread
      int nchar;
      // First call of fread is outside the while loop so we gurantee that if there is content to read
      // nchar does not = 0 when going into the while loop
      nchar = fread(in_buf,sizeof(char),BUF_SIZE,inputFile);
      // While there is content being read, loop
      while(nchar != 0){
        // Store the return value copy_non_vowels so we know how many charecters are in out buf
        int output = copy_non_vowels(nchar, in_buf, out_buf);
        // Here we only write the characters in out_buf that we know are not null
        // (Hence the use of the int output)
        fwrite(out_buf,sizeof(char),output,outputFile);
        // fread the next section (up to BUF_SIZE which is currently 1024)
        nchar = fread(in_buf,sizeof(char),BUF_SIZE,inputFile);
      }
      // close the files opened in main.
      fclose(inputFile);
	    fclose(outputFile);

}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
        FILE *inputFile;
        FILE *outputFile;

    // If there is only one, then it is just the name of the function call
    // Therefore we default to taking in input from the console
    // and outputting onto the console
    if(argc == 1){
    	inputFile = stdin;
    	outputFile = stdout;

    }
    // If there are two arv arguments we assume: Name of function call, name of input file
    // and we default to the output going onto the console.
    if(argc == 2){
            inputFile =fopen(argv[1], "r+");
	    outputFile = stdout;
    }
    // If there are 3 we assume: name of function call, input file, output file
    if(argc == 3){
            inputFile = fopen(argv[1], "r+");
	    outputFile = fopen(argv[2], "w+");
    }
    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);
    // Return 0 when the code is successfully ran
    return 0;
}

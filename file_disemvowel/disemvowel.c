#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024


bool is_vowel(char c) {
    /*
     * Returns true if c is a vowel (upper or lower case), and
     * false otherwise.
     */
        char *vowels = (char*)calloc(11, sizeof(char));
  strcpy(vowels, "aeiouAEIOU\0");
                if(strchr(vowels, c) != NULL){
			free(vowels);
                        return true;
                }
		free(vowels);
		return false;	 
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf.
     * num_chars indicates how many characters are in in_buf,
     * and this function should return the number of non-vowels that
     * that were copied over.
     */

  int i,x=0;
  for (i=0; i<num_chars; ++i) {
	if(!is_vowel(in_buf[i])){
			out_buf[x] = in_buf[i];
			++x;
	}
  }
	return x;
}


void disemvowel(FILE* inputFile, FILE* outputFile) {
   FILE *fp;
   FILE *of;

      	/*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */
      char out_buf[BUF_SIZE];
      char in_buf[BUF_SIZE];
      int nchar;
      of = fopen(outputFile, "w+");
      fp = fopen(inputFile, "w+");
      nchar = fread(in_buf,BUF_SIZE,1,fp);
      while(nchar != 0){
        int output = copy_non_vowels(nchar, in_buf, out_buf);
        fwrite(out_buf,output,1,of);
        fflush(inputFile);
        fflush(outputFile);
        fseek(fp,0,SEEK_CUR);
        nchar = fread(in_buf,BUF_SIZE,1,fp);
      }


}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.




    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    if(argc == 2){
            inputFile = argv[1];
    }
    if(argc == 3){
            inputFile = argv[1];
    }
    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    return 0;
}

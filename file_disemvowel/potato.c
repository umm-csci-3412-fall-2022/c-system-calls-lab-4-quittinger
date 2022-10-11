#include <stdlib.h>
#include <string.h>


#include <stdio.h>
#include <stdbool.h>
#define BUF_SIZE 1024



int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.




    FILE *inputFile = stdin;
    FILE *outputFile = stdout;
    char buffer[BUF_SIZE];
    int nchar = 1;
    while(nchar != 0){
        nchar = fread(buffer, sizeof(char), BUF_SIZE, inputFile);
	fwrite(buffer, sizeof(char), nchar, outputFile);
	fseek(inputFile, 0, SEEK_CUR);
	printf("\n%d\n", nchar);   
    
    }
    //nchar = fread(buffer, sizeof(char), 3, inputFile);
    //fwrite(buffer, sizeof(char), 3, outputFile);
    //fseek(inputFile, 3, SEEK_SET);
    //nchar = fread(buffer, sizeof(char), 3, inputFile);
    //fwrite(buffer, sizeof(char), 3, outputFile);     
    
    

    printf("\n%d\n", nchar);    
    fclose(inputFile);
}


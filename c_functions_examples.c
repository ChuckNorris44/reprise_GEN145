







// ***** NOTES *****
// fgets -> getting string
// fgetc -> getting character
// feof  -> file end of file
// fopen -> open file
// fclose-> closing file
// EOF   -> end of file



// EXAMPLE:
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    int is_ok = EXIT_FAILURE;
    const char* fname = "/tmp/unique_name.txt"; // or tmpnam(NULL);
    FILE* fp = fopen(fname, "w+");
    if(!fp) {
        perror("File opening failed");
        return is_ok;
    }
    fputs("Hello, world!\n", fp);
    rewind(fp);
 
    int c; // note: int, not char, required to handle EOF
    while ((c = fgetc(fp)) != EOF) { // standard C I/O file reading loop
       putchar(c);
    }
 
    if (ferror(fp)) {
        puts("I/O error when reading");
    } else if (feof(fp)) {
        puts("End of file reached successfully");
        is_ok = EXIT_SUCCESS;
    }
 
    fclose(fp);
    remove(fname);
    return is_ok;
}





// EXAMPLE 2:
#include <cstdio>
#include <cstdlib>
 
int main()
{
    int is_ok = EXIT_FAILURE;
    FILE* fp = std::fopen("/tmp/test.txt", "w+");
    if(!fp) {
        std::perror("File opening failed");
        return is_ok;
    }
 
    int c; // note: int, not char, required to handle EOF
    while ((c = std::fgetc(fp)) != EOF) { // standard C I/O file reading loop
       std::putchar(c);
    }
 
    if (std::ferror(fp)) {
        std::puts("I/O error when reading");
    } else if (std::feof(fp)) {
        std::puts("End of file reached successfully");
        is_ok = EXIT_SUCCESS;
    }
 
    std::fclose(fp);
    return is_ok;
}









// ////////////////////////////////////////////
// 		EXAMPLE OF STRNCPY
// ///////////////////////////////////////////
/*
 * 
FUNCTION STRNCPY
char * strncpy ( char * destination, const char * source, size_t num );
Copy characters from string
Copies the first num characters of source to destination. If the end of the source C string (which is signaled by a null-character) is found before num characters have been copied, destination is padded with zeros until a total of num characters have been written to it.

No null-character is implicitly appended at the end of destination if source is longer than num. Thus, in this case, destination shall not be considered a null terminated C string (reading it as such would overflow).

destination and source shall not overlap (see memmove for a safer alternative when overlapping).



PARAMETERS
destination
Pointer to the destination array where the content is to be copied.
source
C string to be copied.
num
Maximum number of characters to be copied from source.
size_t is an unsigned integral type.

RETURN VALUE
destination is returned
* 
*/




// EXAMPLE strncpy::::
/* strncpy example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str1[]= "To be or not to be";
  char str2[40];
  char str3[40];

  /* copy to sized buffer (overflow safe): */
  strncpy ( str2, str1, sizeof(str2) );

  /* partial copy (only 5 chars): */
  strncpy ( str3, str2, 5 );
  str3[5] = '\0';   /* null character manually added */

  puts (str1);
  puts (str2);
  puts (str3);

  return 0;
}







// EXAMPLE












/* Matthew Blanchard
 * ECE 331
 * HW 4
 * strstr() clone
 */

#include<stdio.h>

// Return pointer to first occurance of substring 'needle' in 'haystack'
char *x_strstr(const char *haystack, const char *needle);

int main(int argc, char *argv[]) {
        
        char * substr;  // Substring pulled from haystack

        // Expecting 2 arguments
        if (argc != 3) {
                printf("Error: expecting 2 arguments, found %d\n", argc);
                return 1;
        }
         
        substr = x_strstr(argv[1], argv[2]);
        
        // Report if needle is not found
        if (substr == NULL) {
                printf("%s was not found withing %s\n", argv[2], argv[1]);
                return 2;
        } else {
                printf("%s\n", substr); // Return substring if found
                return 0;
        }
}

char *x_strstr(const char *haystack, const char *needle) {
        char c = ' ';                    // Iterating character
        char *sub_start = haystack;      // Start of most recent match  
        int i = 0;                       // Haystack index
        int j = 0;                       // Needle index

        // Iterate through all of 'haystack'
        for (c = haystack[i]; c != '\0'; c = haystack[++i]){
                if (c == needle[j]) {             // Move needle forward if a match occurs 
                        j++;    
                        if (needle[j] == '\0') {  // Complete match if needle hits null terminator
                                return sub_start;
                        }
                } else {
                        j = 0;                   // Reset needle index & substring start
                        sub_start = haystack + i + 1;       
                }
        }
        return NULL;    // Return null if the needle was not found.
}

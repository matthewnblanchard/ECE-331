/* Matthew Blanchard
 * ECE 331
 * Due 2/9/2017
 *
 * Description: Matches input regular expression to stdin and 
 * prints matching lines to stdout
 *
 * Arguments: 
 *      argv[1]: Regular expression to match
 */

#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
        
        char **line = NULL;       // Line read from stdin
        size_t lsize = 256;       // Initial size of line buffer
        regex_t *preg;            // RE buffer 

        preg = (regex_t *)malloc(sizeof(*preg));
        line = (char **)malloc(lsize);

        // Expecting a single string as an argument (the RE)
        if (argc != 2){
                printf("Error: Expected a single regular expression for an argument\n");
                return 1;
        }
        
        // Compile regular expression
        if (regcomp(preg, argv[1], REG_NOSUB|REG_EXTENDED) != 0) {
                printf("Error: Invalid regular expression\n");
                return 2;
        }

        // Scan for input and print matches
        while (getline(line, &lsize, stdin) != -1) {
                if (regexec(preg, *line, (size_t)0, NULL, 0) != REG_NOMATCH)
                        printf("%s", *line);
        }

        regfree(preg);
        free(preg); 
        free(line);
        return 0;
}

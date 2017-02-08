/*
 * Matthew Blanchard
 * ECE 331
 * HW #1 Q3
 * Due 1/26/2017
 * 
 * Description: Program prints all arguments passed on the command line.
 * Very similar to 'echo'
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
        int i;
        for (i = 1; i < argc; i++) {
                printf("%s", argv[i]);
                if (i < (argc - 1))
                        printf(" ");
        }
        printf("\n");
        return 0;
}

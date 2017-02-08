/*
 * Matthew Blanchard
 * ECE 331
 * HW2 Q4
 *
 * Description: Counts the number of blocks used by the passed files
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>

int main(int argc, char *argv[])
{
        int i = 0;               // Loop index
        int blk_sum = 0;         // Running sum of blocks
        struct stat stat_ret;    // Return struct of stat()
        glob_t *glob_ret;        // Return struct of globi)

        glob_ret = (glob_t *)malloc(sizeof(*glob_ret)); 

        if (argc != 2) {
                printf("Error: bsum-glob requires exactly one glob passed as an argument.\n");
                return -1;
        }
        
        // glob error checking
        switch (glob(argv[1], 0, NULL, glob_ret)) {
        case GLOB_NOSPACE:
                printf("Error: out of memory.\n");
                return -2;
        case GLOB_NOMATCH:
                printf("No files matching '%s' were found.\n", argv[1]);
                return -3;
        case GLOB_ABORTED:
                printf("Encountered a read error\n");
                break;
        }

        for (i = 0; i < glob_ret->gl_pathc; i++) {
                stat(glob_ret->gl_pathv[i], &stat_ret);
                blk_sum += (int)stat_ret.st_blocks;
        }

        globfree(glob_ret);
        free(glob_ret);

        printf("%d\n", blk_sum);
        return 0;
}

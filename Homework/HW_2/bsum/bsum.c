/*
 * Matthew Blanchard
 * ECE 331
 * HW2 Q4
 *
 * Description: Counts the number of blocks used by the passed files
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int i = 0;               // Loop index
        int blk_sum = 0;         // Running sum of blocks
        struct stat stat_ret;    // Return struct of stat()

        if (argc < 2) {
                printf("Error: bsum requires at least one filename passed as an argument.\n");
                return -1;
        }

        for (i = 1; i < argc; i++) {
                if (stat(argv[i], &stat_ret) == -1)
                        printf("File '%s' was not found. Ignoring\n", argv[i]);
                else
                        blk_sum += (int)stat_ret.st_blocks;
        }

        printf("%d\n", blk_sum);
        return 0;
}

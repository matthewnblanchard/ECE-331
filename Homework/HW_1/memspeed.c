/*
 * Matthew Blanchard
 * ECE 331
 * HW #1 Q4
 * Due 1/26/2017
 *
 * Description: Measures memory speed by allocating and writing to
 * a buffer of size BUF_SIZE and timing it.
 
 * Arguments: Takes one argument, BUF_SIZE, which is the size of the 
 * memory buffer to test in bytes
 *
 * Results: Returns start and end times of the write operation in the 
 * following format: buffer_size start(sec) start(nsec) end(sec) end(nsec)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
        #define NSEC 1000000000.0

        unsigned int buf_size = 0;       // Buffer size
        char *buf_ptr = NULL;            // Pointer to buffer in memory
        int i = 0;                       // Loop index
        struct timespec start;           // Write start time
        struct timespec end;             // Write end time

        if (argc != 2) {
                printf("Error: expected 1 argument, found %d\n", argc - 1);
                return 0;
        }
        buf_size = atoi(argv[1]);
        if (buf_size == 0) {
                printf("Error: %s is not a valid memory size\n", argv[1]);
                return 0;
        }

        buf_ptr = malloc(buf_size * sizeof(*buf_ptr));
        if (buf_ptr == NULL) {
                printf("Error: memory overflow\n");
                return 0;
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (i = 0; i < buf_size; i++)
                buf_ptr[i] = 42;
        clock_gettime(CLOCK_MONOTONIC, &end);
        free(buf_ptr);

        printf("%d", buf_size);
        printf(" %ld", (long)start.tv_sec);
        printf(" %ld", (long)start.tv_nsec);
        printf(" %ld", (long)end.tv_sec);
        printf(" %ld\n", (long)end.tv_nsec);
        return 0;
}

/* Matthew Blanchard
 * ECE 331
 * sd_geo.c
 *      Prints geometry of the SD card
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/hdreg.h>
#include <linux/fs.h>
#include <fcntl.h>

int main()
{       
        struct hd_geometry sd;
        int fp;

        fp = open("/dev/mmcblk0p2", O_RDONLY);

        if (fp == -1) {
                printf("Error: failed to open /dev/mmcblk0p2 ... \n");
                return 1;
        }
        if (ioctl(fp, HDIO_GETGEO, &sd)) {
                printf("Error: failed to read SD card geometry ... \n");
                return 2;
        }
        printf("Heads: %u\n", sd.heads);
        printf("Sectors: %u\n", sd.sectors);
        printf("Cylinders: %u\n", sd.cylinders);
        printf("Start: %lu\n", sd.start);

        close(fp);
        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char * argv[])
{
	struct rusage out;
	if (getrusage(RUSAGE_SELF, &out)) {
		printf("Failed to get rusage data ... \n");
		return 1;
	}
	printf("The resident size is %ld ... \n", out.ru_maxrss);
	return 0;
}

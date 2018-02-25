#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
char buffer [2048];
int version = 1;
copy (int old, int new) {
	int count;
	while ((count = read(old, buffer, sizeof(buffer))) > 0)
		write (new, buffer, count);
}

main (argc, argv)
	int argc;
	char * argv[];
{
	int fdold, fdnew;
	if (argc != 3) {	
		printf("NEED TWO ARGUMENTS FOR copy PROGRAM\n");
		exit (1);
	}
	fdold = open (argv[1], O_RDONLY);
	if (fdold == -1) {
		printf("CANNOT OPEN FILE %s \n", argv[1]);
		exit (1);
	}
	fdnew = open (argv[2], O_RDWR+O_CREAT, S_IREAD+S_IWRITE+S_IRGRP+S_IWGRP+S_IROTH);
	if (fdnew == -1) {
		printf("CANNOT CREATE/OPEN FILE %s \n", argv[2]);
		exit(1);
	}
	copy (fdold, fdnew);
	exit (0);
}


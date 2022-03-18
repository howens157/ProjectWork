#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main()
{
	char buf[32] = "notre dame yay!\n";

	int fd;

	fd = syscall(SYS_open, "example.txt", O_RDWR);

	syscall(SYS_write, fd, buf, 32);

	syscall(SYS_close, fd);

	return(0);
}


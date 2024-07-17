
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <signal.h>

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 1000);
	// stashfd;
	// dup2(stashfd, fd);
	if (stashfd < 0)
		exit(1);
	if (close(fd) < 0)
		exit(1);
	return (stashfd);
}

int main()
{
	int fd1;
	int fd2;
	int fd3;
	int stashed_targetfd1;
	int stashed_targetfd2;
	int stashed_targetfd3;

	stashed_targetfd1 = -1;
	stashed_targetfd2 = -1;
	stashed_targetfd3 = -1;

	fd1 = open("out1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// fd1 = stashfd(fd1);
	fd2 = open("out2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// fd2 = stashfd(fd2);
	fd3 = open("out3", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// fd3 = stashfd(fd3);

	// dup2(stashed_targetfd1, fd1);
	stashed_targetfd1 = dup(1);
	dup2(fd1, 1);                
	close(fd1);    

	// dup2(stashed_targetfd2, fd2);
	stashed_targetfd2 = dup(STDIN_FILENO);
	dup2(fd2, 1);                
	close(fd2);                  

	// dup2(stashed_targetfd3, fd3);
	stashed_targetfd3 = dup(1);
	dup2(fd3, 1);                
	close(fd3);
	write(1, "hello\n", 6);
	printf("stashfd: %d\n", stashed_targetfd1);
	printf("stashfd: %d\n", stashed_targetfd2);
	printf("stashfd: %d\n", stashed_targetfd3);

	dup2(stashed_targetfd3, 1);
	close(stashed_targetfd3);  
	dup2(stashed_targetfd2, STDIN_FILENO);
	close(stashed_targetfd2);  
	dup2(stashed_targetfd1, 1);
	close(stashed_targetfd1);  
	write(1, "world\n", 6);
}

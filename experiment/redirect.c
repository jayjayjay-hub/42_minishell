
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
	// stashfd = -1;
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

	// 当初の状態はfd=1(stdout)のはずで、それ以外のfdはstdinとstderrを除けば開かれていないものと考えてください。
	// open_redir_fd()
	fd1 = open("out1", O_WRONLY | O_CREAT | O_TRUNC, 0644);    // fd=1(stdout), fd=3(f1)
	fd1 = stashfd(fd1); // fd=1(stdout), fd=10(f1)
	fd2 = open("out2", O_WRONLY | O_CREAT | O_TRUNC, 0644);    // fd=1(stdout), fd=10(f1), fd=3(f2)
	fd2 = stashfd(fd2); // fd=1(stdout), fd=10(f1), fd=11(f2)
	fd3 = open("out3", O_WRONLY | O_CREAT | O_TRUNC, 0644);    // fd=1(stdout), fd=10(f1), fd=11(f2), fd=3(f3)
	fd3 = stashfd(fd3); // fd=1(stdout), fd=10(f1), fd=11(f2), fd=12(f3)

	// redirect
	stashed_targetfd1 = stashfd(1); // fd=10(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	dup2(fd1, 1);                   // fd=1(f1), fd=10(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	close(fd1);                     // fd=1(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	stashed_targetfd2 = stashfd(1); // fd=10(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	dup2(fd2, 1);                   // fd=1(f2), fd=10(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	close(fd2);                     // fd=1(f2), fd=10(f1), fd=12(f3), fd=13(stdout)
	stashed_targetfd3 = stashfd(1); // fd=10(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	dup2(fd3, 1);                   // fd=1(f3), fd=10(f1), fd=11(f2), fd=12(f3), fd=13(stdout)
	close(fd3);                     // fd=1(f3), fd=10(f1), fd=11(f2), fd=13(stdout)
	write(1, "hello\n", 6);

	// stashed_fd1 = 13
	// stashed_fd2 = 10
	// stashed_fd3 = 11
	// こんな状況になっているはずです。これをresetするには、逆から順番にやっていくことです。

	// reset_redirect
	dup2(stashed_targetfd3, 1); // fd=1(f2), fd=10(f1), fd=13(stdout)
	dup2(stashed_targetfd2, 1); // fd=1(f1), fd=13(stdout)
	dup2(stashed_targetfd1, 1); // fd=1(stdout)
	write(1, "world\n", 6);
	// これで無事、fd=1(stdout)のみ、という当初の状態への復元もできました。
}
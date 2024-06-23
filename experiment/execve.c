#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
    char *new_argv[] = {"/bin/ls", "-l", NULL};  // 実行するプログラムと引数
    char *new_envp[] = { "HOME=/usr/home", "LOGNAME=home", NULL };  // 新しい環境変数

    // カレントディレクトリを変更
    if (chdir("/tmp") == -1) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    // 新しいプログラムで現在のプロセスを置き換える
    if (execve("/bin/ls", new_argv, new_envp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // execveが成功すれば、この行には到達しません
    return 0;
}

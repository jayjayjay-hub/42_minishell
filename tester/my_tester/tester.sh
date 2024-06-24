#!/bin/bash

# ./a.outを作成
cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

# ./tester/tester.sh で実行
cleanup() {
	rm -f cmp out f1 f2 f3 test
}

assert() {
	# テストケースの表示
	printf '%-36s:' "\"$1\""

	# テストケースの実行
	# bash -c "$1" >cmp 2>&-
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	echo -n -e "$1" | ../../minishell >out 2>&-
	actual=$?

	# 出力結果の比較
	diff cmp out >/dev/null && echo -n -e "  diff \033[32mOK\033[0m" || echo -n -e "  diff \033[31mKO\033[0m"

	# exit status の比較
	if [ "$actual" = "$expected" ]; then
		echo -n -e "  status \033[32mOK\033[0m"
	else
		echo -n -e "  status \033[31mKO\033[0m, expected $expected but got $actual"
	fi
	echo
}

# step3 Exec Path
# 絶対パスのコマンド
assert '/bin/pwd'
assert '/bin/ls'
assert '/bin/echo'

# step4 Exec Filename
# 引数なしのコマンド
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'
# exit status 127 (command not found)
assert 'a.out'
assert 'nosuchfile'

# step5 Tokenizer
# ダブル、シングルクオーテンションのハンドリング
assert 'ls /'
assert 'echo hello    world'
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"
assert "echo \"hello   world\" \"42Tokyo\""
assert "echo \"'hello   world'\" \"42Tokyo\""
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

# step6 Redirection
assert "echo hello >test"
assert "echo hello >f1>f2>f3>test"

# step7 Pipe
assert "ls | abc" # waitpidによりabcが先に終了するため、statusがlsによるものになる
assert "abc | ls"
assert "ls | cat"
assert "ls -al | cat -en"
assert "cat Makefile | grep -n all"
assert " "

# ファイルへの書き込み200回
# for i in $(seq 200); do
# 	assert "echo hello >> test"
# done

# normal echo test * 100
# for i in $(seq 100); do
# 	assert "echo hello"
# done

cleanup
echo 'Done.'

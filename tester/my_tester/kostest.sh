#!/bin/bash

# ./a.outを作成
cat <<EOF | gcc -xc -o a.out -
#include <unistd.h>
int main() { write(2, "hello", 5); }
EOF

# ./tester/tester.sh で実行
cleanup() {
	rm -f cmp out f* test er* out* *.c
}

assert () {
	# テストケースの表示
	printf '%-70s:' "\"$1\""

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

assert "/bin/pwd"
assert "/bin/ls"
assert "/bin/echo"
assert "pwd"
assert "echo"
assert "ls"
assert ".out"
assert "nosuchfile"
assert "ls /"
assert "echo hello    world"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '"hello   world"' '42Tokyo'"
assert "echo "hello   world" "42Tokyo""
assert "echo "'hello   world'" "42Tokyo""
assert "echo hello'      world'"
assert "echo hello'  world  '"  42Tokyo  ""
assert "echo hello >test"
assert "echo hello >f1>f2>f3>test"
assert "ls>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f|cat f"
assert "ls | abc"
assert "abc | ls"
assert "ls | cat"
assert "ls -a | cat -en"
assert "cat Makefile | grep -n all"
assert "ls -|a"
assert "ls | cat -en | ls -a | cat -e | cat -n"
assert "cat -en Makefile | grep 1 | sort -r"
assert "ls -l | cat < Makefile | grep -n all >> test"
assert "< Makefile cat -en | cat | cat > f1 | cat -en | grep 1 >f1 >> test"
assert "cd ~"
assert "cd -"
assert "cd .."
assert "cd .. | pwd"
assert "cd | pwd"
assert "cd | ls"
assert "pwd"
assert "pwd > out"
assert "export"
assert "export MY_ENV=123 | export | grep -wc"
assert "export MY_ENV=123 | export | grep MY_ENV"
assert "exit 42"
assert "exit 2147483647"
assert "exit 2147483648"
assert "exit -4"
assert "exit -2147483648"
assert "exit -2147483649"
assert "exit 2 2"
assert "exit hello"
assert "exit 5h"
assert "exit *7"

cleanup
echo 'Done.'

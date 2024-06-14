#!/bin/bash

# ./a.outを作成
cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

# ./tester/tester.sh で実行
cleanup() {
	rm -f cmp out
}

assert() {
	# テストケースの表示
	printf '%-30s:' "\"$1\""

	# テストケースの実行
	# bash -c "$1" >cmp 2>&-
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	echo -n -e "$1" | ../minishell >out 2>&-
	actual=$?

	# 出力結果の比較
	diff cmp out >/dev/null && echo -n '  diff OK' || echo -n '  diff NG'

	# exit status の比較
	if [ "$actual" = "$expected" ]; then
		echo -n '  status OK'
	else
		echo -n "  status NG, expected $expected but got $actual"
	fi
	echo
}

# テストケースをここに追加していく
assert '/bin/pwd'
assert '/bin/ls'
assert '/bin/echo'

# 引数なしのコマンド
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

# エラーコマンドstatus 127
assert 'a.out'
assert 'nosuchfile'

cleanup
echo 'Done.'
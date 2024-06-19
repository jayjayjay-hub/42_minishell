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
	printf '%-36s:' "\"$1\""

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
# assert ""

cleanup
echo 'Done.'
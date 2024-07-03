#!/bin/bash

# ./a.outを作成
cat <<EOF | gcc -xc -o a.out -
#include <unistd.h>
int main() { write(2, "hello", 5); }
EOF

# ./tester/tester.sh で実行
cleanup() {
	rm -f cmp out f* test er* out* *.txt *.c
}

assert() {
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
assert "> file"
assert "> file | cat < no_such_file"
# assert "echo hello > out1.txt > out2.txt > out3.txt 2> err1.txt 2> err2.txt 2> err3.txt| cat out1.txt out2.txt out3.txt err1.txt err2.txt err3.txt"
# assert "echo hello >> out1.txt >> out2.txt >> out3.txt 2>> err1.txt 2>> err2.txt 2>> err3.txt| cat out1.txt out2.txt out3.txt err1.txt err2.txt err3.txt"
assert "ls > out1.txt > out2.txt > out3.txt 2> err1.txt 2> err2.txt 2> err3.txt| cat out1.txt out2.txt out3.txt err1.txt err2.txt err3.txt"
# assert "ls >> out1.txt >> out2.txt >> out3.txt 2>> err1.txt 2>> err2.txt 2>> err3.txt| cat out1.txt out2.txt out3.txt err1.txt err2.txt err3.txt"
assert "ls no_such_file > out1.txt > out2.txt > out3.txt 2> err1.txt 2> err2.txt 2> err3.txt| cat out1.txt out2.txt out3.txt err1.txt err2.txt err3.txt"
# assert "ls no_such_file >> out1.txt >> out2.txt >> out3.txt 2>> err1.txt 2>> err2.txt 2>> err3.txt| cat out1.txt out2.txt out3.txt err1.txt err2.txt err3.txt"
assert "echo a > out| echo b >> out| echo c >> out| echo d >> out| cat out"
assert "echo a > out| echo b >> out| echo c >> out| echo d > out| cat out"
# assert "echo hello 2147483647> file"
assert "echo hello 2147483648> file"
assert "./a.out 3> file3 2> file2 1> file1| cat file3 file2 file1, printf '#include<unistd.h>\nint main(){write(1, "fd1\\n", 4)|write(2, "fd2\\n", 4)|write(3, "fd3\\n", 4)|}' > a.c && gcc a.c"
assert "./a.out 1> file1 2> file2 3> file3| cat file1 file2 file3, printf '#include<unistd.h>\nint main(){write(1, "fd1\\n", 4)|write(2, "fd2\\n", 4)|write(3, "fd3\\n", 4)|}' > a.c && gcc a.c"
assert "echo a 1> 1.txt 2> 2.txt 3> 3.txt| ./a.out 1>> 1.txt 2>> 2.txt 3>> 3.txt| cat 1.txt 2.txt 3.txt, printf '#include<unistd.h>\nint main(){write(1, "fd1\\n", 4)|write(2, "fd2\\n", 4)|write(3, "fd3\\n", 4)|}' > a.c && gcc a.c"
assert "echo a 3> 3.txt 2> 2.txt 1> 1.txt 2> 2.txt 3> 3.txt| echo b 1>> 1.txt 2>> 2.txt 3>> 3.txt 2>> 2.txt 1>> 1.txt| ./a.out 1>> 1.txt 2>> 2.txt 3>> 3.txt 2>> 2.txt 1>> 1.txt| cat 1.txt 2.txt 3.txt, printf '#include<unistd.h>\nint main(){write(1, "fd1\\n", 4)|write(2, "fd2\\n", 4)|write(3, "fd3\\n", 4)|}' > a.c && gcc a.c"
# assert "echo a > f| echo b >> f| cat f f f >> ff| cat ff ff >> f| cat f"
assert "ls>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f>f|cat f"

# step7 Pipe
assert "ls | abc" # waitpidによりabcが先に終了するため、statusがlsによるものになる
assert "abc | ls"
assert "ls | cat"
assert "ls -a|cat -en"
assert "cat Makefile | grep -n all"
assert "ls -|a"

# multi Pipe
assert "ls | cat -en | ls -a | cat -e | cat -n"
# assert "sleep 2 | sleep 1 | cat | cat -e | cat -n | echo hello"

#mix Pipe
assert "ls -l | cat < Makefile | grep -n all >> test"
assert "< Makefile cat -en | cat | cat > f1 | cat -en | grep 1 >f1 >> test"

# step8 Expantion
# assert "echo a > $NO_ENV | echo b, unset NO_ENV"

assert " "

cleanup
echo 'Done.'

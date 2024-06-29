#!/bin/bash

failed=0
error_num=0
cases=0
test_file="./tester/my_tester/test_cmd.txt"
error_file="./tester/my_tester/test_cmd_error.txt"

# ./.outを作成
cat <<EOF | gcc -xc -o .out -
#include <stdio.h>
int main() { printf("hello from .out\n"); }
EOF

cleanup() {
    rm -f cmp* out* f1 f2 f3 test
}

del_error_cmd_file() {
	rm -f $error_file
}

assert() {
	error_num=0
    # テストケースの実行
    echo -n -e "$1" | bash >cmp 2>&1
    expected=$?
    echo -n -e "$1" | ./minishell >out 2>&1
    actual=$?

    # minishellのプロンプト行とexitコマンド行を除外
    grep -v '^minishell\$ ' cmp > cmp_filtered
    grep -v '^minishell\$ ' out > out_filtered
    grep -v '^exit$' cmp_filtered > cmp_filtered_final
    grep -v '^exit$' out_filtered > out_filtered_final

	# exit status と 出力結果の比較がどっちもOKの場合"."を表示
	if [ "$actual" = "$expected" ] && diff cmp_filtered_final out_filtered_final >/dev/null; then
		printf "\033[32m.\033[0m"
	else
		printf "\033[31mF\033[0m"
		failed=1
		error_num=1
	fi
}

failer() {
	echo "*****************************************************************"
	# テストケースの実行
	echo -n -e "$1" | bash >cmp 2>&1
	expected=$?
	echo -n -e "$1" | ./minishell >out 2>&1
	actual=$?

	# minishellのプロンプト行とexitコマンド行を除外
	grep -v '^minishell\$ ' cmp > cmp_filtered
	grep -v '^minishell\$ ' out > out_filtered
	grep -v '^exit$' cmp_filtered > cmp_filtered_final
	grep -v '^exit$' out_filtered > out_filtered_final
	# テストケースの表示(command: "testcase" と表示, 色は青)
	echo -n "command: "
	echo -e "'\033[34m$1\033[0m'"
	echo

	# exit status の比較
	if [ "$actual" != "$expected" ]; then
		printf "<< status KO, expected \033[31m$expected\033[0m but got \033[31m$actual\033[0m >>"
		echo
		echo
	fi
	if ! diff cmp_filtered_final out_filtered_final >/dev/null; then
		printf "<< diff KO >>"
		echo
		diff cmp_filtered_final out_filtered_final
		# それぞれの出力結果をexpect/cases_expectとout/cases_outのナンバーのファイルに保存
		cases=$((cases+1))
	fi
	echo
	echo
}

cleanup
del_error_cmd_file

# test.txt からテストケースを読み込んで実行する
while IFS= read -r testcase; do
    # '#' から始まるコメント行を無視
    if [[ "$testcase" =~ ^\s*# ]]; then
        continue
    fi

    assert "$testcase"
	if [ $error_num -eq 1 ]; then
		echo "$testcase" >> $error_file
	fi
done < $test_file

# failed=1の場合, エラーケースの表示
if [ $failed -eq 1 ]; then
	echo
	echo
	# エラーケースの表示(色は赤)
	# エラーLogはcases_expectとcases_outのナンバーのファイルに保存ということを表示
	mkdir expect out
	echo "cases_expect* and cases_out* are saved the error cases."
	echo -e "\033[31mFailed test cases\033[0m"
	echo
	while IFS= read -r testcase; do
		failer "$testcase"
	done < $error_file
fi

cleanup
echo 'Done.'

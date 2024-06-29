#!/bin/bash

failed=0
error_num=0
cases=1
test_file="./tester/my_tester/test_cmd.txt"
error_cmd="./error/all_error_cmd.txt"

# ./.outを作成
cat <<EOF | gcc -xc -o .out -
#include <stdio.h>
int main() { printf("hello from .out\n"); }
EOF

cleanup() {
    rm -f cmp* out* f1 f2 f3 test .out
}

del_error_cmd_file() {
	rm -rf $error_file error
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
	error_file="./error/cases$cases.txt"
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
	printf "\033[31m$cases. \033[0m"
	echo -e "'\033[34m$1\033[0m'"

	# exit status の比較
	printf "'$1'" >> $error_file
	echo -e "\n" >> $error_file
	if [ "$actual" != "$expected" ]; then
		printf "・status KO, expected \033[31m$expected\033[0m but got \033[31m$actual\033[0m"
		echo
		# エラーログをcasesファイルに保存
		echo "status KO" >> $error_file
		echo "expected $expected but got $actual" >> $error_file
		echo -e "\n" >> $error_file
	fi
	if ! diff cmp_filtered_final out_filtered_final >/dev/null; then
		echo "・diff KO"
		echo "diff KO" >> $error_file
		diff cmp_filtered_final out_filtered_final >> $error_file
		echo -e "\n" >> $error_file
		echo "<< expect >>" >> $error_file
		cat cmp_filtered_final >> $error_file
		echo -e "\n" >> $error_file
		echo "<< your output >>" >> $error_file
		cat out_filtered_final >> $error_file
	fi
	cases=$((cases+1))
	echo
}

cleanup
del_error_cmd_file

mkdir error

# test.txt からテストケースを読み込んで実行する
while IFS= read -r testcase; do
    # '#' から始まるコメント行を無視
    if [[ "$testcase" =~ ^\s*# ]]; then
        continue
    fi

    assert "$testcase"
	if [ $error_num -eq 1 ]; then
		echo "$testcase" >> $error_cmd
	fi
done < $test_file

# failed=1の場合, エラーケースの表示
if [ $failed -eq 1 ]; then
	echo
	echo
	# エラーケースの表示(色は赤)
	# エラーLogはcases_expectとcases_outのナンバーのファイルに保存ということを表示
	echo "cases_expect* and cases_out* are saved the error cases."
	echo -e "\033[31mFailed test cases\033[0m"
	echo
	while IFS= read -r testcase; do
		failer "$testcase"
	done < $error_cmd
else
	echo
	echo -e "\033[32mAll test cases passed.\033[0m"
fi

cleanup
echo 'Done.'

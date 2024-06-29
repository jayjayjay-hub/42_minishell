#!/bin/bash

failed=0
error_num=0
cases=1
diff_cmd="./error/diff.txt"

# ./.outを作成
cat <<EOF | gcc -xc -o .out -
#include <stdio.h>
int main() { printf("hello from .out\n"); }
EOF

cleanup() {
    rm -f cmp* out* f1 f2 f3 test .out
}

failer() {
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

	colordiff -u cmp_filtered_final out_filtered_final
	echo
	cases=$((cases+1))
}

cleanup

while IFS= read -r testcase; do
	failer "$testcase"
	echo "****************************************************************"
	echo
done < $diff_cmd
echo

cleanup
echo 'Done.'

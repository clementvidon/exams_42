src="$1"
cmd="gcc -Wall -Wextra -Werror $src -g -fsanitize=address"


echo ""
echo "parsing_1 ./a.out"
$cmd && ./a.out

echo ""
echo "parsing_2 ./a.out hello"
$cmd && ./a.out hello

echo ""
echo "parsing_3 ./a.out cd;"
$cmd && ./a.out cd ";"

echo ""
echo "parsing_4 ./a.out cd|"
$cmd && ./a.out cd "|"

echo ""
echo "parsing_5 ./a.out cd"
$cmd && ./a.out cd

echo ""
echo "parsing_6 ./a.out cd; pwd | echo ok"
$cmd && ./a.out cd ";" /bin/pwd "|" /bin/echo ok

echo ""
echo "program_1 ./a.out echo (: ; echo :)"
$cmd && ./a.out /bin/echo "(:" ";" /bin/echo ":)"

echo ""
echo "program_2 ./a.out echo (: ; echo :)"
$cmd && ./a.out /bin/salut /bin/ls ";" /bin/echo ":)"

echo ""
echo "pipe_2 ./a.out cat | cat | ls"
$cmd && ./a.out /bin/cat "|" /bin/cat "|" /bin/ls

echo ""
echo "pipe_1 ./a.out ls | grep a"
$cmd && ./a.out /bin/ls "|" /bin/grep a


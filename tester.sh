#!/bin/bash

make re -C ~/MINISHELL/
echo
echo ---------TESTING ECHO--------
echo
TEST=test_minishell
~/MINISHELL/minishell << yo
echo bla > $TEST 
echo bla bla >> $TEST  
echo -n bla bla >> $TEST
echo -nn bla bla >> $TEST
echo -nn -nn   -n --n bla >> $TEST
echo -n 'bla' >> $TEST
echo 'bla' >> $TEST
echo '\$SHELL' "\$SHELL" >> $TEST
echo \$SHELL\$PATH >> $TEST
echo 'bla "  " bla' "  bla"'bal'"bla   " >> $TEST
echo "\$NHENTH" >> $TEST
echo \$PWD >> $TEST
echo \$1 bla >> $TEST
echo \$1bla >> $TEST
echo \$19BLO >> $TEST
echo '\$?' >> $TEST
echo \$? >> $TEST
tnoeuheontu $TEST
echo \$? >> $TEST
echo \$? >> $TEST
echo bla -n
exit >> $TEST
yo


TEST=test_bash
/bin/bash << yo
echo bla > $TEST 
echo bla bla >> $TEST  
echo -n bla bla >> $TEST
echo -nn bla bla >> $TEST
echo -nn -nn   -n --n bla >> $TEST
echo -n 'bla' >> $TEST
echo 'bla' >> $TEST
echo '\$SHELL' "\$SHELL" >> $TEST
echo \$SHELL\$PATH >> $TEST
echo 'bla "  " bla' "  bla"'bal'"bla   " >> $TEST
echo "\$NHENTH" >> $TEST
echo \$PWD >> $TEST
echo \$1 bla >> $TEST
echo \$1bla >> $TEST
echo \$19BLO >> $TEST
echo '\$?' >> $TEST
echo \$? >> $TEST
tnoeuheontu $TEST
echo \$? >> $TEST
echo \$? >> $TEST
exit >> $TEST
yo

echo
diff -s test_minishell test_bash

echo
echo ---------TESTING OTHER BUILTIN--------
echo 
TEST=test_minishell
~/MINISHELL/minishell << yo
cd .. > $TEST
cd MINISHELL/ >> $TEST
cd ...
pwd >> $TEST
export SHELL=blabla BLO=blablibloup >> $TEST
export BLO= bloblo
export BLO =bloblo
export =
env >> $TEST
unset SHELL PATH nhtueo>> $TEST
exit >> $TEST
yo


TEST=test_bash
/bin/bash << yo > $TEST
cd ..
cd MINISHELL/ 
pwd 
export SHELL=blabla BLO=blablibloup
env
unset
unset SHELL PATH nhtueo
exit
yo

echo
diff -s test_minishell test_bash

echo
echo ---------TESTING PIPES--------
echo 
TEST=test_minishell
~/MINISHELL/minishell << yo
echo bla | wc > $TEST 
echo blanetuoh | wc -c >> $TEST  
echo -n bla bla | grep b | wc >> $TEST
ls -la | grep a | wc >> $TEST 
"echo" 'bla''bla' | wc -l >> $TEST 
exit >> $TEST
yo


TEST=test_bash
/bin/bash << yo > $TEST
echo bla | wc 
echo blanetuoh | wc -c  
echo -n bla bla | grep b | wc
ls -la | grep a | wc 
"echo" 'bla''bla' | wc -l 
exit
yo

echo
diff -s test_minishell test_bash

echo
echo ---------TESTING EXIT STATUS--------
echo
TEST=test_minishell
~/MINISHELL/minishell << yoy
echo \$? > $TEST
echo bla >>	$TEST
echo \$? >> $TEST
nteouh >> $TEST
echo \$? >> $TEST
../monitoring.sh >> $TEST
echo \$? >> $TEST 
nteouh >> $TEST
echo >> $TEST
echo \$? >> $TEST 
exit 11
yoy

echo $? >> $TEST

TEST=test_bash
/bin/bash << yoyoy
echo \$? > $TEST
echo bla >>	$TEST
echo \$? >> $TEST
nteouh >> $TEST
echo \$? >> $TEST
../monitoring.sh >> $TEST
echo \$? >> $TEST 
nteouh >> $TEST
echo >> $TEST
echo \$? >> $TEST 
exit 11
yoyoy

echo $? >> $TEST

echo
diff -s test_minishell test_bash

rm -rf test_minishell test_bash

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
exit >> $TEST
yo


TEST=test_bash
/bin/bash << yo > $TEST
echo bla 
echo bla bla  
echo -n bla bla
echo -nn bla bla
echo -nn -nn   -n --n bla
echo -n 'bla'
echo 'bla'
echo '\$shell' "\$shell"
echo \$shell\$path
echo 'bla "  " bla' "  bla"'bal'"bla   "
echo "\$nhenth"
echo \$pwd
echo \$1 bla
echo \$1bla
echo \$19blo
echo '\$?'
echo \$?
tnoeuheontu 
echo \$?
echo \$?
exit
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
pwd >> $TEST
export SHELL=blabla >> $TEST
env >> $TEST
##unset >> $TEST
exit >> $TEST
yo


TEST=test_bash
/bin/bash << yo > $TEST
cd ..
cd MINISHELL/ 
pwd 
export SHELL=blabla
env
##unset
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

diff -s test_minishell test_bash
#echo '---------TESTING EXIT--------'
#TEST=test
#~/MINISHELL/minishell << yoy
#~/MINISHELL/minishell << yo
#exit 5
#yo
#echo \$? > $TEST
#~/MINISHELL/minishell << yo
#exit 109
#yo
#echo \$? >> $TEST
#exit
#yoy


#TEST=test2
#/bin/bash << yoyoy
#~/MINISHELL/minishell << yo
#exit 5
#yo
#echo \$? > $TEST
#~/MINISHELL/minishell << yo
#exit 109
#yo
#echo \$? >> $TEST
#exit
#yoyoy

#diff -s test test2

rm -rf test_minishell test_bash

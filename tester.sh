#!/bin/bash

make re -C ~/MINISHELL/
echo '---------TESTING ECHO--------'
TEST=test_minishell
~/MINISHELL/minishell << yo
echo bla > $TEST
echo bla bla >>	$TEST 
echo -n bla bla >> $TEST
echo -nn bla bla >> $TEST 
echo -nn -nn   -n --n bla >> $TEST
echo -n 'bla' >> $TEST
echo 'bla' >> $TEST
exit
yo


TEST=test_bash
/bin/bash << yo 
echo bla > $TEST
echo bla bla >>	$TEST 
echo -n bla bla >> $TEST
echo -nn bla bla >> $TEST 
echo -nn -nn   -n --n bla >> $TEST
echo -n 'bla' >> $TEST
echo 'bla' >> $TEST
exit
yo

diff -s test_minishell test_bash

#echo '---------TESTING EXIT--------'
#TEST=test
#~/MINISHELL/minishell << yoy
#~/MINISHELL/minishell << yo
#exit 5
#yo
#echo $? > $TEST
#~/MINISHELL/minishell << yo
#exit 109
#yo
#echo $? >> $TEST
#exit
#yoy


#TEST=test2
#/bin/bash << yoyoy
#~/MINISHELL/minishell << yo
#exit 5
#yo
#echo $? > $TEST
#~/MINISHELL/minishell << yo
#exit 109
#yo
#echo $? >> $TEST
#exit
#yoyoy

#diff -s test test2

rm -rf test_minishell test_bash

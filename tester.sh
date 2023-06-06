#!/bin/bash

make -C ~/MINISHELL/
echo
echo ---------TESTING ECHO--------
echo
TEST=.test_minishell
~/MINISHELL/minishell << yo
echo bla > $TEST 
echo bla bla >> $TEST  
echo -n bla bla >> $TEST
echo -nn bla bla >> $TEST
echo -nn -nn   -n --n bla >> $TEST
echo -n 'bla' >> $TEST
echo bla -n >> $TEST
echo -n-n-n bla -n >> $TEST
echo -nnn-nnn bla >> $TEST
echo -n -nnn- bla >> $TEST
echo --n >> $TEST
echo -n --n ---n >> $TEST
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


TEST=.test_bash
/bin/bash << yo
echo bla > $TEST 
echo bla bla >> $TEST  
echo -n bla bla >> $TEST
echo -nn bla bla >> $TEST
echo -nn -nn   -n --n bla >> $TEST
echo -n 'bla' >> $TEST
echo bla -n >> $TEST
echo -n-n-n bla -n >> $TEST
echo -nnn-nnn bla >> $TEST
echo -n -nnn- bla >> $TEST
echo --n >> $TEST
echo -n --n ---n >> $TEST
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
diff -s .test_minishell .test_bash

echo
echo ---------TESTING OTHER BUILTIN--------
echo 
TEST=.test_minishell
~/MINISHELL/minishell << yo
echo BLABLA > $TEST
echo \$? 0 >> $TEST
cd ... >> $TEST
echo \$? 1 >> $TEST
cd MINISHELL/ >> $TEST
echo \$? 2 >> $TEST
pwd >> $TEST
echo \$? 3 >> $TEST
eexport >> $TEST
echo \$? 4 >> $TEST
echo \$SHELL >> $TEST
export SHELL=blabla BLO=blablibloup >> $TEST
echo \$SHELL >> $TEST
echo \$? >> $TEST
export BLO= bloblo >> $TEST
echo \$BLO >> $TEST
echo \$? >> $TEST
export BLO =bloblo >> $TEST
echo \$? >> $TEST
export = = = >> $TEST
echo \$? >> $TEST
echo \$? >> $TEST
env nthuo >> $TEST
echo \$? >> $TEST
unset SHELL BLO nhtueo
env | head -n 5 >> $TEST
echo \$? >> $TEST
exit >> $TEST
yo


TEST=.test_bash
/bin/bash << yo
echo BLABLA > $TEST
echo \$? 0 >> $TEST
cd ... >> $TEST
echo \$? 1 >> $TEST
cd MINISHELL/ >> $TEST
echo \$? 2 >> $TEST
pwd >> $TEST
echo \$? 3 >> $TEST
eexport >> $TEST
echo \$? 4 >> $TEST
echo \$SHELL >> $TEST
export SHELL=blabla BLO=blablibloup >> $TEST
echo \$SHELL >> $TEST
echo \$? >> $TEST
export BLO= bloblo >> $TEST
echo \$BLO >> $TEST
echo \$? >> $TEST
export BLO =bloblo >> $TEST
echo \$? >> $TEST
export = = = >> $TEST
echo \$? >> $TEST
echo \$? >> $TEST
env nthuo >> $TEST
echo \$? >> $TEST
unset SHELL BLO nhtueo
env | head -n 5 >> $TEST
echo \$? >> $TEST
exit >> $TEST
yo

echo
diff -s .test_minishell .test_bash

echo
echo ---------TESTING PIPES--------
echo 
TEST=.test_minishell
~/MINISHELL/minishell << yo
echo bla | wc > $TEST 
echo blanetuoh | wc -c >> $TEST  
echo -n bla bla | grep b | wc >> $TEST
ls -la | grep a | wc >> $TEST 
"echo" 'bla''bla' | wc -l >> $TEST 
exit >> $TEST
yo


TEST=.test_bash
/bin/bash << yo
echo bla | wc > $TEST 
echo blanetuoh | wc -c >> $TEST  
echo -n bla bla | grep b | wc >> $TEST
ls -la | grep a | wc >> $TEST 
"echo" 'bla''bla' | wc -l >> $TEST 
exit >> $TEST
yo

echo
diff -s .test_minishell .test_bash

echo
echo ---------TESTING EXIT STATUS--------
echo
TEST=.test_minishell
~/MINISHELL/minishell << yo
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
yo

echo $? >> $TEST

TEST=.test_bash
/bin/bash << yo
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
yo

echo $? >> $TEST

echo
diff -s .test_minishell .test_bash

echo
echo ---------TESTING REDIR---------
echo 
TEST=.test_minishell
~/MINISHELL/minishell << yo
cat < Makefile > $TEST
echo bla > file | echo blaoubla > file >> $TEST
cat file >> $TEST
echo bla >> file | echo blaoubla >> file >> $TEST
cat file >> $TEST
> file >> $TEST
> file >> $TEST
> file >> $TEST
exit >> $TEST
yo

echo $? >> $TEST

TEST=.test_bash
/bin/bash << yo
cat < Makefile > $TEST
echo bla > file | echo blaoubla > file >> $TEST
cat file >> $TEST
echo bla >> file | echo blaoubla >> file >> $TEST
cat file >> $TEST
> file >> $TEST
> file >> $TEST
> file >> $TEST
exit >> $TEST
yo

echo $? >> $TEST

echo
diff -s .test_minishell .test_bash

echo
echo ---------TESTING MISC---------
echo 
TEST=.test_minishell
~/MINISHELL/minishell << yo
cat | cat | ls > $TEST
exit nt >> $TEST
yo

echo $? >> $TEST

TEST=.test_bash
/bin/bash << yo
cat | cat | ls > $TEST
exit nt >> $TEST
yo

echo $? >> $TEST

echo
diff -s .test_minishell .test_bash

echo
echo ---------TESTING ENV -I---------
echo 
TEST=.test_minishell
env -i ~/MINISHELL/minishell << yo
env > $TEST
env nnthuoe >> $TEST
env nnth uoe >> $TEST
env ./tags >> $TEST
unset nuthou >> $TEST
env >> $TEST
unset SHELL >> $TEST
export SHELL=/bin/bash >> $TEST
export SHELL= >> $TEST
export SHELL=/bin/bash >> $TEST
export SHELL=/bin/sh >> $TEST
env | head -n 5 >> $TEST
pwd >> $TEST
cd . >> $TEST
/bin/ls >> $TEST
echo $? >> $TEST
exit nt >> $TEST
yo

echo $? >> $TEST

TEST=.test_bash
env -i /bin/bash << yo
env > $TEST
env nnthuoe >> $TEST
env nnth uoe >> $TEST
env ./tags >> $TEST
unset nuthou >> $TEST
env >> $TEST
unset SHELL >> $TEST
export SHELL=/bin/bash >> $TEST
export SHELL= >> $TEST
export SHELL=/bin/bash >> $TEST
export SHELL=/bin/sh >> $TEST
env | head -n 5 >> $TEST
pwd >> $TEST
cd . >> $TEST
/bin/ls >> $TEST
echo $? >> $TEST
exit nt >> $TEST
yo

echo $? >> $TEST

echo
diff -s .test_minishell .test_bash

echo
echo ---------TESTING CORRECTION -I---------
echo 
TEST=.test_minishell
env -i ~/MINISHELL/minishell << yo
/bin/ls > $TEST
/bin/ls >> $TEST
/bin/ls -a >> $TEST
/bin/ls -l >> $TEST
/bin/who >> $TEST
exit nt >> $TEST
yo

echo $? >> $TEST

TEST=.test_bash
env -i /bin/bash << yo
/bin/ls > $TEST
/bin/ls >> $TEST
/bin/ls -a >> $TEST
/bin/ls -l >> $TEST
/bin/who >> $TEST
exit nt >> $TEST
yo

echo $? >> $TEST

echo
diff -s .test_minishell .test_bash

rm -rf .test_minishell .test_bash file

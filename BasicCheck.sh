#!/bin/bash

# everything works=0, helgrind faild=1, valgrind faild=2, valgrind and helgrind faild=3, Compilation failed=7
DIR_PATH=${1?Error: no path given}
PROGRAM=${2?Error: no program name}
cd $DIR_PATH
output="7"
check="0"
table=" Compilation     Memory leaks     thread race"

make > "/dev/null"
if [ $? -gt 0 ];then
echo $table
echo "   Fail     FAIL	      FAIL"
exit 7
fi

valgrind --leak-check=full --error-exitcode=2 ./${PROGRAM} ${ARGUMANTS} > valgrind.txt  2>&1
if [ $? -eq 2 ];then
check="1"
fi

valgrind --tool=helgrind --error-exitcode=1 ./${PROGRAM} ${ARGUMANTS} > helgrind.txt  2>&1
if [ $? -ne 1 ];then
if [ $check -ne 1 ];then
echo $table
echo "   PASS     PASS	      PASS"
rm valgrind.txt
rm helgrind.txt
exit 0
else
echo $table
echo "   PASS     FAIL	      PASS"
exit 2
rm valgrind.txt
fi
fi

if [ $check -eq 1 ];then
output="3"
echo $table
echo "   PASS     FAIL        FAIL"
else
output="1"
echo $table
echo "   PASS     PASS        FAIL"
fi

rm valgrind.txt
rm helgrind.txt

cd - > "/dev/null"

exit $output

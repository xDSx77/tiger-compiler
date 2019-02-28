#!/bin/sh

function test_good()
{
  ./src/tc $file
  if [ $(echo $?) = 0 ]; then
    echo -e "\033[32;1m[OK] $file \033[0m"
  else
    echo -e "\033[31;1m[KO] $file \033[0m"
  fi
}

function test_error()
{
  ./src/tc $file
  i=$(echo $?)
  if [ $i = 3 ] || [ $i = 2 ]; then
    echo -e "\033[32;1m[OK] error detected in $file \033[0m"
  else
    echo -e "\033[31;1m[KO] error not detected in $file \033[0m"
  fi
}

echo "===================================================="
echo "================TESTING GOOD FILES=================="
echo "===================================================="
for file in ./tests/good/*.tig ; do
  test_good
done

echo "===================================================="
echo "================TESTING BIND FILES=================="
echo "===================================================="
for file in ./tests/bind/*.tig ; do
  test_good
done

echo "===================================================="
echo "================TESTING TYPE FILES=================="
echo "===================================================="
for file in ./tests/type/*.tig ; do
  test_good
done

echo "===================================================="
echo "===========TESTING SYNTAX ERROR IN FILES============"
echo "===================================================="
for file in ./tests/syntax/*.tig ; do
  test_error
done

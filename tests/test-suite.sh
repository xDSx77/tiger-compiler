#!/bin/sh

function test_good()
{
  ../src/tc -XA $file > test
  ../src/tc test
  if [ $(echo $?) = 0 ]; then
    echo -e "\033[32;1m[OK] $file \033[0m"
  else
    echo -e "\033[31;1m[KO] $file \033[0m"
  fi
  rm test
}

function test_error()
{
  ../src/tc $file
  i=$(echo $?)
  if [ $i = 3 ] || [ $i = 2 ]; then
    echo -e "\033[32;1m[OK] lexical/syntactic error detected in $file \033[0m"
  else
    echo -e "\033[31;1m[KO] lexical/syntactic error not detected in $file \033[0m"
  fi
}

function test_bind()
{
  ../src/tc -b $file
  if [ $(echo $?) = 4 ]; then
    echo -e "\033[32;1m[OK] binding error detected in $file \033[0m"
  else
    echo -e "\033[31;1m[KO] binding error not detected in $file \033[0m"
  fi
}

function test_type()
{
  ../src/tc $file
  if [ $(echo $?) = 5 ]; then
    echo -e "\033[32;1m[OK] typing error detected in $file \033[0m"
  else
    echo -e "\033[31;1m[KO] typing error not detected in $file \033[0m"
  fi

}

echo "===================================================="
echo "================TESTING GOOD FILES=================="
echo "===================================================="
for file in ./good/*.tig ; do
  test_good
done

echo "===================================================="
echo "===========TESTING SYNTAX ERROR IN FILES============"
echo "===================================================="
for file in ./syntax/*.tig ; do
  test_error
done

echo "===================================================="
echo "================TESTING BIND FILES=================="
echo "===================================================="
for file in ./bind/*.tig ; do
  test_bind
done

echo "===================================================="
echo "================TESTING TYPE FILES=================="
echo "===================================================="
for file in ./type/*.tig ; do
  test_type
done

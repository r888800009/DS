#!/bin/bash
g++ main.cpp
rm *_sort*.txt
files=( 501 502 503 )
for i in "${files[@]}"
do
    echo 1 $i |./a.out
    echo 2 $i |./a.out
    echo 3 $i |./a.out
done

./test.py *_sort*.txt

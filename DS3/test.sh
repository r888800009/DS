#!/bin/bash
g++ main.cpp -o main
for i in {1..10}
do
    str=$(./testGen.py)
    echo
    echo $str
    echo
    printf "1\n%s\n" "$str" | ./main
done

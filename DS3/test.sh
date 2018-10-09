#!/bin/bash
g++ main.cpp -o main
for i in {1..10}
do
    str=$(./testGen.py)
    echo $str
    printf "%d\n%s\n" 1 "$str" | ./main
done

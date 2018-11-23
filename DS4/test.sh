#!/bin/bash
g++ main_kao.cpp ; cat test.txt |./a.out;

for num in 401 402 1000 2000
do
    vimdiff ./sort$num.txt ./out/sort$num.txt
    vimdiff ./one$num.txt ./out/one$num.txt
    vimdiff ./two$num.txt ./out/two$num.txt
done



#!/bin/bash
g++ main.cpp -o main
time cat test.txt | ./main
vimdiff output204_205.txt ./test_task3.txt


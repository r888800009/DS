#!/bin/bash
g++ main.cpp -o main
./testGen.py | ./main > test-dump.txt 
less test-dump.txt


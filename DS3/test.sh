#!/bin/bash
g++ main.cpp -o main
./testGen.py | ./main 

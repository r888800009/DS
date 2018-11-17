#!/bin/bash
g++ main_kao.cpp ; cat test.txt |./a.out; diff . ./out |less

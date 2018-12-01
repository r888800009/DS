#!/usr/bin/env python
import sys

str1 = sys.argv[1]
str1 = str1.split('->')

for a, b in zip(str1[:-1], str1[1:]):
    print(a+"->"+b)


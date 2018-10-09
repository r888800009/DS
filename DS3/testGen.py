#!/usr/bin/env python
import random

def genInfix(deep):
    if deep < 0:
        return str(random.randint(0,1000))
    result = {
        1: lambda x: genInfix(x) + "+" + genInfix(x),
        2: lambda x: genInfix(x) + "-" + genInfix(x),
        3: lambda x: genInfix(x) + "*" + genInfix(x),
        4: lambda x: genInfix(x) + "/" + genInfix(x),
        5: lambda x: "(" + genInfix(x) + ")",
        6: lambda x: ' ' * random.randint(0, 6) + genInfix(x) + ' ' * random.randint(0, 6) 
    }
    return result[random.randint(1, 6)](deep - 1)
print("1\n{}".format( genInfix(6)))

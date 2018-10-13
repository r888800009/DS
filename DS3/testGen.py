#!/usr/bin/env python
import random

fileout = open("stdin.txt", "w")
ansout = open("ans.txt", "w")

def genInfix(deep):
    if deep < 0:
        return str(random.randint(1,1000))
    result = {
        1: lambda x: genInfix(x) + "+" + genInfix(x),
        2: lambda x: genInfix(x) + "-" + genInfix(x),
        3: lambda x: genInfix(x) + "*" + genInfix(x),
        4: lambda x: genInfix(x) + "/" + genInfix(x),
        5: lambda x: "(" + genInfix(x) + ")",
        6: lambda x: ' ' * random.randint(0, 6) + genInfix(x) + ' ' * random.randint(0, 6) 
    }
    return result[random.randint(1, 6)](deep - 1)
time = 50

for i in range (1, time):
    expr = "{}".format(genInfix(4))
    print("1", file = fileout)
    print(expr, file = fileout)
    print(str(eval(expr)) ,file = ansout)

for i in range (1, time):
    print("1", file = fileout)
    print("{})".format(genInfix(4)), file = fileout)

for i in range (1, time):
    print("1", file = fileout)
    print("({}".format(genInfix(4)), file = fileout)

for i in range (1, time):
    print("1", file = fileout)
    print("{} {}".format(genInfix(3), genInfix(3)), file = fileout)

for i in range (1, time):
    print("1", file = fileout)
    print("{}/0".format(genInfix(4)), file = fileout)


print("4", file = fileout)

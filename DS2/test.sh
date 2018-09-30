#!/bin/bash 

function clean1() 
{

    echo clean 
    rmdir test1
    rm test1/*
    rmdir test2
    rm test2/*
    rmdir test3
    rm test3/*
}

function init1()
{
    echo init 
    mkdir test1
    mkdir test2
    mkdir test3
}

function move1()
{
    mv c*.txt o*.txt t*.txt "./$1/"
}

clean1
init1

echo "test task1"
for i in {201..205};
do
    echo \
    "
    1
    $i
    " | ./main | grep "Total number of records"
    mv "copy$i.txt" "test$i.txt"
    echo \
    "
    1
    input$i.txt
    " | ./main | grep "Total number of records"
    diff "copy$i.txt" "test$i.txt"
done
move1 "test1"

echo 
echo "test task2"
for i in {201..205};
do
    echo \
    "
    1 $i
    2 $i
    100 1
    " | ./main | grep "Total number of records"
    mv "copy$i.txt" "test$i.txt"
    echo \
    "
    1 $i
    2 copy$i.txt
    100 1
    " | ./main | grep "Total number of records"
    diff "copy$i.txt" "test$i.txt"
done
move1 "test2"

echo 
echo "test task3"
for i in {201..204};
do
    echo \
    "
    1 $i    
    1 $(($i + 1))
    3 $i $(($i + 1))
    " | ./main | grep "Total number of records"
    j="$i"_"$(($i + 1))"
    mv "output$j.txt" "test$j.txt"
    echo \
    "
    1 input$i.txt
    1 input$(($i + 1)).txt
    3 copy$i.txt copy$(($i + 1)).txt
    " | ./main | grep "Total number of records"
    diff "output$j.txt" "test$j.txt"
done
move1 "test3"

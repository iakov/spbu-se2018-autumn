#!/bin/bash
declare -a sorts=("bubble" "insertion" "merge" "quick" "heap")
declare -a fast_sorts=("merge" "quick" "heap")

cat /dev/urandom | tr -dc 'A-Za-z0-9' | fold -w 29 | head -n5 > test_5.txt

for((i=10; i<=100000000; i*=10))
do
    cat /dev/urandom | tr -dc 'A-Za-z0-9' | fold -w 29 | head -n$i > test_$i.txt
done

echo "Number of lines is 5:" >> res.txt
for sort in "${sorts[@]}"
do
    valgrind --tool=callgrind --time-stamp=yes --log-file=result.txt ./main 5 test_5.txt $sort
    echo $sort: >> res.txt 
    cat result.txt | grep -E -o '[0-9][0-9]:[0-9][0-9]:[0-9][0-9]:[0-9][0-9].[0-9][0-9][0-9]' | tail -1 >> res.txt
    rm result.txt
done

for((i=10; i <= 10000; i*=10))
do
    echo -e "\nNumber of lines is $i:" >> res.txt
    for sort in "${sorts[@]}"
    do
        valgrind --tool=callgrind --time-stamp=yes --log-file=result.txt ./main $i test_$i.txt $sort
        echo $sort: >> res.txt 
        cat result.txt | grep -E -o '[0-9][0-9]:[0-9][0-9]:[0-9][0-9]:[0-9][0-9].[0-9][0-9][0-9]' | tail -1 >> res.txt
        rm result.txt
    done
done

for((i=100000; i <= 100000000; i*=10))
do
    echo -e "\nNumber of lines is $i:" >> res.txt
    for sort in "${fast_sorts[@]}"
    do
        valgrind --tool=callgrind --time-stamp=yes --log-file=result.txt ./main $i test_$i.txt $sort
        echo $sort: >> res.txt 
        cat result.txt | grep -E -o '[0-9][0-9]:[0-9][0-9]:[0-9][0-9]:[0-9][0-9].[0-9][0-9][0-9]' | tail -1 >> res.txt
        rm result.txt
    done
done
   

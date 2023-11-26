#!/bin/bash
FILES=testfiles
test -d ${FILES} || mkdir ${FILES}
 
for i in 100 1000 10000 100000
do
	for (( c = i; c <= i*10000; c*=10 ))
	do
		./bin/test --vertices $i --edges $c > ./${FILES}/testN${i}M${c}
	done
done

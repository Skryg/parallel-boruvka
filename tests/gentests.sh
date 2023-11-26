#!/bin/bash
FILES=testfiles
IN=${FILES}/in
OUT=${FILES}/out
FLAGS="--min-weight 10 --max-weight 1000" 

test -d ${FILES} || mkdir ${FILES}
test -d ${IN} || mkdir ${IN}
test -d ${OUT} || mkdir ${OUT}

generate() {
	DIRIN=${IN}/V${1}M${2}
	
	for i in {1..5}
	do
		if [ "$2" =  "CLI" ]; then
			echo "./bin/test --vertices $1 --clique ${FLAGS} >> ${DIRIN}"
			./bin/test --vertices $1 --clique ${FLAGS} >> ${DIRIN}
		else
			echo "./bin/test --vertices $1 --edges $2 ${FLAGS} >> ${DIRIN}"
			./bin/test --vertices $1 --edges $2 ${FLAGS} >> ${DIRIN}
		fi
	done
}

testt() {
	NAME=V${1}M${2}
	DIROUT=${OUT}/${NAME}

	../bin/main --testnum 5 < ${IN}/${NAME} > ${DIROUT}
}

generate 2000 4000
testt 2000 4000
generate 2000 100000
testt 2000 100000
generate 2000 CLI
testt 2000 CLI


generate 5000 10000
testt 5000 10000
generate 5000 800000
testt 5000 800000
generate 5000 CLI
testt 5000 CLI



generate 10000 20000
testt 10000 20000
generate 10000 10000000
testt 10000 10000000
generate 10000 CLI
testt 10000 CLI


#!/bin/bash
FILES=testfiles
IN=${FILES}/in
OUT=${FILES}/out
OUTT=${OUT}/thread

test -d ${FILES} || mkdir ${FILES}
test -d ${IN} || mkdir ${IN}
test -d ${OUT} || mkdir ${OUT}
test -d ${OUTT} || mkdir ${OUTT}

testt() {
	NAME=V${1}M${2}
	DIROUT=${OUTT}/${NAME}T${3}

	../bin/main --testnum 5 --threads ${3} < ${IN}/${NAME} > ${DIROUT}
}

testt 5000 10000 1
testt 5000 10000 2
testt 5000 10000 4
testt 5000 10000 8
testt 5000 10000 12
testt 5000 10000 16
testt 5000 10000 24
testt 5000 10000 32




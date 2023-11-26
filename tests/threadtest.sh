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
	DIROUT=${OUTT}/${NAME}

	../bin/main --testnum 5 --threads ${3} < ${IN}/${NAME} > ${DIROUT}
}

testt 5000 CLI 1
testt 5000 CLI 2
testt 5000 CLI 4
testt 5000 CLI 8
testt 5000 CLI 12
testt 5000 CLI 16
testt 5000 CLI 24
testt 5000 CLI 32




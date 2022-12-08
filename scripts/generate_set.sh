#!/bin/bash
SET_COUNT_FAM_1=$1
SET_COUNT_FAM_2=$2
MAX_NUMBER=$3
MAX_SET_COUNT=$4


echo "$SET_COUNT_FAM_1"

for (( i=1 ; i<=$SET_COUNT_FAM_1 ; i++ ));
do
    SET_COUNT=$(shuf -i 0-$MAX_NUMBER -n 1)
    SET=$SET_COUNT
    for(( j=1 ; j<=$SET_COUNT ; j++ ));
    do
        RAND=$(shuf -i 0-$MAX_NUMBER -n 1)
        SET="${SET} ${RAND}" 
    done
    echo "$SET"

done

echo "$SET_COUNT_FAM_2"
for (( i=1 ; i<=$SET_COUNT_FAM_2 ; i++ ));
do
    SET_COUNT=$(shuf -i 0-$MAX_NUMBER -n 1)
    SET=$SET_COUNT
    for(( j=1 ; j<=$SET_COUNT ; j++ ));
    do
        RAND=$(shuf -i 0-$MAX_NUMBER -n 1)
        SET="${SET} ${RAND}" 
    done
    echo "$SET"

done

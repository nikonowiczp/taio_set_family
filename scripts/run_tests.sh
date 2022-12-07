#!/bin/bash

# Run this script to compile and run using the example_set.
# Your working directory must be the bin folder

ALL_RESULTS_FILE=all.out
cd ../test_sets && rm *.out > /dev/null 2>&1

for FILE in ./* ; do
	[ -e "$FILE" ] || continue
	if [[ "$ALL_RESULTS_FILE" == "$FILE" ]];
	then
		continue
	fi
	echo "Parsing file ${FILE}. Output will be written to ${FILE}.out"
	
       	../bin/main/taio_set_family $FILE > ${FILE}.out
	cat ${FILE}.out >> $ALL_RESULTS_FILE
done


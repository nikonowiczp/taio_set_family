#!/bin/bash

# Run this script to compile and run using the example_set.
# Your working directory must be the bin folder
mkdir ../bin > /dev/null 2>&1
rm -rf ../bin/* > /dev/null 2>&1
cd ../bin && cmake ../src .  && make && mv ../bin/main/taio_set_family .. && rm -rf ../bin/* && mv ../taio_set_family ../bin

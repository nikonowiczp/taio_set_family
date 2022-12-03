#!/bin/bash

# Run this script to compile and run using the example_set.
# Your working directory must be the folder this file is in

cmake ./src ./bin && cd ./bin && make && ./main/taio_set_family ../example_set && cd .. 

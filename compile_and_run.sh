#!/bin/bash

# Run this script to compile and run using the example_set.
# Your working directory must be the bin folder

cmake ../src .  && make && ./main/taio_set_family ../example_set

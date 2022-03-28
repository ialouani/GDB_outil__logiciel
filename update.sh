#!/bin/bash
LD_LIBRARY_PATH=/usr/local/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
export LD_LIBRARY_PATH
./example_dynamique

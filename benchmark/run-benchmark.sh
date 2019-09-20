#!/bin/bash
cmake CMakeList.txt
make
./SpyCBlock-benchmarck --benchmark_out=result/json/i5-6300U@4x_3GH_gcc7.4.0.json --benchmark_out_format=json

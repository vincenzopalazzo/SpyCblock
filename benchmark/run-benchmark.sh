#!/bin/bash
cmake CMakeLists.txt
make 
./SpyCBlock-benchmarck --benchmark_out=result/json/i5-6300U@4x_3GH_gcc8.2.0.json --benchmark_out_format=json

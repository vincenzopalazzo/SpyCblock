#!/bin/sh
echo '\n\n----------------------| SpyCBlock |---------------------------\n\n'
echo 'Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com'
echo 'Distributed under the Apache License Version 2.0 software license,'
echo 'see https://www.apache.org/licenses/LICENSE-2.0.txt\n\n\n'
echo 'Welcome into compiler for SpyCBlock, it is a simple parser for bicoin-core'
echo 'Author https://github.com/vincenzopalazzo'
sleep 5
./dependences.sh
./update-submodule.sh
cd ..
mkdir build
cd build && cmake ..
make
cd ..
cp conf.properties build
cp conf-rpc.properties build

#!/bin/sh
print '\n\n----------------------| SpyCBlock |---------------------------\n\n'
print 'Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com'
print 'Distributed under the Apache License Version 2.0 software license,'
print 'see https://www.apache.org/licenses/LICENSE-2.0.txt\n\n\n'
print 'Welcome into compiler for SpyCBlock, it is a simple parser for bicoin-core'
print 'Author https://github.com/vincenzopalazzo'
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

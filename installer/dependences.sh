#!/bin/bash
echo 'Welcome into installer SpyCBlock a simple bicoin-core parser'
echo 'Author https://github.com/vincenzopalazzo'

git --version
GIT_IS_AVAILABLE=$?
if [ $GIT_IS_AVAILABLE -eq 0 ]; then
    # PS1 Line to show current Git Branch in the Prompt
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\[\033[01;32m\]$(__git_ps1 " (%s)")\[\033[00m\]\$ '
else
    # Original PS1 Line
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
fi

echo '----------- Install gtest library --------------------'
echo ''
echo ''
echo ''
echo ''

git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
sudo make install
cd ..
cd ..
sudo rm -r googletest


echo '-------------- Install glog library -------------------'
echo ''
echo ''
echo ''
echo ''

sudo apt-get purge libgflags-dev -y
sudo apt install libgflags-dev -y

git clone https://github.com/google/glog.git
cd glog
mkdir build && cd build
cmake -DGFLAGS_NAMESPACE=google -DCMAKE_CXX_FLAGS=-fPIC ..
make && sudo make install
cmake -DBUILD_SHARED_LIBS:BOOL=ON ..
cmake --build

cd ..
./autogen.sh
./configure
make -j8
sudo make install
cd ..
sudo rm -r glog
echo 'The dependecis are OK'

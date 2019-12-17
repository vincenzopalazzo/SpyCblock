cd ..
git submodule update --init --recursive
git submodule update --recursive --remote --merge --force
sudo rm -r include/spycblockrpc/lib/*
cd include/spycblockrpc
git submodule update --init --recursive
cd ..
cd ..
cd installer

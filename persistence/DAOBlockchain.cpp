//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//
#include "DAOBlockchain.h"
#include "DAOException.h"

#include<experimental/filesystem>

namespace fs = std::experimental::filesystem;

vector<spyCBlock::Block> spyCBlock::DAOBlockchain::loadBlocks(string path) {
    if(path.empty()){
        LOG(ERROR) << "The argument function is null";
        throw new DAOException("The argument function loadBlocks from DAOBlockchain is Empity");
    }
    if(fs::exists(path)){
        if(fs::is_directory(path))
        LOG(INFO) << "Path exits and the path is the directory, the path is:  " << path;
        fs::path pathObject = path;
        //TODO do arrived here
    }
}

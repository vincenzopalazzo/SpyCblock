//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//

#ifndef SPYCBLOCK_DAOBLOCKCHAIN_H
#define SPYCBLOCK_DAOBLOCKCHAIN_H

#include "IDAOBlockchain.h"

using namespace std;

namespace spyCBlock{

    class DAOBlockchain : IDAOBlockchain{

    public:
        vector<Block> loadBlocks(string path) override;

    };

}


#endif //SPYCBLOCK_DAOBLOCKCHAIN_H

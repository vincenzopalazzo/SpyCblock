// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef DAOMANAGERGRAPH_H
#define DAOMANAGERGRAPH_H

#include "../IDAOBlockchain.h"

namespace spyCBlock
{
    class DAOManagerGraph : IDAOBlockchain
    {
       public:

           bool saveBlock(const std::string &inputPath, const std::string &outputPath) override;

           bool saveBlockCompress(const string &inputPath, const string &outputPath) override;
    };
}


#endif // DAOMANAGERGRAPH_H

#ifndef DAOMANAGERGRAPH_H
#define DAOMANAGERGRAPH_H

#include "../IDAOBlockchain.h"

namespace spyCBlock
{
    class DAOManagerGraph : IDAOBlockchain
    {
       public:
           bool saveBlock(string inputPath, string outputPath, int &height) override;

    };
}


#endif // DAOMANAGERGRAPH_H

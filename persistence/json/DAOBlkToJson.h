#ifndef DAOBLKTOJSON_H
#define DAOBLKTOJSON_H

#include<experimental/filesystem>

#include "../IDAOBlockchain.h"

using namespace std;
namespace fs = std::experimental::filesystem;

namespace spyCBlock{


    class DAOFileBlkJson : public IDAOBlockchain{

    private:

      int counterBlock = 0;

      vector<spyCBlock::Block>* readBlock(fs::directory_entry entry, int &conuterBlock);

      bool isBlockFileBlk(fs::directory_entry entry);

      bool convertVectorBlockIntoJson(vector<Block> *blockFileBlk, string outputPath, string nameFile);

      string getNameFile(fs::directory_entry entry);

    public:

        DAOFileBlkJson();

        virtual ~DAOFileBlkJson();

        vector<Block> loadBlocks(string path) override;

        bool saveBlock(string inputPath, string outputPath) override;
    };

}



#endif // DAOBLKTOJSON_H

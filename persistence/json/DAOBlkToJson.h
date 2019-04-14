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
      int currentFile = 0;
      int fileBlkReaded = 0;

      vector<spyCBlock::Block>* readBlock(fs::directory_entry entry, int &conuterBlock);

      shared_ptr<vector<Block>> readBlock(string path, int &conuterBlock);

      bool isBlockFileBlk(fs::directory_entry entry);

      bool isBlockFileBlk(string path);

      bool convertVectorBlockIntoJson(shared_ptr<vector<Block>> blockFileBlk, string outputPath, string nameFile);

      string getNameFile(string path);

      string getNameFile(fs::directory_entry entry);

      //Return the path of file blk
      string nameFileSearched(string pathInput);

    public:

        DAOFileBlkJson();

        virtual ~DAOFileBlkJson();

        vector<Block> loadBlocks(string path) override;

        bool saveBlock(string inputPath, string outputPath) override;
    };

}



#endif // DAOBLKTOJSON_H

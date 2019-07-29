#include <glog/logging.h>

#include "DAOUtilTest.h"
#include "../../persistence/DAOException.h"

namespace fs = std::experimental::filesystem;
using namespace spyCBlock;
using namespace std;

std::vector<spyCBlock::Block> spyCBlock::DAOUtilTest::loadBlocks(string pathInput)
{
  if(pathInput.empty())
  {
    LOG(ERROR) << "The path is empty";
  }

  vector<Block> blockchainBloks;

      if (fs::exists(pathInput))
      {
          if (fs::is_directory(pathInput))
          {
              fs::path pathObject = pathInput;
              LOG(INFO) << "Path exits and the path is the directory, the path is:  " << pathInput;
              for (auto &p: fs::directory_iterator(pathObject))
              {
                  LOG(INFO) << "The file examinad is: " << p;
                  vector<Block> container = readBlocks(p);

                  if (!container.empty())
                  {
                      LOG(INFO) << "I added block readed in this file " << pathInput;
                      LOG(INFO) << "Dimension blockchain before join " << blockchainBloks.size();
                      for(auto& block : container)
                      {
                        blockchainBloks.emplace_back(block);
                      }
                      LOG(INFO) << "Dimension blockchain after join " << blockchainBloks.size();
                  }
              }
              return blockchainBloks;
          }
          LOG(ERROR) << "The path not finisced with a directory";
          throw DAOException("The path not finisced with a directory");

      }
      LOG(INFO) << "The path not exist";
      throw DAOException("The path not exist");
}

bool DAOUtilTest::isBlockFileBlk(experimental::filesystem::__cxx11::directory_entry &entry)
{
  string pathFile = entry.path();
  string tmpPathFile(pathFile);
  LOG(INFO) << "The path in string is: " << pathFile;
  string nameFile = tmpPathFile.substr(tmpPathFile.size() - 12, tmpPathFile.size());
  LOG(INFO) << "The name file in path is " << nameFile;
  bool containsBlk = nameFile.find("blk") != string::npos;
  bool containsExstension = nameFile.find(".dat") != string::npos;
  return containsBlk && containsExstension;
}

std::vector<Block> DAOUtilTest::readBlocks(fs::directory_entry entry) {
    if (!isBlockFileBlk(entry))
    {
        LOG(INFO) << "This path not contain a file blk";
        return vector<Block>();
    }
    ifstream stream(entry.path());

    if (stream.is_open())
    {
        LOG(INFO) << "File in this path " << entry.path() << " is open";
        vector<Block> blocksFile;
        while (!stream.eof())
        {
            blocksFile.emplace_back(Block{});
            Block block = blocksFile.back();
            block.decode(stream);

        }
        stream.close();
        LOG(WARNING) << "Readed a " << blocksFile.size() << " files";
        return blocksFile;
    }
    stream.close();
    LOG(ERROR) << "File not open";
    throw new DAOException("File not open");
}

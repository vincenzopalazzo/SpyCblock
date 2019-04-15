//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//
#include <utility>

#include "DAOBlockchain.h"
#include "DAOException.h"

using namespace spyCBlock;

vector<unique_ptr<Block>> spyCBlock::DAOBlockchain::loadBlocks(string &path) {
    if (path.empty())
    {
        LOG(ERROR) << "The argument function is null";
        throw DAOException("The argument function loadBlocks from DAOBlockchain is Empity");
    }

    vector<unique_ptr<Block>> blockchainBloks;

    if (fs::exists(path))
    {
        if (fs::is_directory(path))
        {
            fs::path pathObject = path;
            LOG(INFO) << "Path exits and the path is the directory, the path is:  " << path;
            for (auto &p: fs::directory_iterator(pathObject))
            {
                LOG(INFO) << "The file examinad is: " << p;
                vector<unique_ptr<Block>> vector1 = readBlock(p);

                if (!vector1.empty())
                {
                    LOG(INFO) << "I added block readed in this file " << path;
                    LOG(INFO) << "Dimension blockchain before join " << blockchainBloks.size();
                    for(auto& block : vector1)
                    {
                      blockchainBloks.push_back(move(block));
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

bool spyCBlock::DAOBlockchain::saveBlock(string inputPath, string outputPath)
{
  //do nothing
}

std::vector<unique_ptr<Block>> spyCBlock::DAOBlockchain::readBlock(fs::directory_entry entry) {
    if (!isBlockFileBlk(entry))
    {
        LOG(INFO) << "This path not contain a file blk";
        return vector<unique_ptr<Block>>();
    }
    ifstream stream(entry.path());

    if (stream.is_open())
    {
        LOG(INFO) << "File in this path " << entry.path() << " is open";
        vector<unique_ptr<Block>> blocksFile;
        while (!stream.eof())
        {
            unique_ptr<Block> block(new Block());
            block->decode(stream);

            string previuHashBlock = block->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
            string genesiBlock = "0000000000000000000000000000000000000000000000000000000000000000";

            if(isBlockGenesi(entry, block))
            {
                LOG(WARNING) << "Finde genesy block";
                blocksFile.push_back(move(block));
            }
            if(previuHashBlock != genesiBlock)
            {
                 blocksFile.push_back(move(block));
            }
        }
        stream.close();
        LOG(WARNING) << "Readed a " << blocksFile.size() << " files";
        return blocksFile;
    }
    stream.close();
    LOG(ERROR) << "File not open";
    throw new DAOException("File not open");
}

bool spyCBlock::DAOBlockchain::isBlockFileBlk(fs::directory_entry &entry)
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

bool spyCBlock::DAOBlockchain::isBlockGenesi(fs::directory_entry &entry, unique_ptr<Block> &genericBlock)
 {
     string pathFile = entry.path();
     string tmpPathFile(pathFile);
     LOG(INFO) << "The path in string is: " << pathFile;
     string nameFile = tmpPathFile.substr(tmpPathFile.size() - 12, tmpPathFile.size());
     LOG(INFO) << "The name file in path is " << nameFile;
     string fileBlkWithBlockGenesi = "blk00000.dat";
     if(nameFile == fileBlkWithBlockGenesi)
       {
           string serchingGenesiBlock = genericBlock->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
           string genesiBlock = "0000000000000000000000000000000000000000000000000000000000000000";
           return serchingGenesiBlock == genesiBlock;
       }
  return false;
}

spyCBlock::DAOBlockchain::~DAOBlockchain() = default;

spyCBlock::DAOBlockchain::DAOBlockchain() = default;


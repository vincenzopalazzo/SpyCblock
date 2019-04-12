//
// Created by https://github.com/vincenzopalazzo on 3/7/19.
//
#include "DAOBlockchain.h"
#include "DAOException.h"


vector<spyCBlock::Block> spyCBlock::DAOBlockchain::loadBlocks(string path) {
    if (path.empty()) {
        LOG(ERROR) << "The argument function is null";
        throw new DAOException("The argument function loadBlocks from DAOBlockchain is Empity");
    }
    vector<Block> blockchainBloks = vector<Block>();
    if (fs::exists(path)) {
        if (fs::is_directory(path)) {
            fs::path pathObject = path;
            LOG(INFO) << "Path exits and the path is the directory, the path is:  " << path;
            for (auto &p: fs::directory_iterator(pathObject)) {
                LOG(INFO) << "The file examinad is: " << p;
                vector<Block> *vector1 = readBlock(p);
                if (vector1 != nullptr) {
                    LOG(INFO) << "I added block readed in this file " << path;
                    LOG(INFO) << "Dimension blockchain before join " << blockchainBloks.size();
                    blockchainBloks.insert(blockchainBloks.end(), vector1->begin(), vector1->end());
                    LOG(INFO) << "Dimension blockchain after join " << blockchainBloks.size();
                }
            }
            return blockchainBloks;
        }
        LOG(ERROR) << "The path not finisced with a directory";
        throw new DAOException("The path not finisced with a directory");

    }
    LOG(INFO) << "The path not exist";
    throw new DAOException("The path not exist");
}

bool spyCBlock::DAOBlockchain::saveBlock(string inputPath, string outputPath)
{
  //do nothing
}

std::vector<spyCBlock::Block> *spyCBlock::DAOBlockchain::readBlock(fs::directory_entry entry) {
    if (!isBlockFileBlk(entry)) {
        LOG(INFO) << "This path not contain a file blk";
        return nullptr;
    }
    ifstream *stream = new ifstream(entry.path());
    if (stream->is_open()) {
        LOG(INFO) << "File in this path " << entry.path() << " is open";
        vector<Block> *blocksFile = new vector<Block>();
        while (!stream->eof()) {
            Block *block = new Block();
            block->decode(*stream);
            string previuHashBlock = block->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
            string genesiBlock = "0000000000000000000000000000000000000000000000000000000000000000";
            if(isBlockGenesi(entry, block)){
                LOG(WARNING) << "Finde genesy block";
                blocksFile->push_back(*block);
              }
            if(previuHashBlock != genesiBlock){
                 blocksFile->push_back(*block);
              }
            delete block;
        }
        LOG(WARNING) << "Readed a " << blocksFile->size() << " files";
        return blocksFile;
    }
    LOG(ERROR) << "File not open";
    throw new DAOException("File not open");
}

bool spyCBlock::DAOBlockchain::isBlockFileBlk(fs::directory_entry entry)
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

bool spyCBlock::DAOBlockchain::isBlockGenesi(fs::directory_entry entry, spyCBlock::Block *genericBlock)
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


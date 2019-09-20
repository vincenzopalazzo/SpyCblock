//@author https://github.com/vincenzopalazzo

#include <iostream>
#include <regex>

#include "block.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;

void Block::decode(std::ifstream &stream) {
    Unserialize(stream, this->magicNum);
    LOG(INFO) << "Magic number readed: " << magicNum;
    Unserialize(stream, this->blocksize);
    LOG(INFO) << "Block size readed: " << blocksize;
    blockHeader.decode(stream);

    this->numberRawTransaction.decode(stream);

    LOG(INFO) << "number raw transanctions into blok whit previous hash " << this->blockHeader.getPreviousBlockHeaderHash().GetHex();

    if (static_cast<int>(numberRawTransaction.getValue()) == -1) {

        LOG_IF(FATAL, (static_cast<int>(numberRawTransaction.getValue()) == -1)) << "Error numberRaw Transaction = " << numberRawTransaction.getValue();
        //TODO segnalare errore lanciando un eccezione
        return;
    }
    rawTransactions.clear();
    rawTransactions.reserve(numberRawTransaction.getValue());
    for (int i = 0; i < static_cast<int>(numberRawTransaction.getValue()); i++) {
        LOG(INFO) << "Readed raw transaction number " <<  i + 1;
        rawTransactions.emplace_back(RawTransaction{});
        RawTransaction& transaction = rawTransactions.back();
        transaction.decode(stream);
    }
    LOG(INFO) << "End block read whit previus hash " << this->blockHeader.getPreviousBlockHeaderHash().GetHex();

    //create hash block
    string deserializeForm = toSerealizationForm();
    this->hashBlock = CryptoSingleton::getIstance().getHash256(deserializeForm);
}

string Block::toSerealizationForm()
{
  return blockHeader.toSerealizationForm();
}

string Block::toString() {
  string stringForm = "-------- BLOCK --------- \n";
  stringForm += "Magic number: \n";
  stringForm += "Block Size: \n";
  stringForm += blockHeader.toString();
  stringForm += "number Raw Transaction: \n";
  stringForm += to_string(numberRawTransaction.getValue());
  stringForm += "\n";
  for (RawTransaction &raw : this->rawTransactions)
  {
      stringForm += raw.toString(); //TODO possible generated exception
  }
  return stringForm;
}

void Block::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
  writerJson.StartObject();

  writerJson.Key("hashBlock");
  writerJson.String(this->hashBlock.c_str());

  writerJson.Key("height");
  writerJson.Int(this->heightBlock);

  writerJson.Key("magicnumber");
  writerJson.Int(this->magicNum);

  writerJson.Key("blockSize");
  writerJson.Int(this->blocksize);

  writerJson.Key("blockHeader");
  this->blockHeader.toJson(writerJson);

  writerJson.Key("numberRawTransactions");
  writerJson.Uint64(this->numberRawTransaction.getValue());

  writerJson.Key("rawTransactions");
  writerJson.StartArray();

  for(RawTransaction &rawTransaction : this->rawTransactions)
  {
    rawTransaction.toJson(writerJson);
  }

  writerJson.EndArray();

  writerJson.EndObject();
}

//TODO generalize this method, with type of deserialization
void Block::toGraphForm(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  wrapper.addInformationLink("height:" + to_string(this->heightBlock));

  for(RawTransaction& rawTx : this->rawTransactions)
  {
    LOG(INFO) << "Call toGraphForm RawTransaction";
    rawTx.toGraphForm(outputStream, wrapper);
  }
}

void Block::toTransactionsGraph(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  wrapper.addInformationLink("height:" + to_string(this->heightBlock));
  wrapper.setDelimitator("|-|");

  for(RawTransaction& rawTx : this->rawTransactions)
  {
    LOG(INFO) << "Call toGraphForm RawTransaction";
    rawTx.toTransactionsGraph(outputStream, wrapper);
  }
}

string Block::convertMagicNumber() {
    stringstream stream;
    stream << hex << magicNum;
    string magicnumberString = stream.str();
    return magicnumberString;
}

//getter and setter
int32_t Block::getMagicNum() const {
    return magicNum;
}

int32_t Block::getBlocksize() const {
    return blocksize;
}

const BlockHeader &Block::getBlockHeader() const {
    return blockHeader;
}

const DVarInt &Block::getNumberRawTransaction() const {
    return numberRawTransaction;
}

const vector<RawTransaction> &Block::getRawTransactions() const {
  return rawTransactions;
}

int32_t Block::getHeightBlock() const
{
  return heightBlock;
}

void Block::setHeightBlock(int32_t heightBlock)
{
  this->heightBlock = heightBlock;
}

string Block::getHashBlock() const
{
  return hashBlock;
}

bool Block::operator==(const Block &rhs) const {
    return magicNum == rhs.magicNum &&
           blocksize == rhs.blocksize &&
           blockHeader == rhs.blockHeader;
}

bool Block::operator!=(const Block &rhs) const {
    return !(rhs == *this);
}

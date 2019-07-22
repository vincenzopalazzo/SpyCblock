#include <iostream>
#include <regex>

#include "block.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;
using namespace nlohmann;

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */

void Block::decode(std::ifstream &stream) {
    Unserialize(stream, this->magicNum);
    LOG(INFO) << "Magic numbar readed: " << magicNum;
    Unserialize(stream, this->blocksize);
    LOG(INFO) << "Block size readed: " << blocksize;
    blockHeader.unserialize(stream);

    this->numbarRawTransaction.decode(stream);

    LOG(INFO) << "Numbar raw transanctions into blok whit previous hash " << this->blockHeader.getPreviousBlockHeaderHash().GetHex();

    if (static_cast<int>(numbarRawTransaction.getValue()) == -1) {

        LOG_IF(FATAL, (static_cast<int>(numbarRawTransaction.getValue()) == -1)) << "Error numbarRaw Transaction = " << numbarRawTransaction.getValue();
        //TODO segnalare errore lanciando un eccezione
        return;
    }
    rawTransactions.clear();
    //Reserve the space for the memory, with exclude new allocation memore and the move the pointer
    rawTransactions.reserve(numbarRawTransaction.getValue());
    //Refactore with this conversation in reddit
    // https://www.reddit.com/r/cpp_questions/comments/bd3b9b/advice_on_memory_management/
    for (int i = 0; i < static_cast<int>(numbarRawTransaction.getValue()); i++) {
        LOG(INFO) << "Readed raw transaction numbar " <<  i + 1;
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
  stringForm += "Magic Numbar: \n";
  stringForm += "Block Size: \n";
  stringForm += blockHeader.toString();
  stringForm += "Numbar Raw Transaction: \n";
  stringForm += to_string(numbarRawTransaction.getValue());
  stringForm += "\n";
  for (RawTransaction &raw : this->rawTransactions)
  {
      stringForm += raw.toString(); //TODO possible generated exception
  }
  return stringForm;
}

json Block::toJsonLite()
{
  return json::object({
                        {"magicNumbar", magicNum},
                        {"blockSize", blocksize},
                        {"blockHeader", blockHeader.toJoson()}
                      });
}

json Block::toJsonFat()
{
  json jsonTransactionRaw;
  for (RawTransaction &raw : this->rawTransactions)
  {
      jsonTransactionRaw.push_back(raw.toJson());
  }

  json jsonFat = {
      {"magicNumbar", magicNum},
      {"blockSize", blocksize},
      {"blockHeader", blockHeader.toJoson()},
      {"numbarRawTransactions", numbarRawTransaction.getValue()},
      {"heightBlock", heightBlock}, //this value for default is -1
      {"hashBlock", hashBlock},
  };

  jsonFat["rawTransactions"] = jsonTransactionRaw;
  return jsonFat;
}

string Block::convertMagicNumbar() {
    stringstream stream;
    stream << hex << magicNum;
    string magicNumbarString = stream.str();
    return magicNumbarString;
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

const DVarInt &Block::getNumbarRawTransaction() const {
    return numbarRawTransaction;
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

//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <cstdint>
#include <sstream>

#include "RawTransaction.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;
using namespace nlohmann;

void RawTransaction::decode(std::ifstream &stream)
{
    Unserialize(stream, version);
    LOG(INFO) << "Version raw transaction " << version;
    this->numberTxIn.decode(stream);
    LOG(INFO) << "Numbar transaction input in raw transaction " << numberTxIn.getValue();
    txIn.clear();

    txIn.reserve(numberTxIn.getValue());
    for(int i = 0; i < static_cast<int>(this->numberTxIn.getValue()); i++)
    {
        txIn.emplace_back(TransactionInput{});
        TransactionInput& transaction = txIn.back();
        transaction.decode(stream);
    }
    this->numberTxOut.decode(stream);
    LOG(INFO) << "Numbar transaction output in raw transaction " << numberTxOut.getValue();

    txOut.clear();
    txOut.reserve(numberTxOut.getValue());

    for(int i = 0; i < static_cast<int>(numberTxOut.getValue()); i++)
    {
        txOut.emplace_back(TransactionOutput{});
        TransactionOutput& transactionOutput = txOut.back();
        transactionOutput.decode(stream);

    }
    //Create a wrapper
    Unserialize(stream, this->lockTime);

    //Create additional information
    string serializationForm = toSerealizationForm();
    this->hashRawTransaction = CryptoSingleton::getIstance().getHash256(serializationForm);
}

string RawTransaction::toSerealizationForm() const
{

  string hexForm = SerializationUtil::toSerealizeForm(this->version);
  hexForm += SerializationUtil::toSerealizeForm(this->numberTxIn);
  for(TransactionInput txInput : this->txIn)
  {
    hexForm += txInput.toSerealizationForm();
  }
  hexForm += SerializationUtil::toSerealizeForm(this->numberTxOut);
  for(TransactionOutput txOutput : this->txOut)
  {
     hexForm += txOutput.toSerealizationForm();
  }
  hexForm += SerializationUtil::toSerealizeForm(this->lockTime);

  return hexForm;
}

string RawTransaction::toString() {
    string stringForm =  "---------- Raw Transaction ----------\n";
    stringForm += "Version: ";
    stringForm += to_string(version);
    stringForm += "---------- Transaction Input ----------\n";
    stringForm += "Number Transaction In: ";
    stringForm += to_string(numberTxIn.getValue());
    for(TransactionInput txInput : this->txIn)
    {
        stringForm += txInput.toString();
    }
    stringForm += "---------- Transaction Output ----------\n";
    stringForm += "Number Transaction out: ";
    stringForm += to_string(numberTxOut.getValue());
    for(TransactionOutput txOutput : this->txOut)
    {
        stringForm += txOutput.toString();
    }
    stringForm += to_string(this->lockTime);
    return stringForm;
}

json RawTransaction::toJson()
{

  json jsonRawTransaction =  json::object({
                        {"version", version},
                        {"numbarTxInput", this->numberTxIn.getValue()},
                        {"numbarTxInput", this->numberTxOut.getValue()},
                        {"lockTime", this->lockTime},
                        {"hashRawTransaction", this->hashRawTransaction},
                      });

  //TODO this refactoring required more attention on Json form test
  json txInputjson;
  for(TransactionInput txInput : this->txIn)
  {
      json txInputJsonSingle = txInput.toJson();
      txInputjson.emplace_back(txInputJsonSingle);
  }

  //TODO this refactoring required more attention on Json form test
  json txOutjson;
  for(TransactionOutput txOutput : this->txOut)
  {
    json txOutputJsonSingle = txOutput.toJson();
    txOutjson.emplace_back(txOutputJsonSingle);
  }

  jsonRawTransaction["inputTransactions"] = txInputjson;
  jsonRawTransaction["outputTransaction"] = txOutjson;
  return jsonRawTransaction;
}

//Getter and setter
int32_t RawTransaction::getVersion() const
{
    return version;
}

const DVarInt &RawTransaction::getNumberTxIn() const
{
    return numberTxIn;
}

const vector<TransactionInput> &RawTransaction::getTxIn() const
{
    return txIn;
}

const DVarInt &RawTransaction::getNumberTxOut() const
{
    return numberTxOut;
}

const vector<TransactionOutput> &RawTransaction::getTxOut() const
{
  return txOut;
}

string RawTransaction::getHashRawTransaction() const
{
  return hashRawTransaction;
}

uint32_t RawTransaction::getLockTime() const
{
    return lockTime;
}




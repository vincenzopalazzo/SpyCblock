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

    if(numberTxIn.getValue() == 0)
    {
      LOG(WARNING) << "Findend the marker";

      this->numberTxIn.decode(stream);

      if(numberTxIn.getValue() == 1)
      {
        LOG(WARNING) << "Findend the flag";
        type = Type::WITNESS;
         numberTxIn.decode(stream); //With this code I readed the numbar tranaction input in Witnees transaction type;
      }
    }else{
      type = Type::PRIMITIVE;
    }

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

    if(type == Type::WITNESS){
      txsWitness.reserve(numberTxIn.getValue());
      for(int i = 0; i < static_cast<int>(numberTxIn.getValue()); i++)
      {
          txsWitness.emplace_back(TransactionWitness{});
          TransactionWitness& txw = txsWitness.back();
          txw.decode(stream);
      }
    }

    //TODO Create a wrapper
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
  for(TransactionInput &txInput : this->txIn)
  {
      json txInputJsonSingle = txInput.toJson();
      txInputjson.emplace_back(txInputJsonSingle);
  }

  //TODO this refactoring required more attention on Json form test
  json txOutjson;
  for(TransactionOutput &txOutput : this->txOut)
  {
    json txOutputJsonSingle = txOutput.toJson();
    txOutjson.emplace_back(txOutputJsonSingle);
  }

  jsonRawTransaction["inputTransactions"] = txInputjson;
  jsonRawTransaction["outputTransaction"] = txOutjson;
  return jsonRawTransaction;
}

void RawTransaction::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
  writerJson.StartObject();

  writerJson.Key("hashRawTransaction");
  writerJson.String(this->hashRawTransaction.c_str());

  writerJson.Key("version");
  writerJson.Int(this->version);

  writerJson.Key("numbarTxInput");
  writerJson.Uint64(this->numberTxIn.getValue());

  writerJson.Key("txInput");
  writerJson.StartArray();

  for(TransactionInput &txInput : this->txIn)
  {
    txInput.toJson(writerJson);
  }

  writerJson.EndArray();

  writerJson.Key("numbarTxOutput");
  writerJson.Uint64(this->numberTxOut.getValue());

  writerJson.Key("txOutput");
  writerJson.StartArray();

  for(TransactionOutput &txOutput : this->txOut)
  {
    txOutput.toJson(writerJson);
  }

  writerJson.EndArray();

  writerJson.Key("lockTime");
  writerJson.Uint(this->lockTime);

  writerJson.EndObject();
}

uint8_t RawTransaction::getFlag() const
{
  return flag;
}

uint8_t RawTransaction::getMarker() const
{
  return marker;
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




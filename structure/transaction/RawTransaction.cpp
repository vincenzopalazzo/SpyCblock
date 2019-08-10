//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//
#include <cstdint>
#include <sstream>

#include "../../include/spycblockrpc/core/graph/TransactionGraph.h"

#include "RawTransaction.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"
#include "../../persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../../persistence/graph/transactions/TransactionsRawGraph.h"

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
    LOG(WARNING) << "Hash tx: " << hashRawTransaction;
}

string RawTransaction::toSerealizationForm() const
{

  string hexForm = SerializationUtil::toSerealizeForm(this->version);

  hexForm.append(SerializationUtil::toSerealizeForm(this->numberTxIn));
  for(TransactionInput txInput : this->txIn)
  {
    hexForm.append(txInput.toSerealizationForm());
  }
  hexForm.append(SerializationUtil::toSerealizeForm(this->numberTxOut));
  for(TransactionOutput txOutput : this->txOut)
  {
     hexForm.append(txOutput.toSerealizationForm());
  }

  hexForm.append(SerializationUtil::toSerealizeForm(this->lockTime));
  //Debug hex
  if(this->type == RawTransaction::Type::WITNESS)
  {
    LOG(ERROR) << "\n****** HEX segregated witness *************\n"
                    + hexForm
                    + "\n****************************";
  }
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

//can be removed
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

void RawTransaction::toGraphForm(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  //TODO add method for add information
 /* vector<string> informations;
  informations.emplace_back(wrapper.getLinkInformations().begin(), wrapper.getLinkInformations().end());
  informations.emplace_back("RawTxID: " + this->hashRawTransaction);
  informations.emplace_back("lockTime: " + to_string(this->lockTime));
  string witness = "false";
  if(type == Type::WITNESS)
  {
      witness = "true";
  }
  informations.emplace_back("witness: " + witness);
  wrapper.setLinkInformations(informations);*/

/* this is more difficulte
  if(this->txIn.size() > 1 && this->txOut.size() > 1){
    return;
  }
*/
  for(TransactionInput &txInput : this->txIn)
  {
    txInput.toGraphForm(outputStream, wrapper);
    for(TransactionOutput &txOutput : this->txOut)
    {
      txOutput.toGraphForm(outputStream, wrapper);
      spyCBlockRPC::TransactionGraph transaction;
      transaction.buildTransaction(wrapper);
      transaction.serialize(outputStream);
    }
  }

}

void RawTransaction::toTransactionsGraph(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  /*
  vector<string> informations;
  informations.emplace_back(wrapper.getLinkInformations().begin(), wrapper.getLinkInformations().end());
  informations.emplace_back("RawTxID: " + this->hashRawTransaction);
  informations.emplace_back("lockTime: " + to_string(this->lockTime));
  string witness = "false";
  if(type == Type::WITNESS)
  {
      witness = "true";
  }
  informations.emplace_back("witness: " + witness);
  wrapper.setLinkInformations(informations);*/
/* this is more difficulte
  if(this->txIn.size() > 1 && this->txOut.size() > 1){
    return;
  }
*/
  wrapper.setTo(this->hashRawTransaction);
  bool setValue = false;
  for(TransactionOutput txOut : this->txOut)
  {
    if(setValue == false)
    {
      txOut.toTransactionsGraph(outputStream, wrapper);
      setValue = true;
    }
  }

  for(TransactionInput inputTx : this->txIn)
  {
    inputTx.toTransactionsGraph(outputStream, wrapper);

    TransactionsRawGraph transactioGraph;
    transactioGraph.buildTransaction(wrapper);
    transactioGraph.serialize(outputStream);
  }

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




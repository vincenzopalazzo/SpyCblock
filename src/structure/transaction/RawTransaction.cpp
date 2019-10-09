// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <cstdint>
#include <sstream>

#include "../../../include/spycblockrpc/src/core/graph/TransactionGraph.h"

#include "RawTransaction.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"
#include "../../persistence/graph/transactions/DAOTransactionsGraph.h"
#include "../../persistence/graph/transactions/TransactionsRawGraph.h"

using namespace spyCBlock;
using namespace std;

void RawTransaction::decode(std::ifstream &stream)
{
    Unserialize(stream, version);
    LOG(INFO) << "Version raw transaction " << version;
    this->numberTxIn.decode(stream);

    if(numberTxIn.getValue() == 0){
      LOG(WARNING) << "Findend the marker";

      this->numberTxIn.decode(stream);

      if(numberTxIn.getValue() == 1){
        LOG(WARNING) << "Findend the flag";
        type = Type::WITNESS;
        numberTxIn.decode(stream); //With this code I readed the number tranaction input in Witnees transaction type;
      }
    }else{
      type = Type::PRIMITIVE;
    }

    LOG(INFO) << "Number transaction input in raw transaction " << numberTxIn.getValue();
    txIn.clear();

    txIn.reserve(numberTxIn.getValue());
    for(int i = 0; i < static_cast<int>(this->numberTxIn.getValue()); i++)
    {
        txIn.emplace_back(TransactionInput{});
        TransactionInput& transaction = txIn.back();
        transaction.decode(stream);
    }
    this->numberTxOut.decode(stream);
    LOG(INFO) << "Number transaction output in raw transaction " << numberTxOut.getValue();

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
  if(this->type == RawTransaction::Type::WITNESS){
    LOG(WARNING) << "\n****** HEX segregated witness *************\n"
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
    for(auto txInput : this->txIn)
    {
        stringForm += txInput.toString();
    }
    stringForm += "---------- Transaction Output ----------\n";
    stringForm += "Number Transaction out: ";
    stringForm += to_string(numberTxOut.getValue());
    for(auto txOutput : this->txOut)
    {
        stringForm += txOutput.toString();
    }
    if(type == Type::WITNESS){
        for(auto signatureStack : txsWitness)
        {
           stringForm += signatureStack.toString();
        }
    }
    stringForm += to_string(this->lockTime);
    return stringForm;
}

void RawTransaction::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
  writerJson.StartObject();

  writerJson.Key("hashRawTransaction");
  writerJson.String(this->hashRawTransaction.c_str());

  writerJson.Key("version");
  writerJson.Int(this->version);

  writerJson.Key("numberTxInput");
  writerJson.Uint64(this->numberTxIn.getValue());

  writerJson.Key("txInput");
  writerJson.StartArray();

  for(TransactionInput &txInput : this->txIn)
  {
    txInput.toJson(writerJson);
  }

  writerJson.EndArray();

  writerJson.Key("numberTxOutput");
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
  wrapper.addInformationLink("RawTxID: " + this->hashRawTransaction);
  wrapper.addInformationLink("lockTime: " + to_string(this->lockTime));
  bool witness = false;
  if(type == Type::WITNESS){
      witness = true;
  }
  wrapper.addInformationLink("witness: " + to_string(witness));
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
  wrapper.setTo(this->hashRawTransaction);
  wrapper.addInformationLink("RawTxID: " + this->hashRawTransaction);
  wrapper.addInformationLink("lockTime: " + to_string(this->lockTime));
  bool witness = false;
  if(type == Type::WITNESS){
      witness = true;
  }
  wrapper.addInformationLink("witness: " + to_string(witness));
  // TODO this serealize all transaztion input to one transaction output
  //This is wrong, decide if deserialize all transazions or all transaction without many to many.
  bool setValue = false;
  for(TransactionOutput txOut : this->txOut)
  {
    if(setValue == false){
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

//Getter and setter
uint8_t RawTransaction::getFlag() const
{
  return flag;
}

uint8_t RawTransaction::getMarker() const
{
  return marker;
}

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




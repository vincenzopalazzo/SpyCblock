//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <cstdint>
#include <sstream>

#include "RawTransaction.h"
#include "../../persistence/serializationutil.h"
#include "../../crypto/cryptosingleton.h"

using namespace spyCBlock;

RawTransaction::~RawTransaction()
{
  txInd.clear();
  txOut.clear();
}

int32_t RawTransaction::getVersion() const
{
    return version;
}

const DVarInt &RawTransaction::getNumberTxIn() const
{
    return numberTxIn;
}

const vector<unique_ptr<TransactionInput>> &RawTransaction::getTxInd() const
{
    return txInd;
}

const DVarInt &RawTransaction::getNumberTxOut() const
{
    return numberTxOut;
}

const vector<unique_ptr<TransactionOutput>> &RawTransaction::getTxOut() const
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

void RawTransaction::decode(std::ifstream &stream)
{
    Unserialize(stream, version);
    LOG(INFO) << "Version raw transaction " << version;
    this->numberTxIn.decode(stream);
    LOG(INFO) << "Numbar transaction input in raw transaction " << numberTxIn.getValue();
    txInd.clear();
    for(int i = 0; i < static_cast<int>(this->numberTxIn.getValue()); i++)
    {
        //TransactionInput *transaction = new TransactionInput();
        unique_ptr<TransactionInput> transaction(new TransactionInput());
        transaction->decode(stream);
        this->txInd.push_back(move(transaction));
        delete transaction.release();
    }
    this->numberTxOut.decode(stream);
    LOG(INFO) << "Numbar transaction output in raw transaction " << numberTxOut.getValue();
    txOut.clear();
    for(int i = 0; i < static_cast<int>(numberTxOut.getValue()); i++)
    {
        //TransactionOutput *transactionOutput = new TransactionOutput();
        unique_ptr<TransactionOutput> transactionOutput(new TransactionOutput());
        transactionOutput->decode(stream);
        this->txOut.push_back(move(transactionOutput));
        delete transactionOutput.release();
    }
    Unserialize(stream, this->lockTime);


    //Create additional information
    string serializationForm = toSerealizationForm();
    this->hashRawTransaction = CryptoSingleton::getIstance()->getHash256(serializationForm);
}

string RawTransaction::toSerealizationForm()
{

  string hexForm = SerializationUtilSingleton::getInstance()->toSerealizeForm(this->version);
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->numberTxIn);
  for(int i = 0; i < static_cast<int>(numberTxIn.getValue()); i++)
  {
    hexForm += txInd.at(i)->toSerealizationForm();
  }
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->numberTxOut);
  for(int i = 0; i < static_cast<int>(numberTxOut.getValue()); i++)
  {
     hexForm += txOut.at(i)->toSerealizationForm();
  }
  hexForm += SerializationUtilSingleton::getInstance()->toSerealizeForm(this->lockTime);

  return hexForm;
}

string RawTransaction::toString() {
    string stringForm =  "---------- Raw Transaction ----------\n";
    stringForm += "Version: ";
    stringForm += to_string(version);
    stringForm += "---------- Transaction Input ----------\n";
    stringForm += "Number Transaction In: ";
    stringForm += to_string(numberTxIn.getValue());
    for(int i = 0; i < static_cast<int>(numberTxIn.getValue()); i++)
    {
        stringForm += this->txInd.at(i)->toString();
    }
    stringForm += "---------- Transaction Output ----------\n";
    stringForm += "Number Transaction out: ";
    stringForm += to_string(numberTxOut.getValue());
    for(int i = 0; i < static_cast<int>(numberTxOut.getValue()); i++)
    {
        stringForm += this->txOut.at(i)->toString();
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
  //stringstream intputTransactionJson;
  json txInputjson;
  for(int i = 0; i < static_cast<int>(numberTxIn.getValue()); i++)
  {
    //intputTransactionJson <<  this->txInd.at(i).toJson() << ",";
      txInputjson.push_back(this->txInd.at(i)->toJson());
  }

  //stringstream outputTransactionJson;
  json txOutjson;
  for(int i = 0 ; i < static_cast<int>(numberTxOut.getValue()); i++)
  {
    //outputTransactionJson <<  this->txOut.at(i).toJson() << ",";
    txOutjson.push_back(this->txOut.at(i)->toJson());
  }

  /*jsonRawTransaction["inputTransactions"] = {intputTransactionJson.str()};
  jsonRawTransaction["outputTransaction"] = {outputTransactionJson.str()};*/
  jsonRawTransaction["inputTransactions"] = txInputjson;
  jsonRawTransaction["outputTransaction"] = txOutjson;
  return jsonRawTransaction;
}




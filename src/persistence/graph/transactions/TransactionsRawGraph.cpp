// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <glog/logging.h>

#include "TransactionsRawGraph.h"
#include "../../../../include/spycblockrpc/src/core/graph/WrapperInformations.h"

using namespace std;
using namespace spyCBlockRPC;

void spyCBlock::TransactionsRawGraph::serialize(ofstream &stream)
{
  LOG(INFO) << "************ Serialization this information ************\n";
  string serializeTransaction;
  //Serialization informations input
  serializeTransaction += from;
  for (auto iterator = linkInformations.begin(); iterator != linkInformations.end();  ++iterator)
  {
    serializeTransaction += (delimitator + *iterator);
  }
  serializeTransaction += (delimitator + to);
  LOG(WARNING) << serializeTransaction;
  stream << serializeTransaction << "\n";
}

void spyCBlock::TransactionsRawGraph::buildTransaction(spyCBlockRPC::WrapperInformations &wrapper)
{
  string hashPreviusRawTx = wrapper.getFrom();
  LOG(WARNING) << "Script sing: "  << hashPreviusRawTx;
  string hashRawTx = wrapper.getTo();
  LOG(WARNING) << "Script public key: " << hashRawTx;

  //TODO this is UTIL?
 /* this->linkInformations = wrapper.getLinkInformations();
  LOG(WARNING) << "Information size: " << linkInformations.size();*/

  this->delimitator = wrapper.getDelimitator();
  LOG(INFO) << "Delimitator: " << delimitator;

  this->from = wrapper.getFrom();
  this->to = wrapper.getTo();

  this->linkInformations.insert(wrapper.getLinkInformationsBlock().begin(),
                                wrapper.getLinkInformationsBlock().end());

  this->linkInformations.insert(wrapper.getLinkInformationsTransaction().begin(),
                                wrapper.getLinkInformationsTransaction().end());

  LOG(INFO) << "Numbar information link: " << linkInformations.size();
}

void spyCBlock::TransactionsRawGraph::serialize(gzFile &file)
{
  LOG(INFO) << "************ Serialization this information ************\n";

  string serializeTransaction;
  //Serialization informations input
  serializeTransaction += this->from;

  for(auto &information: linkInformations)
  {
    serializeTransaction += (this->delimitator + information);
  }
  serializeTransaction += (this->delimitator  + this->to + "."); //LOOK here the . not is the refuse but is the delimitator for compression file
  LOG(INFO) << serializeTransaction;
  gzwrite(file, serializeTransaction.c_str(), serializeTransaction.size());
}

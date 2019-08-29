
#include <glog/logging.h>

#include "TransactionsRawGraph.h"
#include "../../../include/spycblockrpc/core/graph/WrapperInformations.h"

using namespace std;
using namespace spyCBlockRPC;

void spyCBlock::TransactionsRawGraph::serialize(ofstream &stream)
{
  LOG(INFO) << "************ Serialization this information ************\n";
  //Not serialize the transaction many to many
  string serializeTransaction;
  //Serialization informations input
  serializeTransaction += from;
  for(string &information: this->linkInformations)
  {
    serializeTransaction += (delimitator + information);
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

  this->linkInformations = wrapper.getLinkInformations();
  LOG(WARNING) << "Information size: " << linkInformations.size();

  this->delimitator = wrapper.getDelimitator();
  LOG(INFO) << "Delimitator: " << delimitator;

  this->from = wrapper.getFrom();
  this->to = wrapper.getTo();

  this->linkInformations = wrapper.getLinkInformations();
  LOG(INFO) << "Numbar information link: " << linkInformations.size();
}

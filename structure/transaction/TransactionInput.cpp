//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//

#include <sstream>
#include "TransactionInput.h"
#include <glog/logging.h>
#include "../../persistence/serializationutil.h"

using namespace spyCBlock;

const OutPoint &TransactionInput::getOutpoint() const {
    return outpoint;
}

void TransactionInput::setOutpoint(const OutPoint &outpoint) {
  TransactionInput::outpoint = outpoint;
}

string TransactionInput::decodeIntoStringScriptSing()
{
  string hexScriptSing = this->script.getRawScriptString();
  if(this->outpoint.getN() == 0xffffffff)
  {
    LOG(INFO) << "Method decodeIntoStringScriptSing: This is conibase transacrion";
    return hexScriptSing;
  }

  LOG(INFO) << "Method decodeIntoStringScriptSing: The op_code into hex script is " << hexScriptSing.substr(0, 2);
  //insert this code into util
  unsigned int op_codeHex;
  std::stringstream streamHex;
  streamHex << std::hex << hexScriptSing.substr(0, 2);
  streamHex >> op_codeHex;
  LOG(INFO) << "Method decodeIntoStringScriptSing: The op_code after convertionhec into unsigned int is " << op_codeHex;

  op_codeHex *= 2;
  string scriptPure = hexScriptSing.substr(2, op_codeHex * 2);
  LOG(INFO) << "Method decodeIntoStringScriptSing: The pure script is " << scriptPure;

  /*After create a class op_code*/
  //TODO Lo stream per la conversione delle stringhe puo essere un singleton?
  unsigned int op_type;
  streamHex.clear();
  streamHex << std::hex << hexScriptSing.substr(op_codeHex, op_codeHex + 2);
  if(op_type != 0x1)
  {
    //https://bitcoin.org/en/glossary/sighash-all
    LOG(INFO) << "Method decodeIntoStringScriptSing: " << "the script code not is the SIGHASH_ALL";
    return hexScriptSing;
  }
  string pubKey = hexScriptSing.substr(2 + op_type + 2, 2 + op_type + 2 + 66);
  LOG(INFO) << "Method decodeIntoStringScriptSing: " << "The public key is " << pubKey;
  return pubKey;
}


void TransactionInput::decode(std::ifstream &stream)
{
    outpoint.Unserialize(stream);
    LOG(INFO) << "Outopoint Hash" << outpoint.getHash().GetHex();
    LOG(INFO) << "Outopoint N" << outpoint.getN();
    this->script.decode(stream);
    LOG(INFO) << "Script Lenght" << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value" << script.toString();
    Unserialize(stream, this->sequences);
    LOG(INFO) << "Numbar sequences " << sequences;
}

string TransactionInput::toSerealizationForm()
{
  stringstream stream;
  stream << SerializationUtilSingleton::getInstance()->toSerealizeForm(this->outpoint.getHash())
         << SerializationUtilSingleton::getInstance()->toSerealizeForm(this->outpoint.getN())
         << SerializationUtilSingleton::getInstance()->toSerealizeForm(this->getScript().getScriptLenght())
         << this->script.getScriptToSerializationForm()
         << SerializationUtilSingleton::getInstance()->toSerealizeForm(this->sequences);
  return stream.str();
}

uint32_t TransactionInput::getSequences() const {
    return sequences;
}

const DScript &TransactionInput::getScript() const {
    return script;
}

string TransactionInput::toString() {
    stringstream stream;
    stream << outpoint.ToString();
    stream << script.getScriptString() << endl;
    stream << "Sequences: " << sequences << endl;
    return stream.str();
}


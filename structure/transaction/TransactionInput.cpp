#include <sstream>

#include <glog/logging.h>

#include "TransactionInput.h"
#include "../../persistence/SerializationUtil.h"
#include "../../crypto/CryptoCore.h"

using namespace spyCBlock;
using namespace std;
using namespace nlohmann;

/**
 * Created on 1/21/19.
 * @author https://github.com/vincenzopalazzo
 */
void TransactionInput::decode(std::ifstream &stream)
{
    outpoint.Unserialize(stream);
    LOG(WARNING) << "Outopoint Hash: " << outpoint.getHash().GetHex();
    LOG(WARNING) << "Outopoint N: " << outpoint.getN();
    this->script.decode(stream);
    LOG(INFO) << "Script Lenght" << script.getScriptLenght().getValue();
    LOG(INFO) << "Script Value" << script.toString();
    Unserialize(stream, this->sequences);
    LOG(INFO) << "Numbar sequences " << sequences;

    //Create hash transaction
    string hexInputTransaction = toSerealizationForm();
    this->hashInputTransaction = CryptoSingleton::getIstance().getHash256(hexInputTransaction);

}

string TransactionInput::toSerealizationForm()
{
  string hexForm = SerializationUtil::toSerealizeForm(this->outpoint.getHash());
  hexForm.append(SerializationUtil::toSerealizeForm(this->outpoint.getN()));
  hexForm.append(SerializationUtil::toSerealizeForm(this->getScript().getScriptLenght()));
  hexForm.append(this->script.getScriptToSerializationForm());
  hexForm.append(SerializationUtil::toSerealizeForm(this->sequences));

  return hexForm;
}

bool TransactionInput::isScriptNull()
{
  LOG_IF(ERROR, script.getRawScriptString().empty()) << "The scrips is null";
  return this->script.getRawScriptString().empty();
}

json TransactionInput::toJson()
{
  json jsonTxsInput = json::object({
                                     {"outputTxHash", this->outpoint.getHash().GetHex()},
                                     {"ammount", this->outpoint.getN()},
                                     {"scriptLenght", this->getScript().getScriptLenght().getValue()},
                                     {"script", this->getScript().getRawScriptString()},
                                     {"sequences", this->sequences},
                                     {"hashInputTransaction", this->hashInputTransaction},
                                   });

  return jsonTxsInput;
}

void TransactionInput::toJson(rapidjson::Writer<rapidjson::OStreamWrapper> &writerJson)
{
  writerJson.StartObject();

  writerJson.Key("hashInputTransaction");
  writerJson.String(this->hashInputTransaction.c_str());

  writerJson.Key("outputTxHash");
  writerJson.String(outpoint.getHash().ToString().c_str());

  writerJson.Key("ammount");
  writerJson.Uint(outpoint.getN());

  writerJson.Key("scriptLenght");
  writerJson.Uint64(this->getScript().getScriptLenght().getValue());

  writerJson.Key("script");
  writerJson.String(this->script.getRawScriptString().c_str());

  writerJson.Key("sequences");
  writerJson.Uint(this->sequences);

  writerJson.EndObject();
}

void TransactionInput::toGraphForm(ofstream &outputStream, spyCBlockRPC::WrapperInformations &wrapper)
{
  wrapper.setHashPreviousTx(this->outpoint.getHash().GetHex());
  wrapper.setNOutpoint(this->outpoint.getN());
}

string TransactionInput::toString()
{
    string stringForm = outpoint.ToString();
    stringForm += script.getScriptToSerializationForm();
    stringForm += "\n";
    stringForm += "Sequences: ";
    stringForm += to_string(sequences);
    stringForm += "\n";
    return stringForm;
}

//TODO non funziona e' stata solo una prova
//Non cancello il codice perchè potrebbe essere sempre implementata una cosa del genere
string TransactionInput::decodeIntoStringScriptSing() const
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

//getter and setter
const OutPoint &TransactionInput::getOutpoint() const
{
    return outpoint;
}

void TransactionInput::setOutpoint(const OutPoint &outpoint)
{
  TransactionInput::outpoint = outpoint;
}

const string& TransactionInput::getHashInputTransaction() const
{
  return hashInputTransaction;
}

uint32_t TransactionInput::getSequences() const
{
    return sequences;
}

const DScript &TransactionInput::getScript() const
{
    return script;
}

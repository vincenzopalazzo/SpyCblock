// Copyright (c) 2018-2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include "UTXOTransaction.h"

#include <glog/logging.h>

#include <iostream>
#include <string>

#include "../../DefinitionMacro.h"
#include "../../crypto/UtilCrypto.h"
#include "../../persistence/SerializationUtil.h"
#include "../../util/serialize.h"

using namespace std;
using namespace spyCBlock;

/**

 func Varint128Read(bytes []byte, offset int) ([]byte, int) { // take a byte
array and return (byte array and number of bytes read)

    // store bytes
    result := []byte{} // empty byte slice

    // loop through bytes
    for _, v := range bytes[offset:] { // start reading from an offset

        // store each byte as you go
        result = append(result, v)

        // Bitwise AND each of them with 128 (0b10000000) to check if the 8th
bit has been set set := v & 128 // 0b10000000 is same as 1 << 7

        // When you get to one without the 8th bit set, return that byte slice
        if set == 0 {
            return result, len(result)
            // Also return the number of bytes read
        }
    }

    // Return zero bytes read if we haven't managed to read bytes properly
    return result, 0

}
 * @param dbKey
 * @param dbValue
 */

void spyCBlock::UTXOTransaction::decode(
    std::vector<unsigned char> const& dbKey,
    std::vector<unsigned char> const& dbValue) {
  auto prefix = dbKey[0];
  LOG(INFO) << "Prefix is " << prefix;
  if (prefix == 14) {
    this->obfuscateKey = dbValue;
    LOG(INFO) << "obfuscateKey is " << this->obfuscateKey.size();
  }
  if (prefix == 0x43 && dbKey.size() > 32) {
    // Stage 2.1
    this->txId = UtilCrypto::BytesLittleEndianToStringBigEndian(dbKey, 1, 32);
    LOG(INFO) << "Transaction ID " << this->txId;
    stringstream stream;
    for (std::size_t i = 33; i < dbKey.size(); i++) stream << dbKey[i];
    LOG(INFO) << stream.str();
    this->vOut =
        ReadVarInt<stringstream, VarIntMode::DEFAULT, uint64_t>(stream);
    LOG(INFO) << "Vout in var in is: " << this->vOut;
    // stage 2.2
    auto extendedObKey = extendObfuscateKey();
    stream.clear();
    auto offset = 0;  // it si passed by reference to the method toVarIntForm
                      // and it will be increase with the new offset
    auto varIntOne =
        SerializationUtil::toVarIntForm<int>(extendedObKey, offset);
    for (auto i = 0; i < extendedObKey.size(); i++) stream << extendedObKey[i];
    auto decodeExtendedKey =
        ReadVarInt<stringstream, VarIntMode::DEFAULT, uint64_t>(stream);
    LOG(INFO) << "ReadVarInt is " << decodeExtendedKey;
    this->height = (decodeExtendedKey > 1);
    LOG(INFO) << "Height: " << this->height;
    this->coinbase = (decodeExtendedKey & 1);
    LOG(INFO) << "Coinbase: " << this->coinbase;
    LOG(INFO) << "Offset second var int decoding " << offset;
    // stage 2.3
    auto varIntTwo =
        SerializationUtil::toVarIntForm<int>(extendedObKey, offset);
    auto decodeExtendedKeyTwo =
        ReadVarInt<stringstream, VarIntMode::DEFAULT, uint64_t>(stream);
    this->amount =
        SerializationUtil::toDecompressedVarInt<int64_t>(decodeExtendedKeyTwo);
    LOG(INFO) << "Amount: " << this->amount;
    this->totoAmount += this->amount;
    // stage 2.4
    // TODO: Calculate the addresses
  }
}

// TODO: Working here:
// https://github.com/lightningamp/bitcoin-utxo-dump/blob/3377e131ae3aa54248142f0d2375da08c002a9bd/utxodump.go#L267
std::vector<unsigned char> spyCBlock::UTXOTransaction::extendObfuscateKey() {
  std::vector<unsigned char> extended;
  // i = obfuscateKey.size() - 1: the -1 is needed because we need to skip the
  // first bit
  LOG(INFO) << "this->obfuscateKey.size() -> " << this->obfuscateKey.size();
  extended.reserve(this->obfuscateKey.size());
  for (std::size_t i = 1; i < this->obfuscateKey.size(); i++)
    extended.emplace_back(this->obfuscateKey[i]);

  auto k = 0;
  for (std::size_t i = extended.size() - 1;
       extended.size() - 1 < this->obfuscateKey.size() - 1; i++) {
    extended.emplace_back(this->obfuscateKey[k]);
    k++;
  }
  LOG(INFO) << "extended.size() -> " << extended.size();
  // Make XOR to undo of the bytes to undo the obfuscation operation
  std::vector<unsigned char> unwrap;
  unwrap.reserve(obfuscateKey.size());
  for (std::size_t i = 0; i < obfuscateKey.size(); i++) {
    auto result = obfuscateKey[i] ^ extended[i];
    unwrap.emplace_back(result);
  }
  return unwrap;
}

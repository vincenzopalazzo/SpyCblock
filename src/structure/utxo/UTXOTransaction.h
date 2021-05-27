// Copyright (c) 2018-2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#ifndef SPYCBLOCK_UTXOTRANSACTION_H
#define SPYCBLOCK_UTXOTRANSACTION_H

#include <string>
#include <vector>

/**
 * Format of UTXO on level db is
 *     type                          txid (little-endian) index (varint) \ | /
 *         <><--------------------------------------------------------------><>
 *   key:   430000155b9869d56c66d9e86e3c01de38e3892a42b99949fe109ac034fff6583900
 *
 *   value: 71a9e87d62de25953e189f706bcf59263f15de1bf6c893bda9b045 <- obfuscated
 *         b12dcefd8f872536b12dcefd8f872536b12dcefd8f872536b12dce <- extended
 * obfuscateKey c0842680ed5900a38f35518de4487c108e3810e6794fb68b189d8b <-
 * deobfuscated (XOR)
 *          <----><----><><-------------------------------------->
 *           /      |    \                   |
 *      varint   varint   varint          script <- P2PKH/P2SH hash160, P2PK
 * public key, or complete script |        |     nSize |        | |     amount
 * (compressesed)
 *         |
 *         |
 *  100000100001010100110
 *  <------------------> \
 *         height         coinbase
 *
 *  See also: https://bitcoin.stackexchange.com/a/52167/91194
 */

namespace spyCBlock {
/**
 * I noted that the serialization inside the decode method requires two
 * different stages, and I try to summarize them here
 * 1. Ge the transaction id and the vout
 * 2. Read the from the value the information that is divided like
 *      2.1: decode the transaction id and the vouot
 *      2.2: decode the height and the coinbase
 *      2.3: decode the amount
 *      2.4: decode the address(es) of the UTXOs
 *
 *  The basic ide is to use the chain of responsibility pattern with the list
 * implementation, and each of the point 2.x write a handler that makes in a
 * readable way the serialization
 */
class UTXOTransaction {
 private:
  std::string txId;
  uint64_t vOut;
  uint32_t height;
  uint32_t coinbase;
  int64_t amount;
  std::vector<unsigned char> obfuscateKey;

  std::vector<unsigned char> extendObfuscateKey();

 public:
  // debug propriety
  int64_t totoAmount = 0;

  void decode(std::vector<unsigned char> const& dbKey,
              std::vector<unsigned char> const& dbValue);

  /**
   * FIXME(vincenzopalazzo): Remove this method, move the obfuscateKey out of
   * the structure
   */
  inline void clear() {
    this->txId = "";
    this->vOut = 0;
  }
};
}  // namespace spyCBlock

#endif  // SPYCBLOCK_UTXOTRANSACTION_H

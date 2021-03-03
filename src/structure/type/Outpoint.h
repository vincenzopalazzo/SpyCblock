// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Copyright (c) 2018-2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PARSINGBLOCKCHAIN_OUTPOINT_H
#define PARSINGBLOCKCHAIN_OUTPOINT_H

#include <stdint.h>

#include <cstdint>

#include "../../util/script.h"
#include "../../util/serialize.h"
#include "../../util/uint256.h"

namespace spyCBlock {
class OutPoint {
 public:
  static constexpr uint32_t NULL_INDEX = std::numeric_limits<uint32_t>::max();

  OutPoint() : n(NULL_INDEX) {}

  const uint256 &getHash() const;

  void setHash(const uint256 &hash);

  uint32_t getN() const;

  ADD_SERIALIZE_METHODS;

  template <typename Stream, typename Operation>
  inline void SerializationOp(Stream &s, Operation ser_action) {
    READWRITE(hash);
    READWRITE(n);
  }

  friend bool operator<(const OutPoint &a, const OutPoint &b);

  friend bool operator==(const OutPoint &a, const OutPoint &b);

  friend bool operator!=(const OutPoint &a, const OutPoint &b);

  std::string ToString() const;

 private:
  uint256 hash;

  uint32_t n;
};
}  // namespace spyCBlock

#endif  // PARSINGBLOCKCHAIN_OUTPOINT_H

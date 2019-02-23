//
// Created by https://github.com/vincenzopalazzo on 1/21/19.
//  The type is type bitcoin core implementation
//
#ifndef PARSINGBLOCKCHAIN_OUTPOINT_H
#define PARSINGBLOCKCHAIN_OUTPOINT_H

#include <cstdint>
#include <stdint.h>
#include "../util/amount.h"
#include "../util/script.h"
#include "../util/serialize.h"
#include "../util/uint256.h"

using namespace std;

static const int SERIALIZE_TRANSACTION_NO_WITNESS = 0x40000000;

//TODO refactoring the tipe
/** An outpoint - a combination of a transaction hash and an index n into its vout */
class OutPoint
{
private:
    uint256 hash;
    uint32_t n;
public:
    static constexpr uint32_t NULL_INDEX = std::numeric_limits<uint32_t>::max();

    OutPoint(): n(NULL_INDEX) { }
    OutPoint(const uint256& hashIn, uint32_t nIn): hash(hashIn), n(nIn) { }

    virtual ~OutPoint();

    /*TODO this metod is not sicure*/
    const uint256 &getHash() const;

    void setHash(const uint256 &hash);

    uint32_t getN() const;

    void setN(uint32_t n);

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(hash);
        READWRITE(n);
    }


    void SetNull();
    bool IsNull();


    friend bool operator<(const OutPoint& a, const OutPoint& b);

    friend bool operator==(const OutPoint& a, const OutPoint& b);

    friend bool operator!=(const OutPoint& a, const OutPoint& b);

    std::string ToString() const;
};

#endif //PARSINGBLOCKCHAIN_OUTPOINT_H

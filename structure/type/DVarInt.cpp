//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <cmath>
#include <glog/logging.h>
#include <uv.h>
#include "DVarInt.h"
#include "../../util/serialize.h"

uint64_t DVarInt::getValue() const {
    return value;
}

/* TODO LOGGER THIS position*/
//TODO LOOK LOG qualcosa non va come dovrebbe
void DVarInt::decode(std::ifstream &stream) {
    value = ReadCompactSize(stream);
    //value = ReadVarInt<std::ifstream, VarIntMode::DEFAULT , uint64_t>(stream);
   /* uint64_t valueTmp;
    CVarInt<VarIntMode::DEFAULT, uint64_t> variantInt(valueTmp);
    variantInt.Unserialize(stream, value);
    LOG(WARNING) << "Variant int read is: " << value;*/
    /*uint8_t size;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (8bit) -> " << size;
    if(size < 253){
        this->value = size;
        return;
    }
    uint8_t value_16;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (16bit) -> " << value_16;
    if(value_16 < pow(2, 16)){
        this->value = value_16;
        return;
    }
    uint16_t value_32;
    Unserialize(stream, value_32);
    LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_32;
    if(value_32 < pow(2, 32)){
        this->value = value_32;
        return;
    }
    uint32_t value_64;
    Unserialize(stream, value_64);
    LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_64;
    if(value_64 < pow(2, 64)){
        this->value = value_64;
        return;
    }
    this->value = -1;
    LOG_IF(FATAL, value == -1) << "DVarInt crash :'(";*/
/*
    uint8_t chSize = ser_readdata8(stream);
    uint64_t nSizeRet = 0;
    if (chSize < 253)
    {
        nSizeRet = chSize;
    }
    else if (chSize == 253)
    {
        nSizeRet = ser_readdata16(stream);
        if (nSizeRet < 253)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    }
    else if (chSize == 254)
    {
        nSizeRet = ser_readdata32(stream);
        if (nSizeRet < 0x10000u)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    }
    else
    {
        nSizeRet = ser_readdata64(stream);
        if (nSizeRet < 0x100000000ULL)
            throw std::ios_base::failure("non-canonical ReadCompactSize()");
    }
    if (nSizeRet > (uint64_t)MAX_SIZE)
        throw std::ios_base::failure("ReadCompactSize(): size too large");
    value = nSizeRet;*/
    LOG(INFO) << "Variant int read is: " << value;
}

//TODO last tentative
/*void DVarInt::decode(std::ifstream &stream) {
    uint8_t size;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (8bit) -> " << size;
    if(size < 253){
        this->value = size;
        return;
    }
    if(size == 253){
        ushort value_16;
        Unserialize(stream, size);
        LOG(INFO) << "DVarInt test: size first test (16bit) -> " << value_16;
        this->value = value_16;
        return;
    }

    if(size == 254){
        uint32_t value_32;
        Unserialize(stream, value_32);
        LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_32;
        this->value = value_32;
        return;
    }

        ulong value_64;
        Unserialize(stream, value_64);
        LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_64;
        this->value = value_64;
        return;
   // this->value = -1;
    //LOG_IF(FATAL, value == -1) << "DVarInt crash :'(";
}*/

//Fix version test
/***
 * THIS non returned error but is not correct, test this part
 * @param stream
 */
/*void DVarInt::decode(std::ifstream &stream) {
    uint8_t size;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (8bit) -> " << size;
    if(size < 253){
        this->value = size;
        return;
    }
    uint16_t value_16;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (16bit) -> " << value_16;
    if(value_16 == 253){
        this->value = value_16;
        return;
    }
    uint32_t value_32;
    Unserialize(stream, value_32);
    LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_32;
    if(value_32 == 254){
        this->value = value_32;
        return;
    }
    uint64_t value_64;
    Unserialize(stream, value_64);
    LOG(INFO) << "DVarInt test: size first test (64bit) -> " << value_64;
    if(value_64 == 255){
        this->value = value_64;
        return;
    }
    this->value = -1;
    LOG(INFO) << "DVarInt VALUE -1";
}*/

/* another teentative
void DVarInt::decode(std::ifstream &stream) {
    uint8_t size;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (8bit) -> " << size;
    if(size < 0xFD){
        this->value = size;
        return;
    }
    uint16_t value_16;
    Unserialize(stream, size);
    LOG(INFO) << "DVarInt test: size first test (16bit) -> " << value_16;
    if(value_16 <= 0xFFFF){
        this->value = value_16;
        return;
    }
    uint32_t value_32;
    Unserialize(stream, value_32);
    LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_32;
    if(value_32 <= 0xFFFFFFFF){
        this->value = value_32;
        return;
    }
    uint64_t value_64;
    Unserialize(stream, value_64);
    LOG(INFO) << "DVarInt test: size first test (32bit) -> " << value_64;
    //if(value_64 >= pow(2, 32) && value_64 < pow(2,32)){
        this->value = value_64;
       // return;
    //}
    //this->value = -1;
    //LOG_IF(FATAL, value == -1) << "DVarInt crash :'(";
}
*/


DVarInt::~DVarInt() {
}


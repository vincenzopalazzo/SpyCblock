//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <cmath>
#include <glog/logging.h>
#include "DVarInt.h"
#include "../../util/serialize.h"

int DVarInt::getValue() const {
    return value;
}

/* TODO LOGGER THIS position*/
//TODO LOOK LOG qualcosa non va come dovrebbe
void DVarInt::decode(std::ifstream &stream) {
    ReadCompactSize(stream); 
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

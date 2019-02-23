//
// Created by https://github.com/vincenzopalazzo on 2/4/19.
//

#include <cmath>
#include "DVarInt.h"
#include "../util/serialize.h"

unsigned int DVarInt::getValue() const {
    return value;
}

/* TODO LOGGER THIS position*/
void DVarInt::decode(std::ifstream &stream) {
    uint8_t size;
    Unserialize(stream, size);

    if(size < 253){
        this->value = size;
        return;
    }
    uint8_t value_16;
    Unserialize(stream, size);
    if(value_16 < pow(2, 16)){
        this->value = value_16;
        return;
    }
    uint16_t value_32;
    Unserialize(stream, value_32);
    if(value_32 < pow(2, 32)){
        this->value = value_32;
        return;
    }
    uint32_t value_64;
    Unserialize(stream, value_64);
    if(value_64 < pow(2, 64)){
        this->value = value_64;
        return;
    }
    this->value = -1;
}

DVarInt::~DVarInt() {

}

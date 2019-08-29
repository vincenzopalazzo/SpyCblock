cmake_minimum_required(VERSION 3.9)
project(SpyCBlock-benchmarck)

set(CMAKE_CXX_STANDARD 14)

#Glog
find_package(glog 0.3.5 REQUIRED)

## Json library
find_package(RapidJSON) #This find the element in the OS

#bitcoin rpc lib
find_library(bitcoinapi 0.3 REQUIRED)

#GoogleBenchmark
find_package(benchmark)

add_executable(

        ${PROJECT_NAME}

        src/BanckMerchSerializationGraph.cpp

        ../core/SpyCBlock.cpp
        ../core/ConfiguratorSingleton.cpp

        ../util/uint256.cpp
        ../util/strencodings.cpp
        ../util/prevector.cpp

        ../structure/block/block.cpp
        ../structure/block/blockHeader.cpp
        ../structure/transaction/RawTransaction.cpp
        ../structure/transaction/TransactionOutput.cpp
        ../structure/transaction/TransactionInput.cpp
        ../structure/transaction/TransactionWitness.cpp
        ../structure/script/scriptCode.cpp
        ../structure/type/Outpoint.cpp
        ../structure/type/DVarInt.cpp
        ../structure/type/DScript.cpp
        ../structure/type/Outpoint.cpp

        ../persistence/DAOException.cpp
        ../persistence/SerializationUtil.cpp
        ../persistence/json/DAOJson.cpp
        ../persistence/graph/DAOManagerGraph.cpp
        ../persistence/graph/transactions/DAOTransactionsGraph.cpp
        ../persistence/graph/transactions/TransactionsRawGraph.cpp

        ../crypto/UtilCrypto.cpp
        ../crypto/CryptoCore.cpp

        #cpp-properties file include
        ../include/cpp-properties/src/Properties.cpp
        ../include/cpp-properties/src/PropertiesParser.cpp
        ../include/cpp-properties/src/PropertiesUtils.cpp

        #include bitcoin-cryptography-library
        ../include/bitcoin-cryptography-library/cpp/Sha256.cpp
        ../include/bitcoin-cryptography-library/cpp/Sha256Hash.cpp
        ../include/bitcoin-cryptography-library/cpp/Utils.cpp

        #include spycblocrpc
        ../include/spycblockrpc/core/graph/TransactionGraph.cpp
        ../include/spycblockrpc/core/graph/WrapperInformations.cpp
       ../include/spycblockrpc/ConfiguratorSingleton.cpp

       ../include/spycblockrpc/commands/DecodeScriptCommand.cpp
       ../include/spycblockrpc/commands/DecodeRawTransaction.cpp
        ../include/spycblockrpc/commands/HeightBlockchainCommand.cpp
        ../include/spycblockrpc/commands/DecodeBlockAtIndexCommand.cpp

)

#using glog
target_link_libraries(${PROJECT_NAME} glog::glog)
##using filesystem
target_link_libraries(${PROJECT_NAME} stdc++fs)
#bitcoin rpc lib
target_link_libraries(${PROJECT_NAME} bitcoinapi)
target_link_libraries(${PROJECT_NAME} benchmark)



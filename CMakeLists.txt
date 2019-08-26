cmake_minimum_required(VERSION 3.9)
project(SpyCBlock)

set(CMAKE_CXX_STANDARD 14)

# Locate GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Glog
find_package(glog 0.3.5 REQUIRED)

## Json library
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(RapidJSON) #This find the element in the OS

#bitcoin rpc lib
find_library(bitcoinapi 0.3 REQUIRED)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(

        SpyCBlockTests

        test/util/DAOUtilTest.cpp

        test/StructureBitcoinCoreTest.cpp
        test/SHABitcoinCoreTest.cpp
        test/SerealizationTest.cpp
        test/DAOJsonTest.cpp
        test/NullDataTransactionsTest.cpp
        test/ExceptionCompactsizeTest.cpp
        test/ConfiguratorSingletonTest.cpp
        test/DAOManagerGraphTest.cpp

        util/uint256.cpp
        util/strencodings.cpp
        util/prevector.cpp

        structure/block/block.cpp
        structure/block/blockHeader.cpp
        structure/transaction/RawTransaction.cpp
        structure/transaction/TransactionOutput.cpp
        structure/transaction/TransactionInput.cpp
        structure/transaction/TransactionWitness.cpp
        structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp
        structure/type/DVarInt.cpp
        structure/type/DScript.cpp
        structure/type/Outpoint.cpp

        persistence/DAOException.cpp
        persistence/json/DAOJson.cpp
        persistence/SerializationUtil.cpp
        persistence/graph/DAOManagerGraph.cpp
        persistence/graph/transactions/DAOTransactionsGraph.cpp
        persistence/graph/transactions/TransactionsRawGraph.cpp

        crypto/UtilCrypto.cpp
        crypto/CryptoCore.cpp

        core/ConfiguratorSingleton.cpp

        #cpp-properties file include
        include/cpp-properties/src/Properties.cpp
        include/cpp-properties/src/PropertiesParser.cpp
        include/cpp-properties/src/PropertiesUtils.cpp

        #include bitcoin-cryptography-library
        include/bitcoin-cryptography-library/cpp/Sha256.cpp
        include/bitcoin-cryptography-library/cpp/Sha256Hash.cpp
        include/bitcoin-cryptography-library/cpp/Utils.cpp

        #include spycblocrpc
        include/spycblockrpc/core/graph/TransactionGraph.cpp
        include/spycblockrpc/core/graph/WrapperInformations.cpp
        include/spycblockrpc/ConfiguratorSingleton.cpp

        include/spycblockrpc/commands/DecodeScriptCommand.cpp
        include/spycblockrpc/commands/DecodeRawTransaction.cpp
        include/spycblockrpc/commands/HeightBlockchainCommand.cpp
        include/spycblockrpc/commands/DecodeBlockAtIndexCommand.cpp

)

add_executable(

        ${PROJECT_NAME}

        core/ParserMain.cpp
        core/SpyCBlock.cpp
        core/ConfiguratorSingleton.cpp

        util/uint256.cpp
        util/strencodings.cpp
        util/prevector.cpp

        structure/block/block.cpp
        structure/block/blockHeader.cpp
        structure/transaction/RawTransaction.cpp
        structure/transaction/TransactionOutput.cpp
        structure/transaction/TransactionInput.cpp
        structure/transaction/TransactionWitness.cpp
        structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp
        structure/type/DVarInt.cpp
        structure/type/DScript.cpp
        structure/type/Outpoint.cpp

        persistence/DAOException.cpp
        persistence/SerializationUtil.cpp
        persistence/json/DAOJson.cpp
        persistence/graph/DAOManagerGraph.cpp
        persistence/graph/transactions/DAOTransactionsGraph.cpp
        persistence/graph/transactions/TransactionsRawGraph.cpp

        crypto/UtilCrypto.cpp
        crypto/CryptoCore.cpp

        #cpp-properties file include
        include/cpp-properties/src/Properties.cpp
        include/cpp-properties/src/PropertiesParser.cpp
        include/cpp-properties/src/PropertiesUtils.cpp

        #include bitcoin-cryptography-library
        include/bitcoin-cryptography-library/cpp/Sha256.cpp
        include/bitcoin-cryptography-library/cpp/Sha256Hash.cpp
        include/bitcoin-cryptography-library/cpp/Utils.cpp

        #include spycblocrpc
        include/spycblockrpc/core/graph/TransactionGraph.cpp
        include/spycblockrpc/core/graph/WrapperInformations.cpp
        include/spycblockrpc/ConfiguratorSingleton.cpp

        include/spycblockrpc/commands/DecodeScriptCommand.cpp
        include/spycblockrpc/commands/DecodeRawTransaction.cpp
        include/spycblockrpc/commands/HeightBlockchainCommand.cpp
        include/spycblockrpc/commands/DecodeBlockAtIndexCommand.cpp

)

#using glog
target_link_libraries(${PROJECT_NAME} glog::glog)
target_link_libraries(SpyCBlockTests glog::glog)
#using gtest
target_link_libraries(SpyCBlockTests ${GTEST_LIBRARIES} pthread)
##using filesystem
target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(SpyCBlockTests stdc++fs)
##Json library
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

#bitcoin rpc lib
target_link_libraries(SpyCBlockTests bitcoinapi)
target_link_libraries(${PROJECT_NAME} bitcoinapi)



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
#find_package(RapidJSON) #This find the element in the OS

#bitcoin rpc lib
find_library(bitcoinapi 0.3 REQUIRED)

#target_include_directories(rapidjson PUBLIC include/rapidjson/include)

#target_include_directories(spycblockrpc PUBLIC include/spycblockrpc)

#target_include_directories(btccryptography PUBLIC include/bitcoin-cryptography-library)

#target_include_directories(cppproperties PUBLIC include/cpp-properties/src)

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

target_include_directories(${PROJECT_NAME} PUBLIC include/rapidjson/include)
target_include_directories(${PROJECT_NAME} PUBLIC include/spycblockrpc)
target_include_directories(${PROJECT_NAME} PUBLIC include/bitcoin-cryptography-library)
target_include_directories(${PROJECT_NAME} PUBLIC include/cpp-properties/src)

target_include_directories(SpyCBlockTests PUBLIC include/rapidjson/include)
target_include_directories(SpyCBlockTests PUBLIC include/spycblockrpc)
target_include_directories(SpyCBlockTests PUBLIC include/bitcoin-cryptography-library)
target_include_directories(SpyCBlockTests PUBLIC include/cpp-properties/src)

#using glog
target_link_libraries(${PROJECT_NAME} glog::glog)
target_link_libraries(SpyCBlockTests glog::glog)
#using gtest
target_link_libraries(SpyCBlockTests ${GTEST_LIBRARIES} pthread)
##using filesystem
target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(SpyCBlockTests stdc++fs)

#bitcoin rpc lib
target_link_libraries(SpyCBlockTests bitcoinapi)
target_link_libraries(${PROJECT_NAME} bitcoinapi)



cmake_minimum_required(VERSION 3.9)
project(SpyCBlockTests)

set(CMAKE_CXX_STANDARD 14)

# Locate GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Glog
find_package(glog 0.3.5 REQUIRED)

#bitcoin rpc lib
find_library(bitcoinapi 0.3 REQUIRED)

#ZLIB
find_package(ZLIB)
find_package(OpenMP)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(

        ${PROJECT_NAME}

        util/DAOUtilTest.cpp

        StructureBitcoinCoreTest.cpp
        SHABitcoinCoreTest.cpp
        SerealizationTest.cpp
        DAOJsonTest.cpp
        NullDataTransactionsTest.cpp
        ExceptionCompactsizeTest.cpp
        ConfiguratorSingletonTest.cpp
        DAOManagerGraphTest.cpp
        SerializationDataCompressedZLib.cpp
        BugHashStructureBlockTest.cpp

        ../src/util/uint256.cpp
        ../src/util/strencodings.cpp
        ../src/util/prevector.cpp

        ../src/structure/block/Block.cpp
        ../src/structure/block/BlockHeader.cpp
        ../src/structure/transaction/RawTransaction.cpp
        ../src/structure/transaction/TransactionOutput.cpp
        ../src/structure/transaction/TransactionInput.cpp
        ../src/structure/transaction/TransactionWitness.cpp
        ../src/structure/script/scriptCode.cpp
        ../src/structure/type/Outpoint.cpp
        ../src/structure/type/DVarInt.cpp
        ../src/structure/type/DScript.cpp
        ../src/structure/type/Outpoint.cpp

        ../src/persistence/DAOException.cpp
        ../src/persistence/json/DAOJson.cpp
        ../src/persistence/SerializationUtil.cpp
        ../src/persistence/graph/DAOManagerGraph.cpp
        ../src/persistence/graph/transactions/DAOTransactionsGraph.cpp
        ../src/persistence/graph/transactions/TransactionsRawGraph.cpp

        ../src/crypto/UtilCrypto.cpp
        ../src/crypto/CryptoCore.cpp

        ../src/core/ConfiguratorSingleton.cpp

        #cpp-properties file include
        ../include/cpp-properties/src/Properties.cpp
        ../include/cpp-properties/src/PropertiesParser.cpp
        ../include/cpp-properties/src/PropertiesUtils.cpp

        #include bitcoin-cryptography-library
        ../include/bitcoin-cryptography-library/cpp/Sha256.cpp
        ../include/bitcoin-cryptography-library/cpp/Sha256Hash.cpp
        ../include/bitcoin-cryptography-library/cpp/Utils.cpp

        ../#include spycblocrpc
        ../include/spycblockrpc/src/core/graph/TransactionGraph.cpp
        ../include/spycblockrpc/src/core/graph/WrapperInformations.cpp
        ../include/spycblockrpc/src/ConfiguratorSingleton.cpp
        ../include/spycblockrpc/src/commands/DecodeScriptCommand.cpp
        ../include/spycblockrpc/src/commands/DecodeRawTransaction.cpp
        ../include/spycblockrpc/src/commands/HeightBlockchainCommand.cpp
        ../include/spycblockrpc/src/commands/DecodeBlockAtIndexCommand.cpp
)

#using glog
target_link_libraries(${PROJECT_NAME} glog::glog)
#using gtest
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
##using filesystem
target_link_libraries(${PROJECT_NAME} stdc++fs)

target_link_libraries(${PROJECT_NAME} bitcoinapi)

target_link_libraries(${PROJECT_NAME}  ${ZLIB_LIBRARIES})

target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

#todo test this
target_include_directories(${PROJECT_NAME} PUBLIC include/rapidjson/include)


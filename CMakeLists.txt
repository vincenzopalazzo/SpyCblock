cmake_minimum_required(VERSION 3.9)
project(SpyCBlock)

set(CMAKE_CXX_STANDARD 17)

# Locate GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Glog
find_package(glog 0.3.5 REQUIRED)

## Json library
find_package(nlohmann_json 3.2.0 REQUIRED)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(

        SpyCBlockTests

        test/StructureBitcoinCoreTest.cpp
        test/DAOBlockchainTest.cpp
        test/SHABitcoinCoreTest.cpp
        test/SerealizationTest.cpp
        test/JsonSerializationTest.cpp
        test/DAOBlkToJsonTest.cpp
        test/DAOJsonTest.cpp
        test/NullDataTransactionsTest.cpp
        test/ExceptionCompactsizeTest.cpp
        test/ConfiguratorSingletonTest.cpp

        util/uint256.cpp
        util/strencodings.cpp
        util/prevector.cpp


        cryptobitcoin/Sha256.cpp
        cryptobitcoin/Sha256Hash.cpp
        cryptobitcoin/Utils.cpp

        structure/block/block.cpp
        structure/block/blockHeader.cpp
        structure/transaction/RawTransaction.cpp
        structure/transaction/TransactionOutput.cpp
        structure/transaction/TransactionInput.cpp
        structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp
        structure/type/DVarInt.cpp
        structure/type/DScript.cpp
        structure/type/Outpoint.cpp

        persistence/DAOBlockchain.cpp
        persistence/DAOException.cpp
        persistence/json/DAOBlkToJson.cpp
        persistence/json/DAOJson.cpp
        persistence/SerializationUtil.cpp

        crypto/UtilCrypto.cpp
        crypto/CryptoCore.cpp

        core/ConfiguratorSingleton.cpp

        #cpp-properties file include
        include/cpp-properties/src/Properties.cpp
        include/cpp-properties/src/PropertiesParser.cpp
        include/cpp-properties/src/PropertiesUtils.cpp

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
        structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp
        structure/type/DVarInt.cpp
        structure/type/DScript.cpp
        structure/type/Outpoint.cpp

        persistence/DAOException.cpp
        persistence/DAOBlockchain.cpp
        persistence/DAOException.cpp
        persistence/SerializationUtil.cpp
        persistence/json/DAOBlkToJson.cpp
        persistence/json/DAOJson.cpp

        crypto/UtilCrypto.cpp
        crypto/CryptoCore.cpp

        cryptobitcoin/Sha256.cpp
        cryptobitcoin/Sha256Hash.cpp
        cryptobitcoin/Utils.cpp

        #cpp-properties file include
        include/cpp-properties/src/Properties.cpp
        include/cpp-properties/src/PropertiesParser.cpp
        include/cpp-properties/src/PropertiesUtils.cpp

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



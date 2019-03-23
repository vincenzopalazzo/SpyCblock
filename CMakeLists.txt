cmake_minimum_required(VERSION 3.9)
project(spyCblock)

set(CMAKE_CXX_STANDARD 17)

# Locate GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#Glog
find_package(glog 0.3.5 REQUIRED)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test/RunTest.cpp util/uint256.cpp structure/block/block.cpp structure/block/blockHeader.cpp
        structure/transaction/RawTransaction.cpp structure/transaction/TransactionOutput.cpp
        structure/transaction/TransactionInput.cpp structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp structure/type/DVarInt.cpp structure/type/DScript.cpp
        structure/type/Outpoint.cpp util/strencodings.cpp util/prevector.cpp test/DAOBlockchainTest.cpp persistence/DAOBlockchain.cpp
        persistence/DAOException.cpp crypto/DSha256.cpp test/SHABitcoinCoreTest.cpp crypto/cryptosingleton.cpp
        cryptobitcoin/Sha256.cpp cryptobitcoin/Sha256Hash.cpp cryptobitcoin/Utils.cpp)

add_executable(${PROJECT_NAME} core/ParserMain.cpp util/uint256.cpp structure/block/block.cpp structure/block/blockHeader.cpp
        structure/transaction/RawTransaction.cpp structure/transaction/TransactionOutput.cpp
        structure/transaction/TransactionInput.cpp structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp core/SpyCBlock.cpp structure/type/DVarInt.cpp structure/type/DScript.cpp
        structure/type/Outpoint.cpp util/strencodings.cpp util/prevector.cpp persistence/DAOException.cpp persistence/DAOBlockchain.cpp
        persistence/DAOException.cpp crypto/cryptosingleton.cpp crypto/DSha256.cpp cryptobitcoin/Sha256.cpp cryptobitcoin/Sha256Hash.cpp
        cryptobitcoin/Utils.cpp)

#using glog
target_link_libraries(${PROJECT_NAME} glog::glog)
target_link_libraries(runTests glog::glog)
#using gtest
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
##using filesystem
target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(runTests stdc++fs)


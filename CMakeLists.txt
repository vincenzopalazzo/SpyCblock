cmake_minimum_required(VERSION 2.6)
project(spyCblock)

set(CMAKE_CXX_STANDARD 14)

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
        structure/type/Outpoint.cpp core/SpyCBlock.cpp structure/type/DVarInt.cpp structure/type/DScript.cpp structure/type/Outpoint.cpp)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

target_link_libraries(runTests glog::glog)

add_executable(spyCblock core/ParserMain.cpp util/uint256.cpp structure/block/block.cpp structure/block/blockHeader.cpp
        structure/transaction/RawTransaction.cpp structure/transaction/TransactionOutput.cpp
        structure/transaction/TransactionInput.cpp structure/script/scriptCode.cpp
        structure/type/Outpoint.cpp core/SpyCBlock.cpp structure/type/DVarInt.cpp structure/type/DScript.cpp structure/type/Outpoint.cpp)

target_link_libraries(spyCblock glog::glog)

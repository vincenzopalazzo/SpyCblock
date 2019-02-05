cmake_minimum_required(VERSION 2.6)
project(parsingBlockchain)

set(CMAKE_CXX_STANDARD 14)

# Locate GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test/RunTest.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_executable(parsingBlockchain structure/block/blockHeader.cpp structure/block/blockHeader.h structure/block/block.cpp structure/block/block.h structure/transaction/RawTransaction.cpp structure/transaction/RawTransaction.h structure/transaction/TransactionOutput.cpp structure/transaction/TransactionOutput.h structure/transaction/TransactionInput.cpp structure/transaction/TransactionInput.h type/Outpoint.h structure/script/scriptCode.cpp structure/script/scriptCode.h ParserBlock.cpp type/Outpoint.cpp type/DScript.cpp type/DScript.h type/DVarInt.cpp type/DVarInt.h)
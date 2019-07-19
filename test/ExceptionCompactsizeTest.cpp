/*
 * MIT License
 *
 * Copyright (c) 2019 Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>
#include <utility>

#include "../structure/block/block.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"
#include "../core/ConfiguratorSingleton.h"

using namespace std;
using namespace spyCBlock;

/**
 * This battery of tests was developed to solve
 * the exception generated by the bitcoin core library when
 * I go to pareserize the blk files> = 976
 *
 * The exception is
 * unknown file: Failure
 * C++ exception with description
 * "ReadCompactSize(): size too large: iostream error" thrown in the test body.
 *
 * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a
 * subsequent rewrite of the way in which data structures are used and how memory is allocated,
 * so as to decrease the workload on processor and RAM
 *
 * @author https://github.com/vincenzopalazzo
 */

//Test for the first file blk that generated exception
TEST(ExceptionGenerateCompactSizeTest, test_exception_compactsize_file_blk976)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_INFO, pathLogRoot.append("test_exception_compactsize_file_blk976.log").c_str());

    DAOBlockchain daoBlockchain;
    try {
        string path = pathMockRoot.append("bitcoin/block/bug/blk976");

        vector<unique_ptr<Block>> allBlocks = daoBlockchain.loadBlocks(path);
        ASSERT_TRUE(allBlocks.size() > 120);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

}

//Test for the last file blk that generated exception
TEST(ExceptionGenerateCompactSizeTest, test_exception_compactsize_file_blk975)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, pathLogRoot.append("test_exception_compactsize_file_blk975.log").c_str());

    DAOBlockchain daoBlockchain;
    try {
        string path = pathMockRoot.append("bitcoin/block/bug/blk975");

        vector<unique_ptr<Block>> allBlocks = daoBlockchain.loadBlocks(path);
        ASSERT_EQ(135, allBlocks.size());
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

}

//Test for the another file blk that generated exception
TEST(ExceptionGenerateCompactSizeTest, test_exception_compactsize_file_blk977)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_INFO, pathLogRoot.append("test_exception_compactsize_file_blk977.log").c_str());

    DAOBlockchain daoBlockchain;
    try {
        string path = pathMockRoot.append("bitcoin/block/bug/blk977");

        vector<unique_ptr<Block>> allBlocks = daoBlockchain.loadBlocks(path);
        ASSERT_TRUE(allBlocks.size() > 120);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

}

//Test for the another file blk that generated exception
TEST(ExceptionGenerateCompactSizeTest, test_exception_compactsize_file_blk1124)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLog() + "/";

    FLAGS_minloglevel = 0;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_INFO, pathMockRoot.append("test_exception_compactsize_file_blk1124.log").c_str());

    DAOBlockchain daoBlockchain;
    try {
        string path = pathMockRoot.append("bitcoin/block/bug/blk1124");

        vector<unique_ptr<Block>> allBlocks = daoBlockchain.loadBlocks(path);
        ASSERT_TRUE(allBlocks.size() > 50);
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }

}

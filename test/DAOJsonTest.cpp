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
#include "../persistence/json/DAOJson.h"
#include "../persistence/DAOException.h"

using namespace std;
using namespace spyCBlock;

/**
  * Test battery developed to test the DAO for reading all the blk files and
  * the conversion to json of all the corresponding deserialized blk.
  * For more information on DAoJson, look at the source file DAoJson.h and .cpp
  *
  * The alpha version of this project reports a big problem in memory allocation and therefore this leads to a
  * subsequent rewrite of the way in which data structures are used and how memory is allocated,
  * so as to decrease the workload on processor and RAM
  *
  * @author https://github.com/vincenzopalazzo
  *
  */

//First test for decode all files blk into bitcoin diretory blocks
TEST(DAOJsonTest, test_dao_blk_to_json_blockchain_give_file_data_dao_json_test) {
    //Init logger
    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, "/home/vincenzo/Github/SpyCblock/test/log/test_dao_blk_to_json_blockchain_give_file_data_dao_json_test.log");

    DAOJson dao;
    try {
        bool result = dao.saveBlock("/media/vincenzo/vincenzodev/data-mock/tmp/bitcoin/block/blk00450.dat", "/media/vincenzo/vincenzodev/data-mock/tmp/bitcoin/blockJson/blk00450.json");
        ASSERT_TRUE(result); // are inclusind left block in the file blk
    }
    catch (DAOException exception) {
        FAIL() << "Test fail for this cause" << exception.what();
    }
}

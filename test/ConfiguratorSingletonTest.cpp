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
#include <glog/logging.h>

#include "../src/core/ConfiguratorSingleton.h"

#include "../src/structure/transaction/RawTransaction.h"

using namespace std;
using namespace spyCBlock;

/**
  * Test battery developed to test ConfiguratorTest
  *
  * @author https://github.com/vincenzopalazzo
  *
  */

TEST(ConfiguratorSingletonTest, inizialize_test_with_file_config)
{
  //Init logger
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_FALSE(configuration.getPathBlockDat().empty());
}

TEST(ConfiguratorSingletonTest, test_get_height_block_to_start)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_TRUE(configuration.getStartHeightBlock() >= 0);
}

TEST(ConfiguratorSingletonTest, test_get_delimitator_informations_link)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_FALSE(configuration.getDelimitatorLinkInformations().empty());
}

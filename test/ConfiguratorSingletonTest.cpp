// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt


#include <gtest/gtest.h>
#include <utility>
#include <glog/logging.h>

#include "../src/core/ConfiguratorSingleton.h"

#include "../src/structure/transaction/RawTransaction.h"

using namespace std;
using namespace spyCBlock;

/**
  * Unit test developed to test ConfiguratorTest
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

TEST(ConfiguratorSingletonTest, test_log_level)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_TRUE(configuration.getLevelLog() == 2);
}

TEST(ConfiguratorSingletonTest, test_parallel_execution)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_FALSE(configuration.isParallelExecution());
}

TEST(ConfiguratorSingletonTest, test_compression_data)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_FALSE(configuration.isCompressionResult());
}

TEST(ConfiguratorSingletonTest, test_how_many_file_will_be_read)
{
  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;

  ConfiguratorSingleton configuration = ConfiguratorSingleton::getInstance();

  ASSERT_EQ(-1, configuration.getHowManyFileWouldBeRead());
}

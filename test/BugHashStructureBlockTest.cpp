// Copyright (c) 2018-2019 Vincenzo Palazzo vicenzopalazzodev@gmail.com
// Distributed under the Apache License Version 2.0 software license,
// see https://www.apache.org/licenses/LICENSE-2.0.txt

#include <gtest/gtest.h>

#include <utility>

#include "../src/core/ConfiguratorSingleton.h"
#include "../src/persistence/DAOException.h"
#include "../src/persistence/json/DAOJson.h"
#include "../src/structure/block/Block.h"

using namespace std;
using namespace spyCBlock;

/**
 * Unit test developed for fix the bug when the parser calculate the
 * transaction hash.
 * @author https://github.com/vincenzopalazzo
 *
 */

TEST(StructureBitcoinCoreTest, test_for_analisis_structure) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_logtostderr = false;
  FLAGS_minloglevel = 2;
  google::SetLogDestination(
      google::GLOG_ERROR,
      localPathRoot.append("count_all_block_another_file_blk.log").c_str());

  // Init data for start this test
  ifstream stream(pathMockRoot + "bitcoin/block/bug/blk944/blk00944.dat");
  int count = 0;
  Block blockChecked;
  while (!stream.eof()) {
    Block block;
    block.decode(stream);
    count++;
    if (block.getHashBlock() ==
        "000000000000000000464e5a3ce4aeaa830a7955ef9b6fdebe3da8d0dcac1bd5") {
      blockChecked = block;
      break;
    }
  }

  stream.close();

  RawTransaction raw = blockChecked.getRawTransactions().at(106);
  LOG(INFO) << raw.toSerealizationForm();
  ASSERT_EQ(30, raw.getNumberTxOut().getValue());
  ASSERT_EQ(3, raw.getNumberTxIn().getValue());

  // ----- TEST TX INPUT
  ASSERT_EQ("2a27348a0320d632460c87cc6732f78b96072f498bc5df8b1d38cedbbb397456",
            raw.getTxIn().at(0).getOutpoint().getHash().GetHex());
  ASSERT_EQ(0, raw.getTxIn().at(0).getOutpoint().getN());
  ASSERT_EQ(252, raw.getTxIn().at(0).getScript().getScriptLength().getValue());
  ASSERT_EQ(
      "0047304402204019206b38075e308633c7ce1ec0e9d82aa42da216f93d9ee05574"
      "86fd320007022070568e2f0a607cf19b05a6ca70993c8eef496aba61ddbbac7d62"
      "98c138961f430147304402201e8928d5f0d47e05e8b8c23c9196e3eff347a0acfa"
      "77ac4bd2cf0874727d7b4602206096ddb026821c66bd2d5a92e55de8d10abb6fa8"
      "8b88ff7400e2ff8b431d184e014c69522102d3c6abf94e08b389bc60dc6feb4f1e"
      "efe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851"
      "c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1"
      "a498403a8bc3fc76f24000ec1b4114b9017d2553ae",
      raw.getTxIn().at(0).getScript().getRawScriptString());
  LOG(ERROR) << raw.getTxIn().at(0).toSerealizationForm();
  ASSERT_EQ("b7d979000a063dade6c69fe9adcd2e6cb0da34c21c8974e9e9b73d0287524314",
            raw.getTxIn().at(1).getOutpoint().getHash().GetHex());
  ASSERT_EQ(1, raw.getTxIn().at(1).getOutpoint().getN());
  ASSERT_EQ(252, raw.getTxIn().at(1).getScript().getScriptLength().getValue());
  ASSERT_EQ(
      "00473044022070cf7b804b37effe1025cecc278216f2093fbbbc6ae91b950b7aca"
      "e44e38e2ef02200673a311b70f69e1e6276664dd002e58f38711cdb1d1ce3fd7e4"
      "46beefdad3af014730440220407723e46a94f16878e50e4726e2c0aba79fbcca6f"
      "3b14d4777179c71d455f41022052a3abcb565f4ed3468c3b27d90b074c1655fa6f"
      "d062a23b3026afc7c2838ff6014c69522102d3c6abf94e08b389bc60dc6feb4f1e"
      "efe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851"
      "c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1"
      "a498403a8bc3fc76f24000ec1b4114b9017d2553ae",
      raw.getTxIn().at(1).getScript().getRawScriptString());

  ASSERT_EQ("bc89ce3f31b649d9f5f2680654136a1a8a1414e6b8bb26f0932f492ddc0e6c38",
            raw.getTxIn().at(2).getOutpoint().getHash().GetHex());
  ASSERT_EQ(0, raw.getTxIn().at(2).getOutpoint().getN());
  ASSERT_EQ(253, raw.getTxIn().at(2).getScript().getScriptLength().getValue());
  ASSERT_EQ(
      "0047304402202b4afe04209cdb17a67a1b4881396ef44eaedad7ac663a555d2a84"
      "5c809bc24e02202456bc52d49c1c5550cd4bd2db648e96352e388f0cce040792df"
      "5ca528e9a9c1014830450221008819ed1f425826ba739b49478375b4dfd1e54435"
      "03fc0d20ee67a4d904be325f022007a2f9ed0b519bdcac327d5227045d1c348b80"
      "ee7ceeb1102ef01d2560c26ead014c69522102d3c6abf94e08b389bc60dc6feb4f"
      "1eefe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f48"
      "51c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1"
      "f1a498403a8bc3fc76f24000ec1b4114b9017d2553ae",
      raw.getTxIn().at(2).getScript().getRawScriptString());

  // ------- TEST Transaction Output
  /**
   * Value:		 13000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       e3c7203bf45802c9de1d90d8960399c2dc5bf4ef
      ScriptPubkey:	 76a914e3c7203bf45802c9de1d90d8960399c2dc5bf4ef88ac
   */
  ASSERT_EQ("76a914e3c7203bf45802c9de1d90d8960399c2dc5bf4ef88ac",
            raw.getTxOut().at(0).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(0).getScript().getScriptLength().getValue());
  ASSERT_EQ(13000, raw.getTxOut().at(0).getNValue());

  /**
   * Value:		 940000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
   */

  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(1).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(1).getScript().getScriptLength().getValue());
  ASSERT_EQ(940000, raw.getTxOut().at(1).getNValue());

  /**
   * Value:		 1012600 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       c40fd4ceec58366f60b8b73ac6e38d69ad245b5a
      ScriptPubkey:	 76a914c40fd4ceec58366f60b8b73ac6e38d69ad245b5a88ac
   */
  ASSERT_EQ("76a914c40fd4ceec58366f60b8b73ac6e38d69ad245b5a88ac",
            raw.getTxOut().at(2).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(2).getScript().getScriptLength().getValue());
  ASSERT_EQ(1012600, raw.getTxOut().at(2).getNValue());

  /**
   * Value:		 1088000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       898fd12245586a4030ae2becbe3d32028ba9dcea
      ScriptPubkey:	 76a914898fd12245586a4030ae2becbe3d32028ba9dcea88ac
   */
  ASSERT_EQ("76a914898fd12245586a4030ae2becbe3d32028ba9dcea88ac",
            raw.getTxOut().at(3).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(3).getScript().getScriptLength().getValue());
  ASSERT_EQ(1088000, raw.getTxOut().at(3).getNValue());

  /**
   * Value:		 1199730 Satoshi
      Script Len:	 23
      Pubkey OP_CODE:	 OP_HASH160  Bytes:20 tail_op_code:OP_EQUAL
      Pure Pubkey:	     3fa5f3e2d311a9925a0f43a6af24a8203aa4c472
      ScriptPubkey:	 a9143fa5f3e2d311a9925a0f43a6af24a8203aa4c47287
   */
  ASSERT_EQ("a9143fa5f3e2d311a9925a0f43a6af24a8203aa4c47287",
            raw.getTxOut().at(4).getScript().getRawScriptString());
  ASSERT_EQ(23, raw.getTxOut().at(4).getScript().getScriptLength().getValue());
  ASSERT_EQ(1199730, raw.getTxOut().at(4).getNValue());

  /**
   * Value:		 1250000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       0dad867765f83dae4672d35f715e3376a957ee8a
      ScriptPubkey:	 76a9140dad867765f83dae4672d35f715e3376a957ee8a88ac
   */

  ASSERT_EQ("76a9140dad867765f83dae4672d35f715e3376a957ee8a88ac",
            raw.getTxOut().at(5).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(5).getScript().getScriptLength().getValue());
  ASSERT_EQ(1250000, raw.getTxOut().at(5).getNValue());

  /**
   * Value:		 1280000 Satoshi
      Script Len:	 23
      Pubkey OP_CODE:	 OP_HASH160  Bytes:20 tail_op_code:OP_EQUAL
      Pure Pubkey:	     b92c970fac1eed7d6f2bef2848f11b8f0ab3bf03
      ScriptPubkey:	 a914b92c970fac1eed7d6f2bef2848f11b8f0ab3bf0387
   */
  ASSERT_EQ("a914b92c970fac1eed7d6f2bef2848f11b8f0ab3bf0387",
            raw.getTxOut().at(6).getScript().getRawScriptString());
  ASSERT_EQ(23, raw.getTxOut().at(6).getScript().getScriptLength().getValue());
  ASSERT_EQ(1280000, raw.getTxOut().at(6).getNValue());

  /*
   *Value:		 1290000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       80aadad1a04336e23b4d95e9fc98cad18c5178f4
      ScriptPubkey:	 76a91480aadad1a04336e23b4d95e9fc98cad18c5178f488ac
    */
  ASSERT_EQ("76a91480aadad1a04336e23b4d95e9fc98cad18c5178f488ac",
            raw.getTxOut().at(7).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(7).getScript().getScriptLength().getValue());
  ASSERT_EQ(1290000, raw.getTxOut().at(7).getNValue());

  /*
   * Value:		 1326000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       78c13605093a36e309c7d1c277330635114e9422
      ScriptPubkey:	 76a91478c13605093a36e309c7d1c277330635114e942288ac
  */

  ASSERT_EQ("76a91478c13605093a36e309c7d1c277330635114e942288ac",
            raw.getTxOut().at(8).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(8).getScript().getScriptLength().getValue());
  ASSERT_EQ(1326000, raw.getTxOut().at(8).getNValue());

  /**
   * Value:		 1410000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       0dad867765f83dae4672d35f715e3376a957ee8a
      ScriptPubkey:	 76a9140dad867765f83dae4672d35f715e3376a957ee8a88ac
   */

  ASSERT_EQ("76a9140dad867765f83dae4672d35f715e3376a957ee8a88ac",
            raw.getTxOut().at(9).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(9).getScript().getScriptLength().getValue());
  ASSERT_EQ(1410000, raw.getTxOut().at(9).getNValue());

  /**
   * Value:		 1410000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
   */

  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(10).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(10).getScript().getScriptLength().getValue());
  ASSERT_EQ(1410000, raw.getTxOut().at(10).getNValue());

  /**
   * Value:		 1410000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
   */
  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(11).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(11).getScript().getScriptLength().getValue());
  ASSERT_EQ(1410000, raw.getTxOut().at(11).getNValue());

  /**
   * Value:		 1410000 Satoshi
      Script Len:	 23
      Pubkey OP_CODE:	 OP_HASH160  Bytes:20 tail_op_code:OP_EQUAL
      Pure Pubkey:	     ece573b37df3e225cacedca8bdda281ffa4821a6
      ScriptPubkey:	 a914ece573b37df3e225cacedca8bdda281ffa4821a687
   */
  ASSERT_EQ("a914ece573b37df3e225cacedca8bdda281ffa4821a687",
            raw.getTxOut().at(12).getScript().getRawScriptString());
  ASSERT_EQ(23, raw.getTxOut().at(12).getScript().getScriptLength().getValue());
  ASSERT_EQ(1410000, raw.getTxOut().at(12).getNValue());

  /**
   * Value:		 1410000 Satoshi
      Script Len:	 23
      Pubkey OP_CODE:	 OP_HASH160  Bytes:20 tail_op_code:OP_EQUAL
      Pure Pubkey:	     fee7a4f36c10be14f2fee86ede0b4e20f74b8b35
      ScriptPubkey:	 a914fee7a4f36c10be14f2fee86ede0b4e20f74b8b3587
   */
  ASSERT_EQ("a914fee7a4f36c10be14f2fee86ede0b4e20f74b8b3587",
            raw.getTxOut().at(13).getScript().getRawScriptString());
  ASSERT_EQ(23, raw.getTxOut().at(13).getScript().getScriptLength().getValue());
  ASSERT_EQ(1410000, raw.getTxOut().at(13).getNValue());

  /**
   * Value:		 1647000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       e3c7203bf45802c9de1d90d8960399c2dc5bf4ef
      ScriptPubkey:	 76a914e3c7203bf45802c9de1d90d8960399c2dc5bf4ef88ac
   */
  ASSERT_EQ("76a914e3c7203bf45802c9de1d90d8960399c2dc5bf4ef88ac",
            raw.getTxOut().at(14).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(14).getScript().getScriptLength().getValue());
  ASSERT_EQ(1647000, raw.getTxOut().at(14).getNValue());

  /**
   * Value:		 1647000 Satoshi
      Script Len:	 23
      Pubkey OP_CODE:	 OP_HASH160  Bytes:20 tail_op_code:OP_EQUAL
      Pure Pubkey:	     b0bfb114c92a28db0b3d0a93815cf0e223438729
      ScriptPubkey:	 a914b0bfb114c92a28db0b3d0a93815cf0e22343872987
   */
  ASSERT_EQ("a914b0bfb114c92a28db0b3d0a93815cf0e22343872987",
            raw.getTxOut().at(15).getScript().getRawScriptString());
  ASSERT_EQ(23, raw.getTxOut().at(15).getScript().getScriptLength().getValue());
  ASSERT_EQ(1647000, raw.getTxOut().at(15).getNValue());

  /**
   * Value:		 2250000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       13192ab5b60be76455e1f1539533aa1f58dc07c8
      ScriptPubkey:	 76a91413192ab5b60be76455e1f1539533aa1f58dc07c888ac
   */

  ASSERT_EQ("76a91413192ab5b60be76455e1f1539533aa1f58dc07c888ac",
            raw.getTxOut().at(16).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(16).getScript().getScriptLength().getValue());
  ASSERT_EQ(2250000, raw.getTxOut().at(16).getNValue());

  /**
   * Value:		 2273000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       692316b5684153f35b245f55ded4183c276df7a3
      ScriptPubkey:	 76a914692316b5684153f35b245f55ded4183c276df7a388ac
   */

  ASSERT_EQ("76a914692316b5684153f35b245f55ded4183c276df7a388ac",
            raw.getTxOut().at(17).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(17).getScript().getScriptLength().getValue());
  ASSERT_EQ(2273000, raw.getTxOut().at(17).getNValue());

  /**
   * Value:		 2374000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       af7d5f688b1760255f0c522fed16e7ded5ff314a
      ScriptPubkey:	 76a914af7d5f688b1760255f0c522fed16e7ded5ff314a88ac
   */

  ASSERT_EQ("76a914af7d5f688b1760255f0c522fed16e7ded5ff314a88ac",
            raw.getTxOut().at(18).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(18).getScript().getScriptLength().getValue());
  ASSERT_EQ(2374000, raw.getTxOut().at(18).getNValue());

  /**
   * Value:		 3570000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       e7bc58ab367f021dff913c38c55894e415306f46
      ScriptPubkey:	 76a914e7bc58ab367f021dff913c38c55894e415306f4688ac
   */

  ASSERT_EQ("76a914e7bc58ab367f021dff913c38c55894e415306f4688ac",
            raw.getTxOut().at(19).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(19).getScript().getScriptLength().getValue());
  ASSERT_EQ(3570000, raw.getTxOut().at(19).getNValue());

  /**
   * Value:		 5232000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       d070fdc4539046a6fcd2b1194588b56bd78148ee
      ScriptPubkey:	 76a914d070fdc4539046a6fcd2b1194588b56bd78148ee88ac
   */

  ASSERT_EQ("76a914d070fdc4539046a6fcd2b1194588b56bd78148ee88ac",
            raw.getTxOut().at(20).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(20).getScript().getScriptLength().getValue());
  ASSERT_EQ(5232000, raw.getTxOut().at(20).getNValue());

  /**
   * Value:		 6295000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       88fce37fce66b56bf759d8b52b01c147627fabd8
      ScriptPubkey:	 76a91488fce37fce66b56bf759d8b52b01c147627fabd888ac
   */

  ASSERT_EQ("76a91488fce37fce66b56bf759d8b52b01c147627fabd888ac",
            raw.getTxOut().at(21).getScript().getRawScriptString());
  ASSERT_EQ(25, raw.getTxOut().at(21).getScript().getScriptLength().getValue());
  ASSERT_EQ(6295000, raw.getTxOut().at(21).getNValue());

  /**
   * Value:		 6951000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       d5de03f5e78843e139222d68f491f25b6f5ac5b0
      ScriptPubkey:	 76a914d5de03f5e78843e139222d68f491f25b6f5ac5b088ac
   */
  size_t index = 22;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(6951000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a914d5de03f5e78843e139222d68f491f25b6f5ac5b088ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /*
   *Value:		 6979000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
   */

  index = 23;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(6979000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /**
      Value:		 7013000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
     OP_CHECKSIG PubkeyHash:	       5eb9cb524c326d03d30240ddc64405e4453976ca
      ScriptPubkey:	 76a9145eb9cb524c326d03d30240ddc64405e4453976ca88ac
    */
  index = 24;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(7013000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a9145eb9cb524c326d03d30240ddc64405e4453976ca88ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /**
      Value:		 8276000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
     OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
    */

  index = 25;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(8276000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /*
   *
   *Value:		 8505000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       78c13605093a36e309c7d1c277330635114e9422
      ScriptPubkey:	 76a91478c13605093a36e309c7d1c277330635114e942288ac
    */

  index = 26;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(8505000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a91478c13605093a36e309c7d1c277330635114e942288ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /**
      Value:		 15654000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
     OP_CHECKSIG PubkeyHash:	       84f292a49dfd25bcd1797b6827a9a770629d3597
      ScriptPubkey:	 76a91484f292a49dfd25bcd1797b6827a9a770629d359788ac
    */

  index = 27;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(15654000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a91484f292a49dfd25bcd1797b6827a9a770629d359788ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /*
   * Value:		 21539000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
   * */

  index = 28;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(21539000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());

  /*
   * Value:		 55423000 Satoshi
      Script Len:	 25
      Pubkey OP_CODE:	 OP_DUP OP_HASH160  Bytes:20 tail_op_code:OP_EQUALVERIFY
   OP_CHECKSIG PubkeyHash:	       51ea27804b44d6085ce1f885ae16e74436913b9b
      ScriptPubkey:	 76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac
  */

  index = 29;
  ASSERT_EQ(25,
            raw.getTxOut().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(55423000, raw.getTxOut().at(index).getNValue());
  ASSERT_EQ("76a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac",
            raw.getTxOut().at(index).getScript().getRawScriptString());
  LOG(ERROR) << raw.toSerealizationForm();
  ASSERT_EQ(
      "0100000003567439bbdbce381d8bdfc58b492f07968bf73267cc870c4632d620038a3427"
      "2a00000000fc0047304402204019206b38075e308633c7ce1ec0e9d82aa42da216f93d9e"
      "e0557486fd320007022070568e2f0a607cf19b05a6ca70993c8eef496aba61ddbbac7d62"
      "98c138961f430147304402201e8928d5f0d47e05e8b8c23c9196e3eff347a0acfa77ac4b"
      "d2cf0874727d7b4602206096ddb026821c66bd2d5a92e55de8d10abb6fa88b88ff7400e2"
      "ff8b431d184e014c69522102d3c6abf94e08b389bc60dc6feb4f1eefe2244fc459a3fabb"
      "08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851c374dc6381f7da0c3fd7a643"
      "2043159eb26521039b9f33d76aecbd6fbdb7f8a1f1a498403a8bc3fc76f24000ec1b4114"
      "b9017d2553aeffffffff14435287023db7e9e974891cc234dab06c2ecdade99fc6e6ad3d"
      "060a0079d9b701000000fc00473044022070cf7b804b37effe1025cecc278216f2093fbb"
      "bc6ae91b950b7acae44e38e2ef02200673a311b70f69e1e6276664dd002e58f38711cdb1"
      "d1ce3fd7e446beefdad3af014730440220407723e46a94f16878e50e4726e2c0aba79fbc"
      "ca6f3b14d4777179c71d455f41022052a3abcb565f4ed3468c3b27d90b074c1655fa6fd0"
      "62a23b3026afc7c2838ff6014c69522102d3c6abf94e08b389bc60dc6feb4f1eefe2244f"
      "c459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851c374dc6381f7da"
      "0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1a498403a8bc3fc76f240"
      "00ec1b4114b9017d2553aeffffffff386c0edc2d492f93f026bbb8e614148a1a6a135406"
      "68f2f5d949b6313fce89bc00000000fdfd000047304402202b4afe04209cdb17a67a1b48"
      "81396ef44eaedad7ac663a555d2a845c809bc24e02202456bc52d49c1c5550cd4bd2db64"
      "8e96352e388f0cce040792df5ca528e9a9c1014830450221008819ed1f425826ba739b49"
      "478375b4dfd1e5443503fc0d20ee67a4d904be325f022007a2f9ed0b519bdcac327d5227"
      "045d1c348b80ee7ceeb1102ef01d2560c26ead014c69522102d3c6abf94e08b389bc60dc"
      "6feb4f1eefe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f48"
      "51c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1a498"
      "403a8bc3fc76f24000ec1b4114b9017d2553aeffffffff1ec8320000000000001976a914"
      "e3c7203bf45802c9de1d90d8960399c2dc5bf4ef88ace0570e00000000001976a91451ea"
      "27804b44d6085ce1f885ae16e74436913b9b88ac78730f00000000001976a914c40fd4ce"
      "ec58366f60b8b73ac6e38d69ad245b5a88ac009a1000000000001976a914898fd1224558"
      "6a4030ae2becbe3d32028ba9dcea88ac724e12000000000017a9143fa5f3e2d311a9925a"
      "0f43a6af24a8203aa4c47287d0121300000000001976a9140dad867765f83dae4672d35f"
      "715e3376a957ee8a88ac008813000000000017a914b92c970fac1eed7d6f2bef2848f11b"
      "8f0ab3bf038710af1300000000001976a91480aadad1a04336e23b4d95e9fc98cad18c51"
      "78f488acb03b1400000000001976a91478c13605093a36e309c7d1c277330635114e9422"
      "88acd0831500000000001976a9140dad867765f83dae4672d35f715e3376a957ee8a88ac"
      "d0831500000000001976a91451ea27804b44d6085ce1f885ae16e74436913b9b88acd083"
      "1500000000001976a91451ea27804b44d6085ce1f885ae16e74436913b9b88acd0831500"
      "0000000017a914ece573b37df3e225cacedca8bdda281ffa4821a687d083150000000000"
      "17a914fee7a4f36c10be14f2fee86ede0b4e20f74b8b358798211900000000001976a914"
      "e3c7203bf45802c9de1d90d8960399c2dc5bf4ef88ac982119000000000017a914b0bfb1"
      "14c92a28db0b3d0a93815cf0e2234387298710552200000000001976a91413192ab5b60b"
      "e76455e1f1539533aa1f58dc07c888ace8ae2200000000001976a914692316b5684153f3"
      "5b245f55ded4183c276df7a388ac70392400000000001976a914af7d5f688b1760255f0c"
      "522fed16e7ded5ff314a88ac50793600000000001976a914e7bc58ab367f021dff913c38"
      "c55894e415306f4688ac80d54f00000000001976a914d070fdc4539046a6fcd2b1194588"
      "b56bd78148ee88acd80d6000000000001976a91488fce37fce66b56bf759d8b52b01c147"
      "627fabd888ac58106a00000000001976a914d5de03f5e78843e139222d68f491f25b6f5a"
      "c5b088acb87d6a00000000001976a91451ea27804b44d6085ce1f885ae16e74436913b9b"
      "88ac88026b00000000001976a9145eb9cb524c326d03d30240ddc64405e4453976ca88ac"
      "20487e00000000001976a91451ea27804b44d6085ce1f885ae16e74436913b9b88aca8c6"
      "8100000000001976a91478c13605093a36e309c7d1c277330635114e942288ac70dcee00"
      "000000001976a91484f292a49dfd25bcd1797b6827a9a770629d359788acb8a848010000"
      "00001976a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac18b04d0300000000"
      "1976a91451ea27804b44d6085ce1f885ae16e74436913b9b88ac00000000",
      raw.toSerealizationForm());

  ASSERT_EQ("c8686d102b9944c70d215675956f3bc7a6c17dc917b44306ad7b956ae85287c7",
            raw.getHashRawTransaction());
}

TEST(StructureBitcoinCoreTest, test_for_serialization_structure) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_logtostderr = false;
  FLAGS_minloglevel = 2;
  google::SetLogDestination(
      google::GLOG_ERROR,
      localPathRoot.append("test_for_serialization_structure.log").c_str());

  // Init data for start this test
  ifstream stream(pathMockRoot + "bitcoin/block/bug/blk944/blk00944.dat");
  int count = 0;
  Block blockChecked;
  while (!stream.eof()) {
    Block block;
    block.decode(stream);
    count++;
    if (block.getHashBlock() ==
        "000000000000000000464e5a3ce4aeaa830a7955ef9b6fdebe3da8d0dcac1bd5") {
      blockChecked = block;
      break;
    }
  }

  stream.close();

  RawTransaction raw = blockChecked.getRawTransactions().at(106);

  string versionHex = SerializationUtil::toSerealizeForm(raw.getVersion());
  ASSERT_EQ("01000000", versionHex);
  string numTxInputHex =
      SerializationUtil::toSerealizeForm(raw.getNumberTxIn());
  ASSERT_EQ("03", numTxInputHex);

  string hexInputs;
  for (size_t i = 0; i < raw.getTxIn().size(); i++) {
    hexInputs.append(raw.getTxIn().at(i).toSerealizationForm());
  }

  ASSERT_EQ(
      "567439bbdbce381d8bdfc58b492f07968bf73267cc870c4632d620038a34272a00000000"
      "fc0047304402204019206b38075e308633c7ce1ec0e9d82aa42da216f93d9ee0557486fd"
      "320007022070568e2f0a607cf19b05a6ca70993c8eef496aba61ddbbac7d6298c138961f"
      "430147304402201e8928d5f0d47e05e8b8c23c9196e3eff347a0acfa77ac4bd2cf087472"
      "7d7b4602206096ddb026821c66bd2d5a92e55de8d10abb6fa88b88ff7400e2ff8b431d18"
      "4e014c69522102d3c6abf94e08b389bc60dc6feb4f1eefe2244fc459a3fabb08f0cecf2b"
      "7c3cdc210301b601dfcdbe32d1b9f75f9f4851c374dc6381f7da0c3fd7a6432043159eb2"
      "6521039b9f33d76aecbd6fbdb7f8a1f1a498403a8bc3fc76f24000ec1b4114b9017d2553"
      "aeffffffff14435287023db7e9e974891cc234dab06c2ecdade99fc6e6ad3d060a0079d9"
      "b701000000fc00473044022070cf7b804b37effe1025cecc278216f2093fbbbc6ae91b95"
      "0b7acae44e38e2ef02200673a311b70f69e1e6276664dd002e58f38711cdb1d1ce3fd7e4"
      "46beefdad3af014730440220407723e46a94f16878e50e4726e2c0aba79fbcca6f3b14d4"
      "777179c71d455f41022052a3abcb565f4ed3468c3b27d90b074c1655fa6fd062a23b3026"
      "afc7c2838ff6014c69522102d3c6abf94e08b389bc60dc6feb4f1eefe2244fc459a3fabb"
      "08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851c374dc6381f7da0c3fd7a643"
      "2043159eb26521039b9f33d76aecbd6fbdb7f8a1f1a498403a8bc3fc76f24000ec1b4114"
      "b9017d2553aeffffffff386c0edc2d492f93f026bbb8e614148a1a6a13540668f2f5d949"
      "b6313fce89bc00000000fdfd000047304402202b4afe04209cdb17a67a1b4881396ef44e"
      "aedad7ac663a555d2a845c809bc24e02202456bc52d49c1c5550cd4bd2db648e96352e38"
      "8f0cce040792df5ca528e9a9c1014830450221008819ed1f425826ba739b49478375b4df"
      "d1e5443503fc0d20ee67a4d904be325f022007a2f9ed0b519bdcac327d5227045d1c348b"
      "80ee7ceeb1102ef01d2560c26ead014c69522102d3c6abf94e08b389bc60dc6feb4f1eef"
      "e2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851c374dc63"
      "81f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1a498403a8bc3fc"
      "76f24000ec1b4114b9017d2553aeffffffff",
      hexInputs);

  ASSERT_EQ("c8686d102b9944c70d215675956f3bc7a6c17dc917b44306ad7b956ae85287c7",
            raw.getHashRawTransaction());
}

TEST(StructureBitcoinCoreTest, test_for_structure_txs_input) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_logtostderr = false;
  FLAGS_minloglevel = 2;
  google::SetLogDestination(
      google::GLOG_ERROR,
      localPathRoot.append("test_for_serialization_structure.log").c_str());

  // Init data for start this test
  ifstream stream(pathMockRoot + "bitcoin/block/bug/blk944/blk00944.dat");
  int count = 0;
  Block blockChecked;
  while (!stream.eof()) {
    Block block;
    block.decode(stream);
    count++;
    if (block.getHashBlock() ==
        "000000000000000000464e5a3ce4aeaa830a7955ef9b6fdebe3da8d0dcac1bd5") {
      blockChecked = block;
      break;
    }
  }

  stream.close();

  RawTransaction raw = blockChecked.getRawTransactions().at(106);

  size_t index = 0;
  ASSERT_EQ("2a27348a0320d632460c87cc6732f78b96072f498bc5df8b1d38cedbbb397456",
            raw.getTxIn().at(index).getOutpoint().getHash().GetHex());
  ASSERT_EQ(0, raw.getTxIn().at(index).getOutpoint().getN());
  ASSERT_EQ(252,
            raw.getTxIn().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(
      "0047304402204019206b38075e308633c7ce1ec0e9d82aa42da216f93d9ee05574"
      "86fd320007022070568e2f0a607cf19b05a6ca70993c8eef496aba61ddbbac7d62"
      "98c138961f430147304402201e8928d5f0d47e05e8b8c23c9196e3eff347a0acfa"
      "77ac4bd2cf0874727d7b4602206096ddb026821c66bd2d5a92e55de8d10abb6fa8"
      "8b88ff7400e2ff8b431d184e014c69522102d3c6abf94e08b389bc60dc6feb4f1e"
      "efe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851"
      "c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1"
      "a498403a8bc3fc76f24000ec1b4114b9017d2553ae",
      raw.getTxIn().at(index).getScript().getRawScriptString());
  ASSERT_EQ(4294967295, raw.getTxIn().at(index).getSequences());

  index = 1;
  ASSERT_EQ("b7d979000a063dade6c69fe9adcd2e6cb0da34c21c8974e9e9b73d0287524314",
            raw.getTxIn().at(index).getOutpoint().getHash().GetHex());
  ASSERT_EQ(1, raw.getTxIn().at(index).getOutpoint().getN());
  ASSERT_EQ(252,
            raw.getTxIn().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(
      "00473044022070cf7b804b37effe1025cecc278216f2093fbbbc6ae91b950b7aca"
      "e44e38e2ef02200673a311b70f69e1e6276664dd002e58f38711cdb1d1ce3fd7e4"
      "46beefdad3af014730440220407723e46a94f16878e50e4726e2c0aba79fbcca6f"
      "3b14d4777179c71d455f41022052a3abcb565f4ed3468c3b27d90b074c1655fa6f"
      "d062a23b3026afc7c2838ff6014c69522102d3c6abf94e08b389bc60dc6feb4f1e"
      "efe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f4851"
      "c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1f1"
      "a498403a8bc3fc76f24000ec1b4114b9017d2553ae",
      raw.getTxIn().at(index).getScript().getRawScriptString());
  ASSERT_EQ(4294967295, raw.getTxIn().at(index).getSequences());

  index = 2;
  ASSERT_EQ("bc89ce3f31b649d9f5f2680654136a1a8a1414e6b8bb26f0932f492ddc0e6c38",
            raw.getTxIn().at(index).getOutpoint().getHash().GetHex());
  ASSERT_EQ(0, raw.getTxIn().at(index).getOutpoint().getN());
  ASSERT_EQ(253,
            raw.getTxIn().at(index).getScript().getScriptLength().getValue());
  ASSERT_EQ(
      "0047304402202b4afe04209cdb17a67a1b4881396ef44eaedad7ac663a555d2a84"
      "5c809bc24e02202456bc52d49c1c5550cd4bd2db648e96352e388f0cce040792df"
      "5ca528e9a9c1014830450221008819ed1f425826ba739b49478375b4dfd1e54435"
      "03fc0d20ee67a4d904be325f022007a2f9ed0b519bdcac327d5227045d1c348b80"
      "ee7ceeb1102ef01d2560c26ead014c69522102d3c6abf94e08b389bc60dc6feb4f"
      "1eefe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f75f9f48"
      "51c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbdb7f8a1"
      "f1a498403a8bc3fc76f24000ec1b4114b9017d2553ae",
      raw.getTxIn().at(index).getScript().getRawScriptString());
  ASSERT_EQ(4294967295, raw.getTxIn().at(index).getSequences());
}

TEST(StructureBitcoinCoreTest, test_for_serialization_txs_input) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_logtostderr = false;
  FLAGS_minloglevel = 2;
  google::SetLogDestination(
      google::GLOG_ERROR,
      localPathRoot.append("test_for_serialization_structure.log").c_str());

  // Init data for start this test
  ifstream stream(pathMockRoot + "bitcoin/block/bug/blk944/blk00944.dat");
  int count = 0;
  Block blockChecked;
  while (!stream.eof()) {
    Block block;
    block.decode(stream);
    count++;
    if (block.getHashBlock() ==
        "000000000000000000464e5a3ce4aeaa830a7955ef9b6fdebe3da8d0dcac1bd5") {
      blockChecked = block;
      break;
    }
  }

  stream.close();

  RawTransaction raw = blockChecked.getRawTransactions().at(106);

  size_t index = 0;
  string hexInputOne = raw.getTxIn().at(index).toSerealizationForm();
  ASSERT_EQ(
      "567439bbdbce381d8bdfc58b492f07968bf73267cc870c4632d620038a34272a00"
      "000000fc0047304402204019206b38075e308633c7ce1ec0e9d82aa42da216f93d"
      "9ee0557486fd320007022070568e2f0a607cf19b05a6ca70993c8eef496aba61dd"
      "bbac7d6298c138961f430147304402201e8928d5f0d47e05e8b8c23c9196e3eff3"
      "47a0acfa77ac4bd2cf0874727d7b4602206096ddb026821c66bd2d5a92e55de8d1"
      "0abb6fa88b88ff7400e2ff8b431d184e014c69522102d3c6abf94e08b389bc60dc"
      "6feb4f1eefe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f7"
      "5f9f4851c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbd"
      "b7f8a1f1a498403a8bc3fc76f24000ec1b4114b9017d2553aeffffffff",
      hexInputOne);
  index = 1;
  string hexInputTwo = raw.getTxIn().at(index).toSerealizationForm();
  ASSERT_EQ(
      "14435287023db7e9e974891cc234dab06c2ecdade99fc6e6ad3d060a0079d9b701"
      "000000fc00473044022070cf7b804b37effe1025cecc278216f2093fbbbc6ae91b"
      "950b7acae44e38e2ef02200673a311b70f69e1e6276664dd002e58f38711cdb1d1"
      "ce3fd7e446beefdad3af014730440220407723e46a94f16878e50e4726e2c0aba7"
      "9fbcca6f3b14d4777179c71d455f41022052a3abcb565f4ed3468c3b27d90b074c"
      "1655fa6fd062a23b3026afc7c2838ff6014c69522102d3c6abf94e08b389bc60dc"
      "6feb4f1eefe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32d1b9f7"
      "5f9f4851c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aecbd6fbd"
      "b7f8a1f1a498403a8bc3fc76f24000ec1b4114b9017d2553aeffffffff",
      hexInputTwo);

  index = 2;
  string hexInputThird = raw.getTxIn().at(index).toSerealizationForm();
  ASSERT_EQ(
      "386c0edc2d492f93f026bbb8e614148a1a6a13540668f2f5d949b6313fce89bc00"
      "000000fdfd000047304402202b4afe04209cdb17a67a1b4881396ef44eaedad7ac"
      "663a555d2a845c809bc24e02202456bc52d49c1c5550cd4bd2db648e96352e388f"
      "0cce040792df5ca528e9a9c1014830450221008819ed1f425826ba739b49478375"
      "b4dfd1e5443503fc0d20ee67a4d904be325f022007a2f9ed0b519bdcac327d5227"
      "045d1c348b80ee7ceeb1102ef01d2560c26ead014c69522102d3c6abf94e08b389"
      "bc60dc6feb4f1eefe2244fc459a3fabb08f0cecf2b7c3cdc210301b601dfcdbe32"
      "d1b9f75f9f4851c374dc6381f7da0c3fd7a6432043159eb26521039b9f33d76aec"
      "bd6fbdb7f8a1f1a498403a8bc3fc76f24000ec1b4114b9017d2553aeffffffff",
      hexInputThird);
}

TEST(StructureBitcoinCoreTest, test_for_serialization_tx_input) {
  string pathMockRoot =
      ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot =
      ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_logtostderr = false;
  FLAGS_minloglevel = 2;
  google::SetLogDestination(
      google::GLOG_ERROR,
      localPathRoot.append("test_for_serialization_tx_input.log").c_str());

  // Init data for start this test
  ifstream stream(pathMockRoot + "bitcoin/block/bug/blk944/blk00944.dat");
  int count = 0;
  Block blockChecked;
  while (!stream.eof()) {
    Block block;
    block.decode(stream);
    count++;
    if (block.getHashBlock() ==
        "000000000000000000464e5a3ce4aeaa830a7955ef9b6fdebe3da8d0dcac1bd5") {
      blockChecked = block;
      break;
    }
  }

  stream.close();

  RawTransaction raw = blockChecked.getRawTransactions().at(106);
  TransactionInput input = raw.getTxIn().at(2);

  string hashPreviusHex =
      SerializationUtil::toSerealizeForm(input.getOutpoint().getHash());
  ASSERT_EQ("386c0edc2d492f93f026bbb8e614148a1a6a13540668f2f5d949b6313fce89bc",
            hashPreviusHex);

  string indexHex =
      SerializationUtil::toSerealizeForm(input.getOutpoint().getN());
  ASSERT_EQ("00000000", indexHex);

  string scripSigLenght =
      SerializationUtil::toSerealizeForm(input.getScript().getScriptLength());
  ASSERT_EQ("fdfd00", scripSigLenght);
}

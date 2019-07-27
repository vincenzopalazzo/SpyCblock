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

#include <fstream>
#include <utility>

#include <gtest/gtest.h>
#include <glog/logging.h>
#include "../util/uint256.h"
#include "../util/strencodings.h"

#include "../structure/block/block.h"
#include "../persistence/IDAOBlockchain.h"
#include "../persistence/DAOBlockchain.h"
#include "../persistence/DAOException.h"
#include "../core/ConfiguratorSingleton.h"


using namespace spyCBlock;

/**
 * This battery of tests was developed first to test the parser evolution over time,
 * all functions are tested from the parsing of a simple data
 * to the paring of the whole block folder with a parser that was created only at test purpose.
 * Look at the DAOBlockchain.cpp file in persistence to get more information about him
 * @author https://github.com/vincenzopalazzo
 */


//Simple test for decode Genesis block and print ToString of the block in the Log
TEST(StructureBitcoinCoreTest, test_function_to_string)
{
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_logtostderr = false;

    /* "-------- BLOCK --------- \n"
         "Magic Numbar: d9b4bef9\n"
         "Block Size: 285\n"
         "---------- Block Header ---------- \n"
         "Version: 1\n"
         "Previous Block Header Hash: 0000000000000000000000000000000000000000000000000000000000000000\n"
         "Merkle Root: 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n"
         "Time: 2009-01-03 18:15:05\n"
         "nBits: 486604799\n"
         "Nonce: 2083236893\n"
         "Numbar Raw Transaction: 1\n"
         "---------- Raw Transaction ----------\n"
         "Version: 1\n"
         "---------- Transaction Input ----------\n"
         "Number Transaction In: 1\n"
         "Hash public key sender: 0000000000000000000000000000000000000000000000000000000000000000\n"
         "N: 4294967295\n"
         "Length script: 77\n"
         "Script: EThe Times 03/Jan/2009 Chancellor on brink of second bailout for banks\n"
         "Sequences: 4294967295\n"
         "---------- Transaction Output ----------\n"
         "Number Transaction out: 1\n"
         "N Value: 5000000000 satoshi\n"
         "Length script: 67\n"
         "Script: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"
         "0";*/
    string path = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/" + "bitcoin/block/blk00000.dat";
    ifstream stream(path);
    Block block;
    block.decode(stream);
    stream.close();
    LOG(WARNING) << block.toString();
}

//Simple test for import the uint256 bitcoin core
TEST(StructureBitcoinCoreTest, type_uint256_test_block_header)
{
    uint256 priviusBlockHas = uint256();
    priviusBlockHas.SetHex("0000000000004df94b4488e034359e862725dc969c498b9678dc261c58a679dc");
    uint256 merkle_root = uint256();
    merkle_root.SetHex("2b12fcf1b09288fcaff797d71e950e71ae42b91e8bdb2304758dfcffc2b620e3");
    BlockHeader blockHeader(01000000, priviusBlockHas, merkle_root, '6c8cb4d', 'b3936a1a', 'e3143991');
    EXPECT_EQ(blockHeader.getMerkleRoot().GetHex(), "2b12fcf1b09288fcaff797d71e950e71ae42b91e8bdb2304758dfcffc2b620e3");
    EXPECT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(), "0000000000004df94b4488e034359e862725dc969c498b9678dc261c58a679dc");
}

//Simple test for import the Outpoint bitcoin core
TEST(StructureBitcoinCoreTest, type_out_point_tx_in_test)
{
    TransactionInput tx;
    OutPoint outPoint;
    uint256 tx_in_hash;
    tx_in_hash.SetHex("f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16");
    outPoint.setHash(tx_in_hash);
    tx.setOutpoint(outPoint);
    EXPECT_EQ(tx.getOutpoint().getHash().GetHex(), "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16");
}

//Simple test for import the library serealize.h bitcoin core
TEST(StructureBitcoinCoreTest, serialize_test_int)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";

    std::ofstream fileIn(pathRoot + "file_bit_uno.dat");

    int value_in = 32;
    Serialize(fileIn, value_in);

    fileIn.close();

    std::ifstream fileOut(pathRoot + "file_bit_uno.dat");

    int value;
    Unserialize(fileOut, value);

    fileOut.close();

    EXPECT_EQ(value, 32);
}

//First test for decode a gesesis block with the structure of the SpyCBlock
/*
   The real date of blockchain first block read in the blk0000.dat
Magic No: 	d9b4bef9
Blocksize: 	285
########## Block Header ##########
Version:	 1
Previous Hash	 0000000000000000000000000000000000000000000000000000000000000000
Merkle Root	 4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b
millisecond time	 1231006505
Time stamp	 2009-01-03 18:15:05.000000+00:00 (UTC)
Difficulty	 486604799
Nonce		 2083236893
##### Tx Count: 1

Tx Version:	 1
Inputs:		 1
	Coinbase Text:	 0000000000000000000000000000000000000000000000000000000000000000
	Tx Out Index:	 ffffffff Coinbase with special index
	Script Length:	 77
	Sequence:	 ffffffff
Outputs:	 1
	Value:		 5000000000 Satoshi
	Script Len:	 67
	OP_CODE %d is probably obselete pay to address
	Pubkey OP_CODE:	 None Bytes:65 tail_op_code:OP_CHECKSIG
	Pure Pubkey:	   04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
	ScriptPubkey:	 4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac
Lock Time:	 0

  */
TEST(StructureBitcoinCoreTest, unserialize_one_block)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, pathLogRoot.append("unserialize_block_test.log").c_str());

    Block block;

    std::ifstream fileOut(pathMockRoot + "bitcoin/block/blk00000.dat");

    block.decode(fileOut);
    fileOut.close();

    EXPECT_EQ(block.getMagicNum(), spyCBlock::typeBlock::NETWORK_MAIN); //This is equal to "d9b4bef9"
    EXPECT_EQ(block.getBlocksize(), 285);
    EXPECT_EQ(block.getNumbarRawTransaction().getValue(), 1);

    BlockHeader blockHeader = block.getBlockHeader();

    EXPECT_EQ(blockHeader.getVersion(), 1);
    EXPECT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(blockHeader.getMerkleRoot().GetHex(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");
    EXPECT_EQ(blockHeader.getTime(), 1231006505);
    EXPECT_EQ(blockHeader.getNBits(), 486604799);
    EXPECT_EQ(blockHeader.getNonce(), 2083236893);

    //RawTransaction rawTransaction = block->getRawTransactions().at(0);

    EXPECT_EQ(block.getRawTransactions().at(0).getVersion(), 1);
    EXPECT_EQ(block.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);

    //Transaction Input
    //TransactionInput transactionInput = block->getRawTransactions().at(0)->getTxInd().at(0)->;

    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(),"0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN(), 4294967295); // 4294967295 equival at 0xffffff
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue(), 77);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptString().size(), 77);
    string data = "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73";
                 //04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript()
              .getRawScriptString()
              .substr(0,
                       block.getRawTransactions().at(0).getTxIn().at(0)
                            .getScript().getScriptLenght().getValue() * 2), data);

    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).decodeIntoStringScriptSing(), data);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getSequences(), 4294967295);

    //Transaction Output
    EXPECT_EQ(block.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    //TransactionOutput transactionOutput = rawTransaction.getTxOut().at(0);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getNValue(), 5000000000);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght().getValue(), 67);
    //TODO the pure script not calculate with the substr(0, (transactionOutput.getScript().getScriptLenght().getValue()) * 2)
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getScript()
              .getRawScriptString().substr(0,
                                           (block.getRawTransactions().at(0).getTxOut().at(0)
                                                 .getScript().getScriptLenght().getValue()) * 2),
              "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac");
    //TODO this lengh scritp contains the value opt code and this is wrong, wich I have minus two
             //4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac68c39c059c6100
    //Testing a pure script
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0)
              .getScript().getRawScriptString().substr(2, (block.getRawTransactions().at(0)
                                                                .getTxOut().at(0).getScript().getScriptLenght().getValue() - 2) * 2),
              "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
             //04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5facac
    EXPECT_EQ(block.getRawTransactions().at(0).getLockTime(), 0);

}

//Second test for decode a gesesis block and succesive block with the structure of the SpyCBlock
TEST(StructureBitcoinCoreTest, unserialize_two_block)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string localPathRoot = pathLogRoot;

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::ERROR, localPathRoot.append("unserialize_block_test.log").c_str());

    Block block;

    std::ifstream fileOut(pathMockRoot + "/bitcoin/block/blk00000.dat");
    block.decode(fileOut);

    EXPECT_EQ(block.getMagicNum(), spyCBlock::typeBlock::NETWORK_MAIN);
    EXPECT_EQ(block.getBlocksize(), 285);
    EXPECT_EQ(block.getNumbarRawTransaction().getValue(), 1);

    BlockHeader blockHeader = block.getBlockHeader();

    EXPECT_EQ(blockHeader.getVersion(), 1);
    EXPECT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(),
              "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(blockHeader.getMerkleRoot().GetHex(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");
    EXPECT_EQ(blockHeader.getTime(), 1231006505);
    EXPECT_EQ(blockHeader.getNBits(), 486604799);
    EXPECT_EQ(blockHeader.getNonce(), 2083236893);

    //RawTransaction rawTransaction = block->getRawTransactions().at(0);

    EXPECT_EQ(block.getRawTransactions().at(0).getVersion(), 1);
    EXPECT_EQ(block.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().size(), 1);

    //Transaction Input
    //TransactionInput transactionInput = block->getRawTransactions().at(0)->getTxInd().at(0)->;
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(),
              "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN(), 4294967295);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue(), 77);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getSequences(), 4294967295);

    //Transaction Output
    EXPECT_EQ(block.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().size(), 1);

    //TransactionOutput transactionOutput = block->getRawTransactions().at(0)->getTxOut().at(0)->;
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getNValue(), 5000000000);
    EXPECT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght().getValue(), 67);
    EXPECT_EQ(block.getRawTransactions().at(0).getLockTime(), 0);

    Block block_two;

    block_two.decode(fileOut);
    fileOut.close();

    EXPECT_EQ(block_two.getMagicNum(), spyCBlock::typeBlock::NETWORK_MAIN);
    EXPECT_EQ(block_two.getBlocksize(), 215);


    blockHeader = block_two.getBlockHeader();

    EXPECT_EQ(blockHeader.getVersion(), 1);
    EXPECT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(),
              "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");
    EXPECT_EQ(blockHeader.getMerkleRoot().GetHex(), "0e3e2357e806b6cdb1f70b54c3a3a17b6714ee1f0e68bebb44a74b1efd512098");
    EXPECT_EQ(blockHeader.getTime(), 1231469665);
    EXPECT_EQ(blockHeader.getNBits(), 486604799);
    EXPECT_EQ(blockHeader.getNonce(), 2573394689);

    EXPECT_EQ(block_two.getNumbarRawTransaction().getValue(), 1);

    //rawTransaction = block_two->getRawTransactions().at(0)->;

    EXPECT_EQ(block_two.getRawTransactions().at(0).getVersion(), 1);
    EXPECT_EQ(block_two.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);

    //Transaction Input
    //transactionInput = block_two->getRawTransactions().at(0)->getTxInd().at(0)->;
    EXPECT_EQ(block_two.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(),
              "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(block_two.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN(), 4294967295);
    EXPECT_EQ(block_two.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue(), 7);
    EXPECT_EQ(block_two.getRawTransactions().at(0).getTxIn().at(0).getSequences(), 4294967295);

    //Transaction Output
    EXPECT_EQ(block_two.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    //transactionOutput = block_two->getRawTransactions().at(0)->getTxInd().at(0)->getTxOut().at(0);
    EXPECT_EQ(block_two.getRawTransactions().at(0).getTxOut().at(0).getNValue(), 5000000000);
    EXPECT_EQ(block_two.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght().getValue(), 67);
    EXPECT_EQ(block_two.getRawTransactions().at(0).getLockTime(), 0);
}

//First test for decode all file blk
TEST(StructureBitcoinCoreTest, all_Read_file_dat)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string localPathRoot = pathLogRoot;

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, localPathRoot.append("all_Read_file_dat_test_first.log").c_str());

    ifstream stream(pathMockRoot + "bitcoin/block/blk00000.dat");
    ofstream outStream(pathMockRoot + "file_test_readl_all_file_dat_uno.txt");

    vector<Block> blocks;
    try
    {
        if (stream.is_open())
          {
            LOG(INFO) << "Stream is open";
            int numbarBlock = 0;

            while (!stream.eof()) {

                Block block;
                block.decode(stream);
                if(block.getBlockHeader().getVersion() == 0)//TODO dare un occhiata qui qualcosa non va con i numeri di blocchi
                {
                    LOG(WARNING) << "block is null -> " << block.getBlockHeader().getPreviousBlockHeaderHash().GetHex();
                }else{
                    outStream << block.toString();
                    numbarBlock++;
                    blocks.emplace_back(block);
                    LOG(INFO) << "Numbar block read now " << numbarBlock;
                }
            }
            EXPECT_EQ(blocks.size(), 119973); //TODO qualcosa alla fine del blocco fa i capricci sono in realtà 19973
        } else{
            FAIL() << "File not open blk00000.dat";
        }
    }
    catch (out_of_range oe) {
        LOG(FATAL) << "Exception generet: " << oe.what();
        FAIL();
    }
    catch (ifstream::failure fe) {
        LOG(FATAL) << "Exception generet: " << fe.what();
        FAIL();
    }
    LOG(WARNING) << "Memory occuped for list block readed " << (blocks.capacity() * sizeof(Block)) + blocks.size();

    stream.close();
    outStream.close();

}/*Test Read all file dat error numbar file read*/

//First test compare hash previus block whit the previus block generated another parser
TEST(StructureBitcoinCoreTest, compare_previus_block_hash)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string localPathRoot = pathLogRoot;

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_WARNING, localPathRoot.append("compare_previus_block_hash.log").c_str());

    ifstream *fileWhitHash = new ifstream(pathMockRoot + "previus_hash_block_header.txt");

    vector<string> *priviusHashs = new vector<string>();
    if(!fileWhitHash->is_open())
    {
        FAIL() << "File previus_hash_block_header.txt not open";
    }
    while (!fileWhitHash->eof()) {
        string readLine;
        *fileWhitHash >> readLine;
        LOG(INFO) << "I have read " << readLine;
        if(readLine != ""){
            priviusHashs->push_back(readLine);
        } else{
            LOG(WARNING) << "Line empty";
        }

    }
    fileWhitHash->close();
    LOG(INFO) << "Hashs readted: " << priviusHashs->size();
    ASSERT_EQ(priviusHashs->size(), 119972);

    fileWhitHash->close();

    delete fileWhitHash;

    ifstream *fileBlk = new ifstream(pathMockRoot + "/bitcoin/block/blk00000.dat");

    LOG_IF(FATAL, !fileBlk->is_open()) << "File: blk00000 not open";
    int coutBlockRead = 0;
    try {
        while(!fileBlk->eof() && coutBlockRead < priviusHashs->size())
        {
            Block *blockTested = new Block();
            blockTested->decode(*fileBlk);
            LOG(INFO) << "Block hash previus readed " << blockTested->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
            LOG(INFO) << "Block hash previus awaited " << priviusHashs->at(coutBlockRead);
            ASSERT_EQ(blockTested->getBlockHeader().getPreviousBlockHeaderHash().GetHex(),  priviusHashs->at(coutBlockRead)) << "Assertion fail at: " << coutBlockRead;
            coutBlockRead++;
            delete blockTested;
        }
    }
    catch (out_of_range ore)
    {
        LOG(FATAL) << "Exception generated: " << ore.what();
        FAIL() << "Exception generated: " << ore.what();
    }
    EXPECT_EQ(coutBlockRead, 119972);

    fileBlk->close();

    delete priviusHashs;
    delete fileBlk;
}

//First test compare hash previus block whit the previus block generated another parser
TEST(StructureBitcoinCoreTest, read_first_block_another_file_blk)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";
    string localPathRoot = pathLogRoot;

    FLAGS_logtostderr = false;
    FLAGS_minloglevel = 1;
    google::SetLogDestination(google::WARNING, localPathRoot.append("read_first_block_another_file_blk.log").c_str());

    //Init data for start this test
    ifstream stream(pathMockRoot + "bitcoin/block/blk00450.dat");

    Block block;
    block.decode(stream);

    stream.close();

    //Init assertion on blockRead

    /* ------ TEST BLOCK -----*/
    ASSERT_EQ(block.getMagicNum(), spyCBlock::typeBlock::NETWORK_MAIN);
    ASSERT_EQ(block.getBlocksize(), 934444);

    /* ------ TEST BLOCK HEADER-----*/
    BlockHeader blockHeader = block.getBlockHeader();
    ASSERT_EQ(blockHeader.getVersion(), 4);
    ASSERT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(), "0000000000000000037cc15769f72a8c7ea600975439e5a75f0c52534a4034ce");
    ASSERT_EQ(blockHeader.getMerkleRoot().GetHex(), "fdd92740f2472da1be5359a0006205f900ec1ecafea8a37fe2ebccc0d4dab963");
    ASSERT_EQ(blockHeader.getTime(), 1456115552);
    ASSERT_EQ(blockHeader.getNBits(), 403093919);
    ASSERT_EQ(blockHeader.getNonce(), 261426184);

    /* ----------- TEST RAW TRANSACTION -------------*/
    ASSERT_EQ(block.getNumbarRawTransaction().getValue(), 2461);
    ASSERT_EQ(block.getRawTransactions().size(), 2461);
    //RawTransaction rawTransaction = block->getRawTransactions().at(0);
    //unique_ptr<RawTransaction> rawTransaction = block->getRawTransactions().at(0);
    ASSERT_EQ(block.getRawTransactions().at(0).getVersion(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().size(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getLockTime(), 0);

    /* ----------- TEST IN TRANSACTION -------------*/
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);
    //TransactionInput transactionInput = rawTransaction.getTxInd().at(0);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN(), 4294967295); // 4294967295 equival ffffffff
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000000000");
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue(), 42);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getSequences(), 4294967295);

    /* ----------- TEST OUT TRANSACTION -------------*/
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxOut().size(), 1);
    //TransactionOutput transactionOutput = block->getRawTransactions().at(0)->getTxOut().at(0);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght().getValue(), 25);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getNValue(), 2549850141); // satoshi
}

//Second test for decode a two consecutive block into file blk with the structure of the SpyCBlock
TEST(StructureBitcoinCoreTest, read_two_consecutive_block_another_file_blk)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    string localPathRoot = pathLogRoot;

    FLAGS_logtostderr = false;
    FLAGS_minloglevel = 2;
    google::SetLogDestination(google::ERROR, localPathRoot.append("read_two_consecutive_block_another_file_blk.log").c_str());

    ifstream stream(pathMockRoot + "bitcoin/block/blk00450.dat");

    Block block;
    block.decode(stream);


    /* ------ TEST BLOCK -----*/
    ASSERT_EQ(block.getMagicNum(), spyCBlock::typeBlock::NETWORK_MAIN);
    ASSERT_EQ(block.getBlocksize(), 934444);

    /* ------ TEST BLOCK HEADER-----*/
    BlockHeader blockHeader = block.getBlockHeader();

    ASSERT_EQ(blockHeader.getVersion(), 4);
    ASSERT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(), "0000000000000000037cc15769f72a8c7ea600975439e5a75f0c52534a4034ce");
    ASSERT_EQ(blockHeader.getMerkleRoot().GetHex(), "fdd92740f2472da1be5359a0006205f900ec1ecafea8a37fe2ebccc0d4dab963");
    ASSERT_EQ(blockHeader.getTime(), 1456115552);
    ASSERT_EQ(blockHeader.getNBits(), 403093919);
    ASSERT_EQ(blockHeader.getNonce(), 261426184);

    /* ----------- TEST RAW TRANSACTION -------------*/
    ASSERT_EQ(block.getNumbarRawTransaction().getValue(), 2461);
    ASSERT_EQ(block.getRawTransactions().size(), 2461);

    //RawTransaction rawTransaction = block->getRawTransactions().at(0);

    ASSERT_EQ(block.getRawTransactions().at(0).getVersion(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().size(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getLockTime(), 0);

    /* ----------- TEST IN TRANSACTION -------------*/
    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);

    //TransactionInput transactionInput = block->getRawTransactions().at(0)->getTxInd().at(0)->;

    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN(), 4294967295); // 4294967295 equival ffffffff
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000000000");
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue(), 42);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxIn().at(0).getSequences(), 4294967295);

    /* ----------- TEST OUT TRANSACTION -------------*/

    ASSERT_EQ(block.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxOut().size(), 1);

    //TransactionOutput transactionOutput = rawTransaction.getTxOut().at(0);

    ASSERT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght().getValue(), 25);
    ASSERT_EQ(block.getRawTransactions().at(0).getTxOut().at(0).getNValue(), 2549850141); // satoshiBlock *block = new Block();

    /* ----------| SECOND BLOCK |---------- */

    Block blockTwo ;
    blockTwo.decode(stream);

    //Init assertion on blockRead

    /* ------ TEST BLOCK -----*/
    ASSERT_EQ(blockTwo.getMagicNum(), spyCBlock::typeBlock::NETWORK_MAIN);
    ASSERT_EQ(blockTwo.getBlocksize(), 934026);

    /* ------ TEST BLOCK HEADER-----*/
    BlockHeader blockHeaderTwo = blockTwo.getBlockHeader();

    ASSERT_EQ(blockHeaderTwo.getVersion(), 4);
    ASSERT_EQ(blockHeaderTwo.getPreviousBlockHeaderHash().GetHex(), "000000000000000005f63eb7767a8272bde8ea61578c0843e29636cd8e801027");
    ASSERT_EQ(blockHeaderTwo.getMerkleRoot().GetHex(), "e5d3ee60c360e9ed65f25eb0c45a2df37c73a79f233ca74fbd85722994e28c85");
    ASSERT_EQ(blockHeaderTwo.getTime(), 1456009607);
    ASSERT_EQ(blockHeaderTwo.getNBits(), 403093919);
    ASSERT_EQ(blockHeaderTwo.getNonce(), 2516415794);

    /* ----------- TEST RAW TRANSACTION -------------*/
    ASSERT_EQ(blockTwo.getNumbarRawTransaction().getValue(), 2237);
    ASSERT_EQ(blockTwo.getRawTransactions().size(), 2237);

    //RawTransaction rawTransactionTwo = blockTwo->getNumbarRawTransaction().at(0->);

    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getVersion(), 1);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxIn().size(), 1);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getLockTime(), 0);

    /* ----------- TEST IN TRANSACTION -------------*/
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getNumberTxIn().getValue(), 1);

    //TransactionInput transactionInputTwo = blockTwo->getRawTransactions().at(0)->getTxInd().at(0);

    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getN(), 4294967295); // 4294967295 equival ffffffff
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxIn().at(0).getOutpoint().getHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000000000");
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxIn().at(0).getScript().getScriptLenght().getValue(), 42);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxIn().at(0).getSequences(), 4294967295);

    /* ----------- TEST OUT TRANSACTION -------------*/
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getNumberTxOut().getValue(), 1);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxOut().size(), 1);

    //TransactionOutput transactionOutputTwo = blockTwo->getRawTransactions().at(0)->getTxOut().at(0);

    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxOut().at(0).getScript().getScriptLenght().getValue(), 25);
    ASSERT_EQ(blockTwo.getRawTransactions().at(0).getTxOut().at(0).getNValue(), 2542408827); // satoshi

    stream.close();
}

//First test than count the block contains into file blk
TEST(StructureBitcoinCoreTest, count_all_block_another_file_blk)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    string localPathRoot = pathLogRoot;

    FLAGS_logtostderr = false;
    FLAGS_minloglevel = 2;
    google::SetLogDestination(google::GLOG_ERROR, localPathRoot.append("count_all_block_another_file_blk.log").c_str());

    //Init data for start this test
    ifstream stream(pathMockRoot + "bitcoin/block/blk00450.dat");
    int count = 0;
    while(!stream.eof())
    {
        //Block *block = new Block();
        unique_ptr<Block> block(new Block());
        block->decode(stream);

        delete block.release();
        count++;
    }
    ASSERT_EQ(count, 155); // conta anche quello null

    stream.close();
}

//First test compare hash previus block whit the previus block generated another parser
TEST(StructureBitcoinCoreTest, compare_previus_second_block_hash)
{
    string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
    string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

    string localPathRoot = pathLogRoot;

    FLAGS_minloglevel = 2;
    FLAGS_logtostderr = false;
    google::SetLogDestination(google::GLOG_ERROR, localPathRoot.append("compare_previus_second_block_hash.log").c_str());

    ifstream fileWhitHash(pathMockRoot + "previus_hash_second_block_header.txt");

    vector<string> priviusHashs;
    if(!fileWhitHash.is_open())
    {
        FAIL() << "File previus_hash_block_header.txt not open";
    }
    while (!fileWhitHash.eof())
    {
        string readLine;
        fileWhitHash >> readLine;
        LOG(INFO) << "I have read " << readLine;
        if(readLine != "")
        {
            priviusHashs.push_back(readLine);
        }else{
            LOG(WARNING) << "Line empty";
        }

    }

    fileWhitHash.close();
    LOG(INFO) << "Hashs readted: " << priviusHashs.size();
    ASSERT_EQ(priviusHashs.size(), 154);

    fileWhitHash.close();

    ifstream fileBlk(pathMockRoot + "bitcoin/block/blk00450.dat");

    LOG_IF(FATAL, !fileBlk.is_open()) << "File: blk00450 not open";
    int coutBlockRead = 0;
    try
    {
        while(!fileBlk.eof() && coutBlockRead < priviusHashs.size())
        {
            Block *blockTested = new Block();
            blockTested->decode(fileBlk);

            LOG(INFO) << "Block hash previus readed " << blockTested->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
            LOG(INFO) << "Block hash previus awaited " << priviusHashs.at(coutBlockRead);

            ASSERT_EQ(blockTested->getBlockHeader().getPreviousBlockHeaderHash().GetHex(),  priviusHashs.at(coutBlockRead)) << "Assertion fail at: " << coutBlockRead;

            coutBlockRead++;
            delete blockTested;
        }
    }
    catch (out_of_range ore)
    {
        LOG(FATAL) << "Exception generated: " << ore.what();
        FAIL() << "Exception generated: " << ore.what();
    }
    EXPECT_EQ(coutBlockRead, 154);

    fileBlk.close();
}

//Fist test for create readed all file into directory block whit DAOBlockchain
//Look at the DAOBlockchain.cpp file in persistence to get more information about him
TEST(StructureBitcoinCoreTest, compare_previus_all_block_hash)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_minloglevel = 2;
  FLAGS_logtostderr = false;
  google::SetLogDestination(google::GLOG_ERROR,  localPathRoot.append("compare_previus_all_block_hash.log").c_str());

    unique_ptr<IDAOBlockchain> daoBlockchain(new DAOBlockchain());

    try
    {
            string path = pathMockRoot + "bitcoin/block";
            vector<unique_ptr<Block>> blocks = daoBlockchain->loadBlocks(path);
            ASSERT_EQ(120127, blocks.size());

            ifstream stream(pathMockRoot + "previus_hash_second_block_header.txt");

            LOG_IF(ERROR, !stream.is_open()) << "The file previus_hash_second_block_header.txt not opened";

            int numbarBlock = 0;

            while(!stream.eof())
            {
                  string previusBlockCalculate;
                  stream >> previusBlockCalculate;
                  if(!previusBlockCalculate.empty())
                  {
                     LOG(INFO) << "The previus block calculate is: " << previusBlockCalculate;
                     string previusBlockReaded = blocks.at(numbarBlock)->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
                     LOG(INFO) << "The previus block readed is: " << previusBlockCalculate;
                     ASSERT_EQ(previusBlockCalculate, previusBlockReaded) << " the hash block are different at the "  << numbarBlock << " numbars blocks";
                     numbarBlock++;
                  }
              }
            stream.close();

            ifstream streamTwo(pathMockRoot + "previus_hash_block_header.txt");

            LOG_IF(ERROR, !streamTwo.is_open()) << "The file previus_hash_block_header not is open";

            while(!streamTwo.eof())
            {
                string previusBlockCalculate;
                streamTwo >> previusBlockCalculate;
                if(!previusBlockCalculate.empty())
                  {
                    LOG(INFO) << "The previus block calculate is: " << previusBlockCalculate;
                    string previusBlockReaded = blocks.at(numbarBlock)->getBlockHeader().getPreviousBlockHeaderHash().GetHex();
                    LOG(INFO) << "The previus block readed is: " << previusBlockCalculate;
                    ASSERT_EQ(previusBlockCalculate, previusBlockReaded) << " the hash block are different at the "  << numbarBlock << " numbars blocks";
                    numbarBlock++;
                  }
              }
            streamTwo.close();
           }
    catch (DAOException daoException)
    {
        FAIL() << "The the fail for cause of this exception:  " << daoException.what();
    }
}

//FistTest for copare the type block network
TEST(StructureBitcoinCoreTest, compare_type_blocks_network)
{
  string pathMockRoot = ConfiguratorSingleton::getInstance().getPathFileMockTest() + "/";
  string pathLogRoot = ConfiguratorSingleton::getInstance().getPathFileLogTest() + "/";

  string localPathRoot = pathLogRoot;

  FLAGS_logtostderr = false;
  FLAGS_minloglevel = 2;
  google::SetLogDestination(google::GLOG_ERROR, localPathRoot.append("read_two_consecutive_block_another_file_blk.log").c_str());

  //Init data for start this test
  ifstream stream(pathMockRoot + "bitcoin/block/blk00450.dat");

  //Block *block = new Block();
  unique_ptr<Block> block(new Block());
  block->decode(stream);

  EXPECT_EQ(spyCBlock::typeBlock::NETWORK_MAIN, block->getMagicNum());

  stream.close();
}

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



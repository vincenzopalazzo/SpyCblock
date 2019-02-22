//
// Created by https://github.com/vincenzopalazzo on 1/22/19.
//
#include <fstream>
#include "gtest/gtest.h"
#include <glog/logging.h>
#include "../util/uint256.h"
#include "../structure/block/block.h"

using namespace spyCBlock;

//test metod toString
TEST(RunTest, test_function_to_string)
{
    string in;
    in = "-------- BLOCK --------- \n"
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
             "0";

    ifstream *stream = new ifstream("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    Block *block = new Block();
    block->decode(*stream);
    cout << block->toString();
}

/*Test new type uint256*/
TEST(RunTest, type_uint256_test_block_header)
{
    uint256 priviusBlockHas = uint256();
    priviusBlockHas.SetHex("0000000000004df94b4488e034359e862725dc969c498b9678dc261c58a679dc");
    uint256 merkle_root = uint256();
    merkle_root.SetHex("2b12fcf1b09288fcaff797d71e950e71ae42b91e8bdb2304758dfcffc2b620e3");
    BlockHeader *blockHeader = new BlockHeader(01000000, priviusBlockHas, merkle_root, '6c8cb4d', 'b3936a1a', 'e3143991');
    EXPECT_EQ(blockHeader->getMerkleRoot().GetHex(), "2b12fcf1b09288fcaff797d71e950e71ae42b91e8bdb2304758dfcffc2b620e3");
    EXPECT_EQ(blockHeader->getPreviousBlockHeaderHash().GetHex(), "0000000000004df94b4488e034359e862725dc969c498b9678dc261c58a679dc");
}
/*Test new type outpoint*/
TEST(RunTest, type_out_point_tx_in_test)
{
    TransactionInput *tx = new TransactionInput();
    OutPoint *outPoint = new OutPoint();
    uint256 *tx_in_hash = new uint256();
    tx_in_hash->SetHex("f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16");
    outPoint->setHash(*tx_in_hash);
    tx->setOutpoint(*outPoint);
    EXPECT_EQ(tx->getOutpoint().getHash().GetHex(), "f4184fc596403b9d638783cf57adfe4c75c605f6356fbc91338530e9831e9e16");
}

TEST(RunTest, serialize_test_int){
    std::ofstream fileIn ("test/file_test/file_bit_uno.dat");
    int value_in = 32;
    Serialize(fileIn, value_in);
    fileIn.close();

    std::ifstream fileOut ("test/file_test/file_bit_uno.dat");
    int value;
    Unserialize(fileOut, value);
    EXPECT_EQ(value, 32);
}

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
TEST(RunTest, unserialize_block)
{
    Block *block = new Block();

    std::ifstream fileOut ("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    block->decode(fileOut);
    std::stringstream hex_string;
    hex_string << std::hex << block->getMagicNum();
    EXPECT_EQ(hex_string.str(), "d9b4bef9");
    EXPECT_EQ(block->getBlocksize(), 285);

    EXPECT_EQ(block->getNumbarRawTransaction().getValue(), 1);
    BlockHeader blockHeader = block->getBlockHeader();
    EXPECT_EQ(blockHeader.getVersion(), 1);
    EXPECT_EQ(blockHeader.getPreviousBlockHeaderHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(blockHeader.getMerkleRoot().GetHex(), "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b");
    EXPECT_EQ(blockHeader.getTime(), 1231006505);
    EXPECT_EQ(blockHeader.getNBits(), 486604799);
    EXPECT_EQ(blockHeader.getNonce(), 2083236893);

    RawTransaction rawTransaction = block->getRawTransactions().at(0);
    EXPECT_EQ(rawTransaction.getVersion(), 1);
    EXPECT_EQ(rawTransaction.getNumberTxIn().getValue(), 1);

    //Transaction Input
    TransactionInput transactionInput = rawTransaction.getTxInd().at(0);
    EXPECT_EQ(transactionInput.getOutpoint().getHash().GetHex(), "0000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(transactionInput.getOutpoint().getN(), 4294967295);
    EXPECT_EQ(transactionInput.getScript().getScriptLenght().getValue(), 77);
    EXPECT_EQ(transactionInput.getSequences(), 4294967295);

    //Transaction Output
    EXPECT_EQ(rawTransaction.getNumberTxOut().getValue(), 1);
    TransactionOutput transactionOutput = rawTransaction.getTxOut().at(0);
    EXPECT_EQ(transactionOutput.getNValue(), 5000000000);
    EXPECT_EQ(transactionOutput.getScript().getScriptLenght().getValue(), 67);
    EXPECT_EQ(rawTransaction.getLockTime(), 0);

}

/*Test Read all file dat*/
TEST(RunTest, All_Read_file_dat){
    ifstream *stream = new ifstream("/home/vincenzo/tmp/bitcoin/block/blk00000.dat");
    ofstream *outStream = new ofstream("test/file_test/file_test_readl_all_file_dat_uno.dat");
    try {
        if(stream->is_open()){
            LOG(INFO) << "Stream is open";
            int numbarBlock = 0;
            while(!stream->eof()){
                Block *block = new Block();
                block->decode(*stream);
                *outStream << block->toString();
                //cout << block->toString();
                delete block;
                numbarBlock++;
                LOG(INFO) << "Numbar block read now " << numbarBlock;
            }
            EXPECT_EQ(numbarBlock, 256);
        }
    }catch (out_of_range e){
        LOG(FATAL) << "Exception generet: " << e.what();
        FAIL();
    }


}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}




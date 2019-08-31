# SpyCblock
[![Codacy Badge](https://img.shields.io/codacy/grade/13c697b9a6864ec8af152b5c7186bb3e.svg?style=for-the-badge)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=vincenzopalazzo/spyCblock&amp;utm_campaign=Badge_Grade)
![Build Status](https://img.shields.io/travis/com/vincenzopalazzo/SpyCblock.svg?style=for-the-badge)

A small parser for blk files of bitcoin core, this parser also calculates hashd ell transactions with which you can build a simple graph of transactions.

The transactions graph is serialized in the following way

The general form

```
txOringin|otherInformation|otherInformation|txArrival
```

An example

```
Coinbase|5000000000|4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b|1231006505|1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa
```
The parser offers a module for decrypting information in json, converts the entire structure to json, with a result of a blk.dat file inf a blk.json.

This is an example of decoding

```
{
  "hashBlock": "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f",
  "height": 0,
  "magicNumbar": -642466055,
  "blockSize": 285,
  "blockHeader": {
    "version": 1,
    "previusBlockHeaderHash": "0000000000000000000000000000000000000000000000000000000000000000",
    "markleRoot": "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b",
    "time": 1231006505,
    "nBits": 486604799,
    "nonce": 2083236893
  },
  "numbarRawTransactions": 1,
  "rawTransactions": [
    {
      "hashRawTransaction": "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b",
      "version": 1,
      "numbarTxInput": 1,
      "txInput": [
        {
          "hashInputTransaction": "f06a1dc939b97efd459de09236b426bcb61236280fd0cd1f869399cfd8d39aae",
          "outputTxHash": "0000000000000000000000000000000000000000000000000000000000000000",
          "ammount": 4294967295,
          "scriptLenght": 77,
          "script": "04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73",
          "sequences": 4294967295
        }
      ],
      "numbarTxOutput": 1,
      "txOutput": [
        {
          "hashOutputTransaction": "4c2224d8c6c869cf49805d1e4376fd7475b085e04b7ab75fc0d1afeb323a41be",
          "ammount": 5000000000,
          "scriptLenght": 67,
          "script": "4104678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5fac"
        }
      ],
      "lockTime": 0
    }
  ]
}
```

## License
![GitHub](https://img.shields.io/github/license/vincenzopalazzo/SpyCblock.svg?style=for-the-badge)

## Contributors
![GitHub contributors](https://img.shields.io/github/contributors/vincenzopalazzo/SpyCblock.svg?color=blue&style=for-the-badge)

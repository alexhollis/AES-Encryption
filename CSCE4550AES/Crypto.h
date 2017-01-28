/* 
 * File:   Crypto.h
 * Author: Alex Hollis
 *
 * Created on November 26, 2014, 1:35 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>



/*Change filenames here to desired files if needed, otherwise these defaults will apply.*/

#define OUTPUT "output.txt"
#define INPUT  "text.txt"
#define KEY    "key.txt"

/*Filenames*/



#ifndef CRYPTO_H
#define	CRYPTO_H

using namespace std;

class Block {
    unsigned char b[4][4]; // stores the letters
    bitset<8> x[4][4]; // stores letters in binary for later use.
    friend class List;
    void erase();

};

class List {
public:

    List() {
    };

    vector<Block> L;

    
    void encrypt(string); //pass key in main file.    [Vigenere Cipher ]
    int fillblocks();          //Fills blocks, returns length on text accepted.
    void padList(int);         //to be padded with 'A' to ensure blocks are all 4x4 and full.
    void shiftRows();       //shift rows according to AES.
    void parityBit();       //determine if parity bit needs to be toggled.
    void writeout(int, string); //pass flag to tell how to write output. ex: regular or hex
    void MixColumns();  //bit manipulations
    bitset<8> rgfMul(bitset<8>, int);     //multiply function (x,y)
};






#endif	/* CRYPTO_H */


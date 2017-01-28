/* 
 * File:   main.cpp
 * Author: Alex Hollis
 *
 * Created on November 26, 2014, 12:41 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Crypto.h"
#include <fstream>




using namespace std;

int main() {

    List la;
    string key;
    int len;
    ifstream k;
    k.open(KEY);
    char temp;
    while (k >> temp) {
        if (temp >= 'A' && temp <= 'Z') key += temp;
    }

    cout << "Starting Encryption on File..." << endl;



    len = la.fillblocks();
    la.writeout(1, key);



    la.encrypt(key);
    la.writeout(2, key);


    la.padList(len);
    la.writeout(3, key);

    la.shiftRows();
    la.writeout(4, key);

    la.parityBit();
    la.writeout(5, key);

    la.MixColumns();
    la.writeout(6, key);

    cout << "Encryption Complete, see output file for results." << endl;

    return 0;
}



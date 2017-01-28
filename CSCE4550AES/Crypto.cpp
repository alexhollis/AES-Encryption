#include "Crypto.h"
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;
//call the encryption function after filling blocks with elgible text from input file.

void List::encrypt(string key) {
    int len = key.length();
    int block = 0;
    int keyPos = 0;
    int i, j;
    int blockLen = L.size();
    if (blockLen == 0) return;
    unsigned char a, b, c;
    
    cout << "Enciphering text from input..." << endl;

    while (block < blockLen) {
        for (i = 0; i < 4; i++) // rows
        {
            for (j = 0; j < 4; j++) //cols
            {

                
                if(L[block].b[i][j] >= 'A' && L[block].b[i][j] <= 'Z')
                {
                    a = L[block].b[i][j];
                    b = key[keyPos];
                    c = ((a + b - 2 * 'A') % 26 + 'A');
                    L[block].b[i][j] = c;
                    keyPos = (keyPos + 1) % len;
                }
                

            }

        }
        block++;
    }
    cout << "Done!" << endl;
    return;
}
// call padding after encrypting input.

void List::padList(int length) // want to know how many characters were scanned in that met the specifications. (A-Z)
{
    int blocks = L.size();
    int rem = length % 16; //if zero, no partial blocks.
    int pBlock = blocks - 1;
    int row, col;
    
    if(rem > 0){ //calculate starting position in block
        
        cout << "Padding blocks of input..." << endl;
        
        /*
        if (rem >= 1 && rem < 4) {
            row = 0;

            col = (rem % 4) -1;



        }
        if (rem >= 4 && rem < 8) {
            row = 1;

            col = (rem % 4) -1;



        }
        if (rem >= 8 && rem < 12) {
            row = 2;

            col = (rem % 4) -1;



        }
        if (rem >= 12 && rem < 16) {
            row = 3;

            col = (rem % 4) -1;



        } */
        
        bool Loop = true;
        
        for(int x=0; x < 4 && Loop; x++)
            for(int y=0; y<4 && Loop; y++)
                if(L[pBlock].b[x][y] < 'A' || L[pBlock].b[x][y] > 'Z')
                {
                    row = x;
                    col = y;
                    Loop = false;
                    break;
                }
    
        bool once = false;
        
        for (int i = row; i < 4; i++) {

        for (int j = 0; j < 4; j++) {
            if(once == false)
            {
                j+=col;
                once = true;
            }
            L[pBlock].b[i][j] = 'A'; // fill empty spaces with As.

        }




    }

        
    

    cout << "Done!" << endl;
    
    }
    return;
}

void List::shiftRows() { // call after padding
    int blocks = L.size();
    int block = 0;
    unsigned char temp;
    int j, x;
    cout << "Shifting Rows of Blocks..." << endl;
    while (block < blocks) {
        for (int row = 1; row < 4; row++) {

            for (int i = 0; i < row; i++) {
                    for (j = 0; j < 3; j++) {
                    temp = L[block].b[row][j];
                    L[block].b[row][j] = L[block].b[row][j + 1];
                    L[block].b[row][j + 1] = temp;
                }
                

            }

        }

        block++;
    }
    cout << "Done!"<<endl;
}

void List::parityBit() { // call after shift rows

    int block = 0;
    int blocks = L.size();
    cout << "Adjusting Parity Bits if needed..."<<endl;
    while (block < blocks) {

        for (int row = 0; row < 4; row++) {

            for (int col = 0; col < 4; col++) {
                L[block].x[row][col] = L[block].b[row][col]; //set bits in 4x4 block equal to the character in the 

                if (L[block].x[row][col].count() % 2 > 0) L[block].x[row][col][7] = 1; //set parity bit to one to make even.

            }
        }
        block++;
    }
    cout << "Done!" << endl;
}

bitset<8> List::rgfMul(bitset<8> x, int y) {
    bitset<8> pad(string("00011011")); //used if MSB=1;
    bitset<8> result;
    if (y == 2) {
        if (x[7] == 1) // MSB =1
        {
            result = x << 1;
            result = result ^ pad;
        } else result = result << 1;


    } else // y=3
    {
        if (x[7] == 1) //MSB =1   
        {
            result = (x << 1) ^ x;
            result = result ^ pad;

        } else result = (x << 1) ^ x;


    }

    return result;

}

void List::MixColumns()
{
    int blocks = L.size();
    int block = 0;
    cout << "Mixing Columns of Blocks..." << endl;
    while(block < blocks)
    {
        
        for(int col = 0; col < 4; col++)
        {
          L[block].x[0][col]  = (rgfMul(L[block].x[0][col], 2)) ^ (rgfMul(L[block].x[1][col], 3)) ^ L[block].x[2][col] ^ L[block].x[3][col];
          L[block].x[1][col] =  L[block].x[0][col] ^ (rgfMul(L[block].x[1][col], 2)) ^ (rgfMul(L[block].x[2][col], 3)) ^ L[block].x[3][col];  
          L[block].x[2][col] =  L[block].x[0][col] ^ L[block].x[1][col] ^ (rgfMul(L[block].x[2][col], 2)) ^ (rgfMul(L[block].x[3][col], 3)); 
          L[block].x[3][col] =  (rgfMul(L[block].x[0][col], 3)) ^ L[block].x[1][col] ^ L[block].x[2][col] ^ (rgfMul(L[block].x[3][col], 2)); 
        }
        
        block++;
    }
    
    cout << "Done!" << endl;
    
    
    
}

void Block::erase()
{
    for(int i=0; i<4; i++)
        for(int j=0; j< 4; j++)
            b[i][j] = '\0';
    
    
}



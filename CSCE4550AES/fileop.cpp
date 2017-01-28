#include "Crypto.h"

void List::writeout(int step, string key) //step is what part of the program needs to be written out (step 1 = Input File, 2 = Encryption, etc...)
{
    ofstream writer;
    writer.open(OUTPUT, ios::app);

    switch (step) {
        case 1:
        {
            writer << "Starting AES Encryption...\r\n\r\n";
            writer << "Step 1: Input File:\r\n\r\n";
            writer << "Output Text: \r\n\r\n";
            int block = 0;
            int blocks = L.size();
            while (block < blocks) {
                for (int row = 0; row < 4; row++)
                    for (int col = 0; col < 4; col++)
                        writer << L[block].b[row][col];
                block++;

            }
            writer << "\r\n\r\n";
        }
            break;
        case 2:
        {

            writer << "Step 2: Encryption:\r\n\r\n";
            writer << "Key: " << key << "\r\n\r\n";
            writer << "Input Text: \r\n\r\n";
            int block = 0;
            int blocks = L.size();
            while (block < blocks) {
                for (int row = 0; row < 4; row++)
                    for (int col = 0; col < 4; col++)
                        writer << L[block].b[row][col];
                block++;

            }
            writer << "\r\n\r\n";
        }
            break;
        case 3:
        {
            writer << "Step 3: Padding:\r\n\r\n";
            writer << "Output:\r\n\r\n";
            int block = 0;
            int blocks = L.size();
            while (block < blocks) {
                for (int row = 0; row < 4; row++) {
                    for (int col = 0; col < 4; col++)
                        writer << L[block].b[row][col];
                    writer << "\r\n";
                }
                writer << "\r\n";
                block++;

            }
            writer << "\r\n\r\n";
        }
            break;
        case 4:
        {
            writer << "Step 4: Shift Rows:\r\n\r\n";
            writer << "Output:\r\n\r\n";
            int block = 0;
            int blocks = L.size();
            while (block < blocks) {
                for (int row = 0; row < 4; row++) {
                    for (int col = 0; col < 4; col++)
                        writer << L[block].b[row][col];
                    writer << "\r\n";
                }
                writer << "\r\n";
                block++;

            }
            writer << "\r\n\r\n";


        }
            break;
        case 5:
        {
            writer << "Step 5: Parity Bit:\r\n\r\n";
            writer << "Output (in hexadecimal):\r\n\r\n";
            int block = 0;
            int blocks = L.size();
            while (block < blocks) {
                for (int row = 0; row < 4; row++) {
                    for (int col = 0; col < 4; col++)
                        writer << hex << L[block].x[row][col].to_ulong() << " ";
                    writer << "\r\n";
                }

                block++;

            }
            writer << "\r\n\r\n";



        }
            break;
        case 6:
        {
            writer << "Step 6: MixColumns:\r\n\r\n";
            writer << "Output (in hexadecimal):\r\n\r\n";
            int block = 0;
            int blocks = L.size();
            while (block < blocks) {
                for (int row = 0; row < 4; row++) {
                    for (int col = 0; col < 4; col++)
                        writer << hex << L[block].x[row][col].to_ulong() << " ";
                    writer << "\r\n";
                }

                block++;

            }
            writer << "\r\n\r\n";



        }
            break;
    }

    writer.close();
}

int List::fillblocks() {
    ifstream scanner;
    scanner.open(INPUT);
    vector<unsigned char> buffer;
    unsigned char temp;
    cout << "extracting approved data from input file..." << endl;
    while (scanner >> temp) {
        if (temp >= 'A' && temp <= 'Z') buffer.push_back(temp);
    }

    Block T;
    int length = buffer.size();

    int i = 0;
    int row, col;

    while (i < length) {
        for (row = 0; row < 4 && i < length; row++) {
            for (col = 0; col < 4 && i < length; col++) {
                T.b[row][col] = buffer[i];
                i++;

            }
        }
      
        if(row == 4 && col == 4)
                L.push_back(T);

    }
    
    int rem = length % 16;
    bool once =false;
    for(int x = ( rem / 4); x < 4; x++)
        for(int y = 0; y< 4; y++)
        {
            if(once == false) 
            {
                y+= (rem % 4);
                once = true;
            }
            T.b[x][y] = ' ';
            
        }
        L.push_back(T);
    
    
    
    
    cout << "Done!" << endl;
    return length;

}


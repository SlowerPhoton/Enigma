/**
 * @mainpage Encryption algorithm DES
 *
 *
 * @version
 * 20/11/2015
 */


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h> // na co tu jsou?
#include <cmath>  // na co tu jsou?
#include <fstream>
#include <vector>

// #include "debug.h" UNNECESSARY
#include "typeConverter.h" // functions used for converting between different data types
#include "binary.h" // functions used to manipulate with binary data UNNECESSARY
#include "enOrDecrypt.h" // functions used to decide whether to encrypt or decrypt
#include "message.h" // functions used to get and prepare the message
#include "key.h" // functions used to get and prepare the key
#include "subkeys.h" // functions used to create subkeys from the key
#include "encodeMessage.h" // functions used to encode the message


using namespace std;

extern bool encr; // if true user wishes to encrypt UNNECESSARY

int main()
{
    enOrDecrypt();

    vector<unsigned char> message;
    getMessage(message);
    messageExpand(message);

    bool binaryMessage[message.size()*8];
    messageToBinary(binaryMessage, message);


    int key[8];
    getKey(key);

    bool binaryKey[8*8];
    toBinary(key, binaryKey, 8);

    /// Step 1: Create 16 subkeys, each of which is 48-bits long.
    bool subkeys[16][48];
    createSubkeys(binaryKey, subkeys);

    /// Step 2: Encode each 64-bit block of data.
    size_t length = message.size()*8;
    for(int i = 0; i < length; i+=64){
        bool C[64]; // to store the encrypted message
        encodeMessage(binaryMessage+i, subkeys, C);

        // couting the encrypted message
        for(int j = 0; j < 64; j+=8){
            cout << toDecimal(C+j, 8);
            cout << "\t";
        }
        cout << endl;

    }



    return 0;
}


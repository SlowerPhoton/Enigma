#include "message.h"
#include <iostream>
#include <vector>
#include <limits>

extern bool encr;

/*UNUSED*/
int getSizeOfMessage(){
    if(encr)
        std::cout << "Enter the number of characters in the message to encrypt: " << std::endl;
    else
        std::cout << "Enter the number of characters in the encrypted message: " << std::endl;
    int numbersInMessage;
    std::cin >> numbersInMessage;
    return numbersInMessage;
}

int padding(int numbersInMessage){
    return (8 - numbersInMessage%8)%8;
}

void getMessage(std::vector<unsigned char> &message){

    // reserve at least 256 bytes (that's reasonable)
    message.reserve(256);

    if(encr)
        std::cout << "Enter the message to encrypt (numbers in the range <0;255>, 0 will terminate your input): " << std::endl;
    else
        std::cout << "Enter the encrypted message (numbers in the range <0;255>, 0 will terminate your input): " << std::endl;

    // zero is the 'banned number' which will stop the process of obtaining the message (and the '0' will be ignored)
    int get = 1; // to store the user's input
    while(true){
        std::cout << "> ";
        std::cin >> get;

        // check whether the user entered a number
        if(std::cin.fail()) // or if(cin.fail())
        {
            std::cerr << "ERROR: You must enter an integer" << std::endl;

            // user didn't input a number
            std::cin.clear(); // reset failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            // next, request user reinput
            continue;
        }

        // if the user enters a number out of the range <0;255> make him repeat it
        if( !(get>=0 and get<=255) ){
            std::cerr << "ERROR: Must be in range <0;255>, try again" << std::endl;
            continue;
        }

        // end the while loop if 0 has been entered
        if(get == 0)
            break;

        // get is a valid number -> store it in the message
        message.push_back(get);
    }

}

void messageExpand(std::vector<unsigned char> &message){
    int numbersInMessage = message.size();
    int pad = padding(numbersInMessage);
    for(int i = numbersInMessage; i < pad + numbersInMessage; i++){
        message.push_back(0);
    }
}

void messageToBinary(bool binaryMessage[], std::vector<unsigned char> &message){

    unsigned char powOf2;
    size_t noOfNumbers = message.size();
    for(unsigned int i = 0; i < noOfNumbers; i++){
        bool tank[8] = {0,0,0,0,0,0,0,0};
        unsigned char toProcess = message[i];
        // 8 bits -> the biggest possible number (unsigned) is 255
        // the first position represents 128
        int n;
        for(powOf2 = 128, n=0; n<8; powOf2/=2, n++){
            if(powOf2 <= toProcess){
                toProcess -= powOf2;
                tank[n] = 1;
            }
        }

        // copy tank[] to the corresponding position in binaryMessage[]
        for(int j = 0; j < 8; j++)
            binaryMessage[i*8+j] = tank[j];
    }
}

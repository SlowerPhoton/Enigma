#include "enOrDecrypt.h"
#include <iostream>
#include <string.h>

/**
    stores whether the user wishes to encrypt ( @c true ) or decrypt ( @c false )
*/
bool encr;

void enOrDecrypt(){
    encr = false;
    std::cout << "Would you like to encrypt or decrypt? [E/D] ";
    char answer;
    std::cin >> answer;
    answer = toupper(answer);

    if(answer == 'E')
        encr = true;
}

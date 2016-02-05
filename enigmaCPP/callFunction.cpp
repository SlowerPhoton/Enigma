#include "callFunction.h"
#include "help.h"
#include "key.h"
#include "cin.h"
#include "encryption.h"
#include "plugboard.h"
#include "settings.h"
//#include <cstring>

#include <iostream>

void unrecognized(){
    std::cout << "Command unrecognized." << std::endl;
}

std::string trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

bool callFunction(std::string get, int scramblers[3+1][26], int shift[3], int rotor[3]){

    // make input string lower case
    for(size_t i = 0, n = get.length(); i < n; i++)
        get[i] = tolower(get[i]);

    if(get.compare("end") == 0)
        return false;
    if(get.compare("help") == 0)
        help();
    else if(get.compare("generate_key") == 0 or get.compare("gk") == 0)
        generateKey();
    else if(get.compare("generate_scrambler") == 0 or get.compare("gs") == 0)
        generateScrambler(scramblers);
    else if(get.compare("set_key") == 0 or get.compare("sk") == 0)
        setKey(scramblers);
    else if(get.compare("encrypt") == 0 or get.compare("e") == 0)
        encrypt(scramblers, shift, rotor);
    else if(get.compare("set_shift") == 0 or get.compare("ss") == 0)
        setShift(shift);
    else if(get.compare("set_rotor") == 0 or get.compare("sr") == 0)
        setRotor(rotor);
    else if(get.compare("reset_shift") == 0 or get.compare("rs") == 0)
        resetShift(shift);
    else if(get.compare("print_shift") == 0 or get.compare("ps") == 0)
        printShift(shift);
    else if(get.compare("print_rotor") == 0 or get.compare("pr") == 0)
        printRotor(rotor);
    else if(get.compare("encrypt_file") == 0 or get.compare("ef") == 0)
        encryptFile(scramblers, shift, rotor);
    else if(get.compare("capitalize") == 0 or get.compare("c") == 0)
        capitalize();
    else if(get.compare("set_plugboard") == 0 or get.compare("sp") == 0)
        setPlugboard();
    else if(get.compare("save") == 0 or get.compare("s") == 0)
        save(scramblers, shift, rotor);
    else if(get.compare("load") == 0 or get.compare("l") == 0)
        load(scramblers, shift, rotor);
    else
        unrecognized();


    return true;
}

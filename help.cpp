#include "help.h"

#include <iostream>

using namespace std;

void help()
{

    cout << "You are viewing a console application, designed to simulate the Enigma algorithm." << endl << endl;

    cout << "Available commands:" << endl;
    cout << "generate_key or gk\t generates the key (asks for a number to use for the random function's seed, if no number is provided it uses time(NULL) instead)" << endl << endl;
    cout << "generate_scrambler or gs\t generates a scrambler of chosen index (asks for a number to use for the random function's seed, if no number is provided it uses time(NULL) instead)" << endl << endl;
    cout << "set_key or sk\t uploads the key from a chosen file" << endl << endl;
    cout << "encrypt or e\t encrypts the given message" << endl << endl;
    cout << "encrypt_file or ef\t encrypts a chosen file and outputs it into another" << endl << endl;
    cout << "capitalize or c\t enables to change the capitalization of inputs" << endl << endl;
    cout << "reset_shift or rs\t resets the shift of rotors" << endl << endl;
    cout << "set_shift or ss\t sets shift of each rotor to a given value" << endl << endl;
    cout << "print_shift or ps\t prints the current values of shift" << endl << endl;
    cout << "set_plugboard or sp\t enables user to set the plugboard" << endl << endl;
    cout << "save or s\t saves the settings of scramblers, shift, rotor and plugboard to a chosen file" << endl << endl;
    cout << "load or l\t loads the settings of scramblers, shift, rotor and plugboard from a chosen file" << endl << endl;
    cout << "help \t prints all commands" << endl << endl;
    cout << "end \t ends the application" << endl << endl;
}

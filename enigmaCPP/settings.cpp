#include "settings.h"

#include <iostream>
#include <fstream>

extern int plugboard[26];
extern bool keySet;

using namespace std;

void save(int scramblers[3+1][26], int shift[3], int rotor[3]){

    // make sure key was set
    if (!keySet){
        cout << "Cannot save settings if there is no key set." << endl;
        return;
    }

    // get the name of the file
    cout << "Enter the name of the file to save the settings: ";
    string fileN;
    cin >> fileN;

    // create the output and make sure it is open
    ofstream output;
    output.open(fileN.c_str(), ios::binary | ios::out);
    if (output == NULL){
        cout << "File could not be opened/created. Process aborted." << endl;
        return;
    }

    // save scramblers
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 26; j++)
            output.write((char *) &scramblers[i][j], sizeof(int));

    // save shift
    for (int i = 0; i < 3; i++)
        output.write((char *) &shift[i], sizeof(int));

    // save rotor
    for (int i = 0; i < 3; i++)
        output.write((char *) &rotor[i], sizeof(int));

    // save plugboard
    for (int i = 0; i < 26; i++)
        output.write((char *) &plugboard[i], sizeof(int));

    output.close();
}

void load(int scramblers[3+1][26], int shift[3], int rotor[3]){

    // get the name of the file
    cout << "Enter the name of the file to load the settings from: ";
    string fileN;
    cin >> fileN;

    // create the output and make sure it is open
    ifstream input;
    input.open(fileN.c_str(), ios::binary | ios::in);
    if (input == NULL){
        cout << "File could not be opened. Process aborted." << endl;
        return;
    }

    // check file size
    input.seekg(0, ios::end);
    size_t filesize = input.tellg();
    input.seekg(0);
    if (filesize != 544){
        cout << "File is probably corrupted. Process aborted." << endl;
        return;
    }

    // upload scramblers
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 26; j++)
            input.read((char *) &scramblers[i][j], sizeof(int));

    // upload shift
    for (int i = 0; i < 3; i++)
        input.read((char *) &shift[i], sizeof(int));

    // upload rotor
    for (int i = 0; i < 3; i++)
        input.read((char *) &rotor[i], sizeof(int));

    // upload plugboard
    for (int i = 0; i < 26; i++)
        input.read((char *) &plugboard[i], sizeof(int));

    keySet = true;
    input.close();
}

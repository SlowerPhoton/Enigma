#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>

#include "callFunction.h"
#include "cin.h"
#include "plugboard.h"

#define SCRAMBLERS 3

using namespace std;

/* used to remember whether the key was set already */
bool keySet = false;

int main()
{
    /* represents the settings of scramblers, the last index represents the settings of the reflector */
    int scramblers[3 + 1][26];

    /* used to save the shift of scramblers */
    int shift[3] = {0, 0, 0};

    /* used to save the initial shift of rotors */
    int rotor[3] = {0, 0, 0};

    /* reset plugboard to prevent it from containing garbage values */
    resetPlugboard();

    cout << "Type 'help' to find out what this is." << endl << endl;

    bool cont; // to determine whether to continue looping
    string get;
    do {
        cout << "> ";
        cin >> get;
        clearBuffer();

        cont = callFunction(get, scramblers, shift, rotor);

    }
    while(cont);

    return 0;
}

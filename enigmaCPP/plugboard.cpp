#include "plugboard.h"
#include "cin.h"
#include "callFunction.h"

#include <iostream>

/**
 * each index represents a letter of the English alphabet
 * if the letter is not 'plugged' there is 0 in its index /* TO UPDATE
 * if it is there is its new value
 *
 */
int plugboard[26];

using namespace std;

void resetPlugboard()
{
    for(int i = 0; i < 26; i++)
        plugboard[i] = i;
}

void unplug(size_t a)
{
    size_t letterA = plugboard[a];
    plugboard[letterA] = letterA;
    plugboard[a] = a;
}

void printPairs(){

    int bannedI[14];
    for(size_t i = 0; i < 14; i++)
        bannedI[i] = -1;
    size_t ind = 0;
    for(size_t i = 0; i < 26; i++){

        for(size_t a = 0; a < ind; a++) // to print one pair just once
            if(bannedI[a] == i){
                a = 0;
                i++;
                if (i >= 26)
                    return;
            }

        if (plugboard[i] != i){
            bannedI[ind] = plugboard[i];
            ind++;
            cout << '\t' << (char) (i + 'A') << " and " << (char) (plugboard[i] + 'A') << endl;
        }
    }

    if (ind == 0)
        cout << "set_plugboard> Nothing to be printed." << endl;
}

void helpPlugboard(){
    cout << "To reset previous plugboard settings, type 'reset'." << endl;
    cout << "To plug two letter together, type letterA + space + letterB." << endl;
    cout << "Example: 'R Q' or 'r q'." << endl;
    cout << "To unplug a pair of letters type 'unplug'/'up' + space + one of them." << endl;
    cout << "Example to unplug A <-> G: 'up G' or 'unplug a'." << endl;
    cout << "To see all currently plugged letters type 'print'." << endl;
    cout << "To escape type 'return'." << endl << endl;
}

void setPlugboard()
{

    helpPlugboard();

    string get;
    do
    {

        cout << "set_plugboard> ";
        getline(cin, get);

        // trim spaces from left and right
        get = trim(get);

        // make the input lower case
        for(size_t i = 0, n = get.length(); i < n; i++)
            get[i] = tolower(get[i]);

        if(get.compare("reset") == 0)
        {
            resetPlugboard();
            continue;
        }

        if(get.compare("print") == 0)
        {
            printPairs();
            continue;
        }

        if(get.length() == 8 and get.compare(0, 6, "unplug") == 0 and get[6] == ' ' and get[7] <= 'z' and get [7] >= 'a')
        {
            unplug(get[7] - 'a');
            continue;
        }

        if(get.length() == 4 and get[0] == 'u' and get[1] == 'p' and get[2] == ' ' and get[3]<='z' and get[3]>='a') // if it has the correct format for unplugging
        {
            unplug(get[3] - 'a');
            continue;
        }

        if(get.length() == 3)  // if the input is 3 characters long
        {

            if(get[0]>'z' or get[0]<'a' or get[1]!=' ' or get[2]>'z' or get[2]<'a')  // if it doesn't have the correct format for plugging
            {
                cout << "set_plugboard> Command unrecognized." << endl;
                continue;
            }
            size_t letterA = get[0] - 'a';
            size_t letterB = get[2] - 'a';

            if (plugboard[letterA] != letterA) // if letterA is already paired (plugged)
            {
                cout << "set_plugboard> " << (char) (letterA + 'A') << " is plugged already. Unplug it first." << endl;
                continue;
            }
            if (plugboard[letterB] != letterB) // if letterB is already paired (plugged)
            {
                cout << "set_plugboard> " << (char) (letterB + 'A') << " is plugged already. Unplug it first." << endl;
                continue;
            }

            plugboard[letterA] = letterB;
            plugboard[letterB] = letterA;
            continue;
        }

        if (get.compare("return") == 0){
            cout << endl;
            return;
        }

        cout << "set_plugboard> " << "Command unrecognized." << endl;

    }
    while(true);

}

int afterPlug(char a){
    return plugboard[a];
}

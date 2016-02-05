#include "encryption.h"
#include "cin.h"
#include "plugboard.h"

#include <iostream>
#include <cstdio>
#include <string.h>
#include <fstream>


extern bool keySet;
// if true, capitalize all input text characters
bool capI = true;
// if true, capitalize all input file characters
bool capF = false;

using namespace std;

void encrypt(int scramblers[3+1][26], int shift[3], int rotor[3])
{

    // check whether the key was set
    if (keySet == false)
    {
        cout << "There is no key to encrypt with." << endl;
        return;
    }

    // fill the openText
    cout << "Enter a message to encrypt: " << endl;
    string openText;
    getline(cin, openText);

    // to save the encrypted text
    string encrypted;

    // for each character of openText cypher
    for (int i = 0, n = openText.length(); i < n; i++)
    {

        // make the current character of openText upper and save it to c
        int c = openText[i];
        bool isLow = islower(c);
        c = toupper(c);

        // if the character is a letter otherwise do not change it and do not shift scramblers
        if (c >= 'A' and c <= 'Z')
        {

            // shift ('rotate') scramblers
            shift[0]++;
            if (shift[0] == 26)
            {
                shift[1]++;
                shift[0] = 0;

                if (shift[1] == 26)
                {
                    shift[2]++;
                    shift[1] = 0;

                    if (shift[2] == 26)
                    {
                        shift[2] = 0;
                    }
                }
            }


            // turn c into number - how far it is from 'A' in ASCII
            c = c - 'A';

            // corresponding to the plugboard
            c = afterPlug(c);

            /*
               c now need to get through all 3 scramblers
               'reflect' from the reflector
               and go back through all the 3 scramblers again
            */
            // the trip to the reflector
            for (int j = 0; j < 3; j++)
            {

                // encrypt the letter according to the key in the j-th srambler
                if (c + shift[j] + rotor[j] >= 26)
                {
                    // add shift to the number (made from the letter currently being encrypted), find it in the key in the current scrambler, change it according to it and subtract shift
                    c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                }
                else
                    c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                // if c is after subtracting shift less then 0 add 26 to return it back through 'Z'
                if (c < 0)
                    c += 26;

            }

            // encrypt through the reflector
            c = scramblers[3][c];

            // the way back
            for (int j = 2; j >= 0; j--)
            {
                if (c + shift[j] + rotor[j] >= 26)
                {
                    c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                }
                else
                    c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                if (c < 0)
                    c += 26;

            }

            // turn c back into a letter
            c = afterPlug(c);
            if (!capI and isLow)
                c += 'a';
            else
                c += 'A';
        }


        // print the (possibly) encrypted character
        encrypted += (char) c;
    }
    encrypted += '\0';

    // output the encrypted text
    cout << encrypted << endl;
}

void printShift(int shift[3])
{
    cout << '\t';
    for(int i = 0; i < 3; i++)
        cout << shift[i] << '\t';
    cout << endl;
}

void printRotor(int rotor[3])
{
    cout << '\t';
    for(int i = 0; i < 3; i++)
        cout << rotor[i] << '\t';
    cout << endl;
}

void resetShift(int shift[3])
{
    for(int i = 0; i < 3; i++)
        shift[i] = 0;
}

void setShift(int shift[3])
{
    for(int i = 0; i < 3; i++)
    {
        cout << "set shift " << i +1 << ": ";
        int a; cin >> a;
        shift[i] = a%26;
        if (!cin) // unsupported input
        {
            cout << "Unsupported input, try again." << endl;
            cin.clear();
            clearBuffer();
            i--; // ask again for the same rotor's shift
            continue;
        }
        clearBuffer(); // after each cin clear the buffer
    }
}

void setRotor(int rotor[3])
{
    for(int i = 0; i < 3; i++)
    {
        cout << "set initial shift of rotor " << i + 1 << ": ";
        int a; cin >> a;
        rotor[i] = a%26;

        if (!cin) // unsupported input
        {
            cout << "Unsupported input, try again." << endl;
            cin.clear();
            clearBuffer();
            i--; // ask again for the same rotor's shift
            continue;
        }
        clearBuffer(); // after each cin clear the buffer
    }
}

void encryptFile(int scramblers[3+1][26], int shift[3], int rotor[3])
{

    if(keySet == 0)
    {
        cout << "There is no key to encrypt with right now, call set_key." << endl;
        return;
    }


    // get the address and save it to name (for input)
    cout << "Enter the name of the file to encrypt: ";
    string name;
    cin >> name;
    clearBuffer();

    // open the file to read from
    ifstream openText;
    openText.open(name.c_str());
    if (openText == NULL)
    {
        cout << "Failed to open the file, process aborted." << endl;
        return;
    }


    // get the address and save it to name (for output)
    cout << "Enter the name of the output file: ";
    cin >> name;
    clearBuffer();

    // open the file to write in
    ofstream closedText;
    closedText.open(name.c_str());
    if (closedText == NULL)
    {
        cout << "Failed to open the file, process aborted." << endl;
        openText.close();
        return;
    }

    char c;

    while(openText.get(c))
    {
        bool isLow = islower(c);
        c = toupper(c);

        // if the character is a letter otherwise do not change it and do not shift scramblers
        if (c >= 'A' and c <= 'Z')
        {

            // shift ('rotate') scramblers
            shift[0]++;
            if (shift[0] == 26)
            {
                shift[1]++;
                shift[0] = 0;

                if (shift[1] == 26)
                {
                    shift[2]++;
                    shift[1] = 0;

                    if (shift[2] == 26)
                    {
                        shift[2] = 0;
                    }
                }
            }


            // turn c into number - how far it is from 'A' in ASCII
            c = c - 'A';

            // corresponding to the plugboard
            c = afterPlug(c);

            /*
               c now need to get through all 3 scramblers
               'reflect' from the reflector
               and go back through all the 3 scramblers again
            */
            // the trip to the reflector
            for (int j = 0; j < 3; j++)
            {

                // encrypt the letter according to the key in the j-th srambler
                if (c + shift[j] + rotor[j] >= 26)
                {
                    // add shift to the number (made from the letter currently being encrypted), find it in the key in the current scrambler, change it according to it and subtract shift
                    c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                }
                else
                    c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                // if c is after subtracting shift less then 0 add 26 to return it back through 'Z'
                if (c < 0)
                    c += 26;

            }

            // encrypt through the reflector
            c = scramblers[3][c];

            // the way back
            for (int j = 2; j >= 0; j--)
            {
                if (c + shift[j] + rotor[j] >= 26)
                {
                    c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                }
                else
                    c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                if (c < 0)
                    c += 26;

            }

            // turn c back into a letter
            c = afterPlug(c);
            if (!capF and isLow)
                c += 'a';
            else
                c += 'A';
        }

        // print the (possibly) encrypted character
        closedText << (char) c;
    }

    // finish and clean up
    openText.close();
    closedText.close();
}

void capitalize(){
    cout << "Input text is ";
    if (!capI)
        cout << "NOT ";
    cout << "being capitalized." << endl;
    cout << "Type 'I' or 'i' to change it." << endl;
    cout << endl;

    cout << "Input file text is ";
    if (!capF)
        cout << "NOT ";
    cout << "being capitalized." << endl;
    cout << "Type 'F' or 'f' to change it." << endl;

    cout << endl << "To change both type 'B' or 'b'." << endl;

    char a;
    cin >> a;
    clearBuffer();
    a = toupper(a);

    if(a == 'I' or a == 'B')
        capI = !capI;
    if(a == 'F' or a == 'B')
        capF = !capF;
}

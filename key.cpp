#include "key.h"
#include "cin.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>

extern bool keySet;

using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void generateScrambler(int scramblers[3+1][26])
{
    cout << "Enter the number of the scrambler you want to overwrite. Indexed from 1." << endl;
    cout << "Use '4' for the reflector." << endl;

    // which scrambler do we want to overwrite
    string whichS;
    int which;
    do {
        cin >> whichS;
        clearBuffer();

        if (!is_number(whichS)){
            cout << "Input is not a valid number! Try again." << endl;
            continue;
        }

        which = atoi(whichS.c_str());
        if (which < 1 or which > 4){
            cout << "Invalid scrambler index. Try again." << endl;
            continue;
        }

        break;

    } while(true);
    which--; // to index from 0

    // get the seed
    cout << "Enter the seed for the rand function (if the input is not a number, time(NULL) will be used): ";
    string seedS;
    int seed;
    cin >> seedS;
    clearBuffer();
    if (is_number(seedS))
    {
        seed = atoi(seedS.c_str());
        srand(seed);
    }
    else
    {
        srand(time(NULL));
    }

    // prepare the new scrambler


    // fill the array with all possible values
    int toMatch[26];
    for (int i = 0; i < 26; i++)
        toMatch[i] = i;

    // to save the final randomly generated pairs
    int pairs[26];

    // randomly couple (match) numbers from toMatch
    /*
     *    just for 25 letters, it goes from end to beginning, so the letter A is left
     *    it is because there could be just 0 left for A which is also 0, so it would get paired with itself
     *    so we couple it after all other letters are coupled
     */
    for (int i = 25; i > 0; i--)
    {

        // what number from toMatch will be used to couple
        int a = rand()%i;

        // find a-th unused number different from the letter it represents (so B can't get paired with 1)
        int j;
        for (j = 0; j < a + 1; j++)
        {
            if (toMatch[j] == -1 || toMatch[j] == i)
            {
                a++;
            }
        }
        // save this randomly chosen number to pairs (filled from end to beginning)
        pairs[i] = toMatch[j - 1];
        toMatch[j - 1] = -1;
    }

    // find number to match with number that represents A
    for (int j = 0;; j++)
    {
        if (toMatch[j] != -1)
        {
            // if there is 0 left for it in order to avoid duplication exchange values with another random number
            if (toMatch[j] == 0)
            {
                int a = rand()%25+1;
                toMatch[j] = pairs[a];
                pairs[a] = 0;
                break;
            }
            else
            {
                pairs[0] = toMatch[j];
                break;
            }
        }
    }

    // for each letter
    for (int i = 0; i < 26; i++)
    {

        // find where the letter i stored in pairs is
        for (int j = 0;; j++)
        {

            if (pairs[j] == i)
            {

                // somehow works (no idea)
                if (j % 2 == 0)
                {
                    scramblers[which][i] = pairs[j + 1];
                    break;
                }
                else
                {
                    scramblers[which][i] = pairs[j - 1];
                    break;
                }

            }

        }
    }

}

void generateKey()
{
    // get the name of the file
    cout << "Enter name of the file to save the key in: ";
    string output;
    cin >> output;
    clearBuffer();
    ofstream file;
    file.open(output.c_str());

    // get the seed
    cout << "Enter the seed for the rand function (if the input is not a number, time(NULL) will be used): ";
    string seedS;
    int seed;
    cin >> seedS;
    clearBuffer();
    if (is_number(seedS))
    {
        seed = atoi(seedS.c_str());
        srand(seed);
    }
    else
    {
        srand(time(NULL));
    }


    // if there was a problem creating/opening the file, return
    if (file == NULL)
    {
        cout << "Error creating/opening the file, process aborted";
        return;
    }

    // for each scrambler and the reflector generate a key
    for (int scr = 0; scr < 4; scr++)
    {

        // fill the array with all possible values
        int toMatch[26];
        for (int i = 0; i < 26; i++)
            toMatch[i] = i;

        // to save the final randomly generated pairs
        int pairs[26];

        // randomly couple (match) numbers from toMatch
        /*
         *    just for 25 letters, it goes from end to beginning, so the letter A is left
         *    it is because there could be just 0 left for A which is also 0, so it would get paired with itself
         *    so we couple it after all other letters are coupled
         */
        for (int i = 25; i > 0; i--)
        {

            // what number from toMatch will be used to couple
            int a = rand()%i;

            // find a-th unused number different from the letter it represents (so B can't get paired with 1)
            int j;
            for (j = 0; j < a + 1; j++)
            {
                if (toMatch[j] == -1 || toMatch[j] == i)
                {
                    a++;
                }
            }
            // save this randomly chosen number to pairs (filled from end to beginning)
            pairs[i] = toMatch[j - 1];
            toMatch[j - 1] = -1;
        }

        // find number to match with number that represents A
        for (int j = 0;; j++)
        {
            if (toMatch[j] != -1)
            {
                // if there is 0 left for it in order to avoid duplication exchange values with another random number
                if (toMatch[j] == 0)
                {
                    int a = rand()%25+1;
                    toMatch[j] = pairs[a];
                    pairs[a] = 0;
                    break;
                }
                else
                {
                    pairs[0] = toMatch[j];
                    break;
                }
            }
        }

        // for each letter
        for (int i = 0; i < 26; i++)
        {

            // find where the letter i stored in pairs is
            for (int j = 0;; j++)
            {

                if (pairs[j] == i)
                {

                    // somehow works (no idea)
                    if (j % 2 == 0)
                    {
                        file <<  '\t' << pairs[j + 1] << endl;
                        break;
                    }
                    else
                    {
                        file << '\t' << pairs[j - 1] << endl;
                        break;
                    }

                }

            }
        }

        // separate next scrambler by a blank line
        file << endl;

    }

    // inform the user, the generation was successful
    cout << "The key was successfully uploaded." << endl;
}

void setKey(int scramblers[3+1][26])
{

    // get the address of the file with the key
    cout << "Enter the name of the file to upload the key from: ";
    string name;
    cin >> name;
    clearBuffer();

    // open the file
    ifstream file;
    file.open(name.c_str());

    // check for possible errors while opening the source file
    if(file == NULL)
    {
        cout << "There was an error opening the file, process aborted." << endl;
        return;
    }

    // to catch errors while uploading
    bool error = 0;

    // actually upload the key to scramblers
    for(int j = 0; j < 3; j++)
    {
        if(file.eof())
        {
            cout << "File corrupted! Scramblers are not fully set." << endl;
            error = 1;
            break;
        }
        for(int i = 0; i < 26; i++)
        {
            if(file.eof())
            {
                break;
            }
            file >> scramblers[j][i];
        }
    }

    // now upload the key to reflector
    for(int i = 0; i < 26; i++)
    {
        if(file.eof())
        {
            cout << "File corrupted! Reflector is not fully set." << endl;
            error = 1;
            break;
        }
        file >> scramblers[3][i];
    }

    // finish it and tide up
    if(error)
    {
        keySet = false;
    }
    else
    {
        cout << "The key has been successfully uploaded from " << name << "." << endl;
        // key was set
        keySet = true;
    }
    file.close();
}



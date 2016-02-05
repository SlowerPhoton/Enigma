#include "key.h"
#include <iostream>
#include <limits.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

void getKey(int key[8]){
    /* cout << "Prejete si nacist klic? [Y/N] (program se pokusi klic nacist z key.txt)" << endl;
    char answer;
    cin >> answer;
    answer = toupper(answer); // akceptuj i y/n
    if (answer == 'Y'){
        if(uploadKey(key)) // pokud nacteni klice probehlo uspesne
            return; // opust tuto funkci, klic uz je nacteny
    }

    cout << "Zadej klic o 8 cislech: " << endl;
    for(int i = 0; i < 8; i++){
        int nmbr;
        cout << ">";
        cin >> nmbr;
        if(nmbr >= 0 and nmbr <= 255)
            key[i] = nmbr;
        else {
            cout << "Cislo musi byt v rozsahu <0; 255>, zadej znovu!" << endl;
            i--;
        }
    }
    cout << endl;*/

    // clear the buffer after cin used to get the message
    std::cin.clear(); std::cin.ignore(INT_MAX,'\n');

    // get the key
    std::cout << "Enter the key <string>: " << std::endl;
    char keyWord[256];
    fgets(keyWord, 256, stdin);

    // in case the last position of keyWord is '\n' delete it
    if(keyWord[strlen(keyWord) - 1] == '\n'){
        keyWord[strlen(keyWord) - 1] = '\0';
    }

    keyTo8Bytes(keyWord, key);
}

void keyTo8Bytes(char keyWord[], int key[8]){

    // prepare array S with numbers from 0 to 255
    int S[256];
    for(int i = 0; i < 256; i++){
        S[i] = i;
    }

    // shuffle S
    int j = 0;
    int length = strlen(keyWord);
    for(int i = 0; i < 256; i++){
        j = (j + S[i] + keyWord[i % length])%256;
        int pom = S[j];
        S[j] = S[i];
        S[i] = pom;
    }

    // prepare file key.txt for uploading the key OPTIONAL
    /*std::ofstream keyDestination;
    keyDestination.open("key.txt");
    if(keyDestination == NULL){
        std::cout << "Failed to open key.txt, however key is retrieved" << std::endl;
    }*/

    // use first 8 indexes from S (and shuffle them again)
    int i = 0;
    j = 0;
    for(int a = 0; a < 8; a++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int pom = S[i];
        S[i] = S[j];
        S[j] = pom;
        int keyByte = S[(S[i] + S[j]) % 256];
        key[a] = keyByte;
        /*if(keyDestination != NULL){
            keyDestination << keyByte << std::endl;
        }*/
    }

    //keyDestination.close();

}

bool uploadKey(int key[8]){     /* RIGHT NOW UNUSED, UNTRANSLATED */


    std::ifstream keyFile;
    keyFile.open("key.txt");
    if(keyFile == NULL) {
        std::cout << "Soubor key.txt se nepodarilo otevrit" << std::endl;
        return false;
    }

    for(int i = 0; i < 8; i++){

        int nmbr;
        keyFile >> nmbr;

        // check whether we have reached the end of the file already
        if(keyFile.eof()){
            std::cout << "Soubor musi obsahovat 8 cisel!" << std::endl;
            return false;
        }

        // check whether the number is in the range <0; 255>
        if(nmbr >= 0 and nmbr <= 255)
            key[i] = nmbr;
        else {
            std::cout << "Cisla musi byt v rozsahu <0; 255>, nacitani zruseno!" << std::endl;
            return false;
        }
    }

    return true;
}

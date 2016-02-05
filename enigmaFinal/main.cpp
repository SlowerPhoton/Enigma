#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>

#define SCRAMBLERS 3

using namespace std;

int main()
{
    srand(time(NULL));

    // misto urcene pro nacteni klice od scrambleru
    int scramblers[SCRAMBLERS][26];

    // misto urcene pro nacteni klice od reflectoru
    int reflector[26];

    // zde se uklada "otaceni" - rsp. jeho simulace
    int shift[SCRAMBLERS] = {0,0,0};

    // moznost prdnastavit pocatecni otoceni rotoru
    int rotor[SCRAMBLERS] = {0,0,0};

    // zde se uklada posledni vygenerovana sifra (pro zjednoduseni kontroly funkcnosti programu)
    char lastCypher[256];

    // pro kontrolovani, zda byl jiz nastaven klic
    bool keySet = 0;

    // directory, kde se bude pracovat se soubory
    string root;
    cout << "Zadej cestu do adresare, kde se bude pracovat se soubory" << endl;
    cout << "vzor: C:\\\\Users\\\\Desktop" << endl;
    cin >> root;


    char get[50];
    do{
       cin >> get;

        if(strcmp(get, "help") == 0){
            cout << "changeRoot " << "\t" << "zmeni cilovy adresar" << endl;
            cout << "printRoot " << "\t" << "vytiskne aktualni adresar" << endl;
            cout<< endl;
            cout << "generateKey " << "\t" << "vygeneruje klic a ulozi ho do souboru .txt" << endl;
            cout << "setKey " << "\t" << "nacte klic ze zvoleneho txt souboru do scrambleru a reflectoru" << endl;
            cout << endl;
            cout << "printScramblers " << "\t" << "vytiskne soucasne nastaveni scrambleru" << endl;
            cout << "printReflector " << "\t" << "vytiskne soucasne nastaveni reflektoru" << endl;
            cout << "printShift " << "\t" << "vytiskne soucasny shift (o kolik se scramblery otocily)" << endl;
            cout << "printRotor " << "\t" << "vytiskne soucasne nastaveni rotoru (podobny jako shift - jedna se hodnotu, o jakou jsou scramblery hned od zacatku otoceny)" << endl;
            cout << endl;
            cout << "setShift " << "\t" << "nastavi shift do zvolenych hodnot" << endl;
            cout << "setRotor " << "\t" << "nastavi rotor do zvolenych hodnot" << endl;
            cout << "resetShift " << "\t" << "nastavi shift na 0 0 0" << endl;
            cout << "resetRotor " << "\t" << "nastavi rotor na 0 0 0" << endl;
            cout << endl;
            cout << "cypher " << "\t" << "vyzve k zadani textu k zasifrovani" << endl;
            cout << "       " << "\t" << "muze byt misto textu pouzito '-lc', ktere k zasifrovani pouzije posledne vytvorenou sifru" << endl;
            cout << "cypherFile " << "\t" << "vyzve k zadani souboru k zasifrovani a ciloveho souboru" << endl;
            cout << endl;
            cout << "end " << "\t" << "ukonci program" << endl;
            cout << endl;
        }
        else if(strcmp(get, "setKey") == 0){

            // get the address of the file with the key
            cout << "from what file should we upload the key?" << endl;
            string name;
            cin >> name;
            string where = root + "\\" + "\\" + name;

            // open the file
            ifstream file;
            file.open(where.c_str());

            // check for possible errors while opening the source file
            if(file == NULL){
                cout << "there was an error uploading the key, process aborted" << endl;
                continue;
            }

            // to catch errors while uploading
            bool error = 0;

            // actually upload the key to scramblers
            for(int j = 0; j < SCRAMBLERS; j++){
                if(file.eof()){
                    cout << "File corrupted! Scramblers are not fully set." << endl;
                    error = 1;
                    break;
                }
                for(int i = 0; i < 26; i++){
                    if(file.eof()){
                        break;
                    }
                    file >> scramblers[j][i];
                }
            }

            // now upload the key to reflector
            for(int i = 0; i < 26; i++){
                if(file.eof()){
                    cout << "File corrupted! Reflector is not fully set." << endl;
                    error = 1;
                    break;
                }
                file >> reflector[i];
            }

            // if we haven't reached the end of file, the file may be buggy
            /* *********** TODO *********** */
            /*file >> get;
            if(!file.eof()){
                cout << "It seems there is something left in the file. Check whether it is the right one." << endl;
            }*/

            // finish it and tide up
            if(error){
                keySet = 0;
            }
            else{
                cout << "the key has been uploaded from " << where << endl;
                keySet = 1;
            }
            file.close();
        }

        else if(strcmp(get, "printScramblers") == 0){

            // print the current scramblers settings
            cout << "the current scramblers' settings are: "<< endl;
            for(int i = 0; i < 26; i++){
                    cout << scramblers[0][i] << "\t" << scramblers[1][i] << "\t" << scramblers[2][i] << endl;
            }
            cout << endl;
       }

        else if(strcmp(get, "changeRoot") == 0){

            // change the root path
            cout << "Zadej novou cestu: ";
            cin >> root;

       }

        else if(strcmp(get, "printRoot") == 0){

            // print the current root
            cout << root << endl;

       }

        else if(strcmp(get, "sizeRoot") == 0){

            // print the current scramblers settings
            cout << strlen(root.c_str()) << endl;

       }
        else if(strcmp(get, "generateKey") == 0){

            // get the address and save it to where
            cout << "to what file should we upload the generated key?" << endl;
            string name;
            cin >> name;
            string where = root + "\\" + "\\" + name;
            cout << where << endl;

            // open the file
            ofstream target;
            target.open(where.c_str());


            // vygeneruj pro kazdy scrambler klic
            for(int scramblers = 0; scramblers < 4; scramblers++){

                // napln array vsemi moznymi hodnotami
                int keSparovani[26];
                for(int i = 0; i < 26; i++)
                    keSparovani[i] = i;

                // kam ukladat vyslednou sekvenci, jeste nez ji presunu do souboru
                int pary[26];

                // ted nahodne sparuj cisla z keSparovani
                /*
                * vygeneruje se jen pro 25 pismen, jde od konce, tedy zbyde A
                * to proto, ze neumime zajistit, aby na A nezbylo 0
                * i jemu se priradi druh - az po skonceni teto funkce
                */
                for(int i = 25; i > 0; i--){

                    // kolikate cislo z keSparovani mam brat
                    int a = rand()%i;

                    // najdi a-te zatim nepouzite cislo rozdilne od pismena, ktere reprezentuje (tedy B se nemuze sparovat s 1)
                    int j;
                    for(j = 0; j < a + 1; j++){
                        if(keSparovani[j] == -1 || keSparovani[j] == i){
                            a++;
                        }
                    }
                    // uloz toto nahodne cislo do pary (plni se od konce na zacatek)
                    pary[i] = keSparovani[j-1];
                    keSparovani[j-1] = -1;
                }

                // najdi, co priradit do posledniho cisla, ktere odpovida A
                for(int j = 0;;j++){
                    if(keSparovani[j]!=-1){
                        // pokud uz na nej zbyla jen 0, aby nedoslo k duplikaci, prohod si hodnotu s nahodnym jinym cislem
                        if(keSparovani[j]==0){
                            int a = rand()%25+1;
                            keSparovani[j] = pary[a];
                            pary[a]= 0;
                            break;
                        }
                        else{
                            pary[0] = keSparovani[j];
                            break;
                        }
                    }
                }

                // pro kazde pismeno
                for(int i = 0; i < 26; i++){

                    // najdi, kde je pismeno i zapsane v pary
                    for(int j = 0;;j++){

                        if(pary[j] == i){

                            // zapis ho do souboru
                            if(j%2==0){
                                target << "\t" << pary[j+1] << endl;
                                break;
                            }

                            else{
                                target << "\t" << pary[j-1] << endl;
                                break;
                            }
                        }
                    }
                }

                // dalsi scrambler oddel prazdnym radkem
                target << endl;

            }


            // finish it and tide up
            cout << "the key has been saved to " << where << endl;
            target.close();

        }
        else if(strcmp(get, "resetShift") == 0){

            // zresetuj shift na {0, 0, 0}
            for(int i = 0; i < SCRAMBLERS; i++){
                shift[i] = 0;
            }

            // resetovani probehlo uspesne
            cout << "shift byl uveden do polohy: " << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;
        }

        else if(strcmp(get, "setShift") == 0){

            // nastav kazdou slozku shift[]
            for(int i = 0; i < SCRAMBLERS; i++){

                // priprav si promenne
                cout << "Do jake polohy chcete uvest shift pro scrambler " << i + 1 <<"? ";
                int a;
                cin >> a;

                // shift je platne cislo
                if(a >= 0 and a < 26){
                    shift[i] = a;
                }

                // shift neni platne cislo, zkus znovu
                else {
                    cout << "neplatny shift, zadej znovu" << endl;
                    i--;
                }
            }

            // nech si to uzivatele zkontrolovat
            cout << "shift byl uveden do polohy: " << "\t" << shift[0] << "\t" << shift[1] << "\t" << shift[2] << endl;
        }

        else if(strcmp(get, "printShift") == 0){

            // vypis shift[]
            cout << "shift je v poloze: " << "\t" << shift[0] << "\t" << shift[1] << "\t" << shift[2] << endl;
        }

        else if(strcmp(get, "cypher") == 0){

            // zkontroluj, zda byl nastven klic
            if(keySet == 0){
                cout << "There is no key to encrypt with right now, call setKey" << endl;
                continue;
            }

            // priprav promenne
            cout << "Zadejte text k sifrovani: ";
            char openText[256];
            cin >> openText;
            char c;

            // zkontroluj, jestli uzivatel nechce vyuzit lastCypher urceny pro zjednoduseni kontrolovani funkcnosti programu
            if(strcmp(openText,"-lc") == 0){
                // napln openText lastCypher
                for(int i = 0, length = strlen(lastCypher); i < length; i++)
                    openText[i] = lastCypher[i];
                // zresetuj shift na {0, 0, 0}
                for(int i = 0; i < SCRAMBLERS; i++){
                    shift[i] = 0;
                }
            openText[strlen(lastCypher)] = NULL;
            }

            // pro kazdy znak z nacteneho textu sifruj
            for(int i = 0, n = strlen(openText); i < n; i++){

                // preved sifrovany text do tiskacich
                c = openText[i];
                c = toupper(c);

                // pokud je sifrovany znak pismeno, jinak ho nech nezmeneny
                if(c >= 'A' and c <= 'Z'){

                    // otoc scramblery
                    shift[0]++;
                        if(shift[0] == 26){
                            shift[1]++;
                            shift[0] = 0;

                            if(shift[1] == 26){
                                shift[2]++;
                                shift[1] = 0;

                                if(shift[2] == 26){
                                    shift[2] = 0;
                                }
                            }
                        }


                    // vycisli c
                    c = c - 'A';

                    /*
                    * c ted bude muset projit pres 3 scramblery,
                    * "odrazit se" od reflektoru
                    * a projit pres vsechny 3 scramblery zpet
                    */
                    // cesta tam
                    for(int j = 0; j < 3; j++)
                    {

                        // zasifruj znak dle klice v j-tem scrambleru
                        if (c + shift[j] + rotor[j] >= 26)
                        {
                            // pricti ke znaku shift, vyhledej ho v klici, zmen ho a odecti od nej shift
                            c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                        }
                        else
                            c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                        // pokud po odecteni shiftu (rotoru) kledlo c pod nulu, vrat ho pres 'Z' zpatky
                        if(c < 0)
                            c+=26;

                    }

                    // zasifruj skrz reflector
                    c = reflector[c];

                    // zasifruj skrz vsechny scramblery i cestou zpet
                    for(int j = 2; j >= 0; j--)
                    {
                        if (c + shift[j] + rotor[j] >= 26)
                        {
                            c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                        }
                        else
                            c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                        if(c<0)
                            c+=26;

                    }

                    // zmen c zpet v pismeno
                    c += 'A';
                }


                // vypis zasifrovany znak
                cout << c;
                lastCypher[i] = c;
            }

            //ukonci lastCypher
            lastCypher[strlen(openText)] = NULL;

            // priprav comman line na dalsi get
            cout << endl;
       }


        else if(strcmp(get, "setRotor") == 0){

            // nastav kazdou slozku rotor[]
            for(int i = 0; i < SCRAMBLERS; i++){

                // priprav si promenne
                cout << "Do jake polohy chcete uvest rotor pro scrambler " << i + 1 <<"? ";
                int a;
                cin >> a;

                // rotor je platne cislo
                if(a >= 0 and a < 26){
                    rotor[i] = a;
                }

                // shift neni platne cislo, zkus znovu
                else {
                    cout << "neplatny rotor, zadej znovu" << endl;
                    i--;
                }
            }

            // nech si to uzivatele zkontrolovat
            cout << "rotor byl uveden do polohy: " << "\t" << rotor[0] << "\t" << rotor[1] << "\t" << rotor[2] << endl;
        }
        else if(strcmp(get, "printRotor") == 0){

            // vypis rotor[]
            cout << "rotor je v poloze: " << "\t" << rotor[0] << "\t" << rotor[1] << "\t" << rotor[2] << endl;
        }

        else if(strcmp(get, "resetRotor") == 0){

            // zresetuj rotor na {0, 0, 0}
            for(int i = 0; i < SCRAMBLERS; i++){
                rotor[i] = 0;
            }

            // resetovani probehlo uspesne
            cout << "rotor byl uveden do polohy: " << "\t" << 0 << "\t" << 0 << "\t" << 0 << endl;
        }

        else if(strcmp(get, "printReflector") == 0){

            // print the current reflector settings
            cout << "the current reflector settings are: "<< endl;
            for(int i = 0; i < 26; i++){
                    cout << "\t" << reflector[i] << endl;
            }
            cout << endl;
        }

        else if(strcmp(get, "cypherFile") == 0){

            if(keySet == 0){
                cout << "There is no key to encrypt with right now, call setKey" << endl;
                continue;
            }


            // get the address and save it to where
            cout << "Zadej jmeno souboru k zasifrovani: ";
            string name;
            cin >> name;
            string where = root + "\\" + "\\" + name;
            cout << where << endl;

            // open the file to read from
            ifstream openText;
            openText.open(where.c_str());


            // get the address and save it to where
            cout << "Zadej jmeno souboru k zapsani sifrovaneho textu: ";
            cin >> name;
            where = root + "\\" + "\\" + name;
            cout << where << endl;

            // open the file to write in
            ofstream closedText;
            closedText.open(where.c_str());

            char c;

            // jestli se soubory podarilo otevrit, pro kazdy znak ze souboru sifruj
            if(openText == NULL || closedText == NULL){
                cout << "Failed to open the file(s)" << endl;
            } else
            while(openText.get(c)){

                // preved sifrovany text do tiskacich

                c = toupper(c);

                // pokud je sifrovany znak pismeno, jinak ho nech nezmeneny
                if(c >= 'A' and c <= 'Z'){

                    // otoc scramblery
                    shift[0]++;
                        if(shift[0] == 26){
                            shift[1]++;
                            shift[0] = 0;

                            if(shift[1] == 26){
                                shift[2]++;
                                shift[1] = 0;

                                if(shift[2] == 26){
                                    shift[2] = 0;
                                }
                            }
                        }


                    // vycisli c
                    c = c - 'A';

                    /*
                    * c ted bude muset projit pres 3 scramblery,
                    * "odrazit se" od reflektoru
                    * a projit pres vsechny 3 scramblery zpet
                    */
                    // cesta tam
                    for(int j = 0; j < 3; j++)
                    {

                        // zasifruj znak dle klice v j-tem scrambleru
                        if (c + shift[j] + rotor[j] >= 26)
                        {
                            // pricti ke znaku shift, vyhledej ho v klici, zmen ho a odecti od nej shift
                            c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                        }
                        else
                            c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                        // pokud po odecteni shiftu (rotoru) kledlo c pod nulu, vrat ho pres 'Z' zpatky
                        if(c < 0)
                            c+=26;

                    }

                    // zasifruj skrz reflector
                    c = reflector[c];

                    // zasifruj skrz vsechny scramblery i cestou zpet
                    for(int j = 2; j >= 0; j--)
                    {
                        if (c + shift[j] + rotor[j] >= 26)
                        {
                            c = scramblers[j][-26 + c + shift[j] + rotor[j]] - shift[j] - rotor[j];
                        }
                        else
                            c = scramblers[j][c + shift[j] + rotor[j]] - shift[j] - rotor[j];

                        if(c<0)
                            c+=26;

                    }

                    // zmen c zpet v pismeno
                    c += 'A';
                }


                // zapis zasifrovany znak
                closedText << c;
            }

            // priprav command line na dalsi get
            openText.close();
            closedText.close();
            cout << "File encrypted" << endl;


        }

        else if(strcmp(get, "end")){
            cout << "command unrecognized" << endl;
        }

    // zde konci do-while
    }
    while (strcmp(get, "end"));

    return 0;
}

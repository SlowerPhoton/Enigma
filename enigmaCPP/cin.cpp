#include "cin.h"

#include <iostream>
#include <limits>

using namespace std;

void clearBuffer(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

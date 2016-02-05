/**
    @file
    functions used to get and prepare the message
*/

#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include <vector>

/**
    asks user for the number of characters in the message
    @return number of characters in the message
    @n right now unused
*/
int getSizeOfMessage(); /*UNUSED*/


/**
    counts how many characters we need to add to the message in order to be a multiple of 8 characters long (64 bits)
*/
int padding(int numbersInMessage);

/**
    get the message from the user, character after character <unsigned char>
    @param message an array to store the message
    @param numbersInMessage the size of the message (in bytes)

*/
void getMessage(std::vector<unsigned char> &message);

/**
    expands the message in order to be a multiple of 8 ints (bytes) long
    @n adds @c 0 in the empty indexes
*/
void messageExpand(std::vector<unsigned char> &message);

/** \brief converts the message in form of unsigned chars into binary message
 *
 */
void messageToBinary(bool binaryMessage[], std::vector<unsigned char> &message);

#endif // MESSAGE_H_INCLUDED

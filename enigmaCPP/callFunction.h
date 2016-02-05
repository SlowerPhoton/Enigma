#ifndef CALLFUNCTION_H_INCLUDED
#define CALLFUNCTION_H_INCLUDED

#include<string>

/** \brief
 * calls appropriate function according to the command line input
 * \param get command line input
 * \return false if "end" was typed in, otherwise true
 *
 */
bool callFunction(std::string get, int scramblers[3+1][26], int shift[3], int rotor[3]);

/** \brief
 *  trims a given string (deletes spaces from the end and beginning)
 * \param string s to trim
 * \return trimmed string
 *
 */

std::string trim(const std::string &s);


#endif // CALLFUNCTION_H_INCLUDED

#ifndef ENCRYPTION_H_INCLUDED
#define ENCRYPTION_H_INCLUDED

/** \brief
 *  gets a text from the user, encrypts it and outputs it
 * \param scramblers to load the scramblers' settings
 * \param shift to load the shift
 * \param rotor to load the rotor
 *
 */
void encrypt(int scramblers[3+1][26], int shift[3], int rotor[3]);

/** \brief
 *  gets a name of a file to encrypt and encrypts it into a chosen output file
 * \param scramblers to load the scramblers' settings
 * \param shift to load the shift
 * \param rotor to load the rotor
 *
 */
void encryptFile(int scramblers[3+1][26], int shift[3], int rotor[3]);

/** \brief
 *  resets each rotor's shift to 0
 * \param shift to alter it
 *
 */
void resetShift(int shift[3]);

/** \brief
 *  for each rotor asks user for a new shift value
 * \param shift to alter it
 *
 */
void setShift(int shift[3]);

/** \brief
 *  for each rotor asks user for a new initial shift value
 * \param rotor to alter it
 *
 */
void setRotor(int rotor[3]);

/** \brief
 *  prints the shift of each rotor
 * \param shift to read it
 *
 */
void printShift(int shift[3]);

/** \brief
 *  prints the initial shift of each rotor
 * \param rotor to read it
 *
 */
void printRotor(int rotor[3]);

/** \brief
 *  enables user to change the current settings of capitalization \n
 *  by default input is capitalized, file input not
 */
void capitalize();


#endif // ENCRYPTION_H_INCLUDED

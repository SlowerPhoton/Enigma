#ifndef KEY_H_INCLUDED
#define KEY_H_INCLUDED

/** \brief
 *  generates the key and uploads it to a file
 * \param scramblers scramblers to fill in the key
 *
 */
void generateKey();

/** \brief
 *  uploads the key to scramblers from a file
 * \param scramblers to upload the data
 *
 */
void setKey(int scramblers[3+1][26]);

/** \brief generates a new scrambler (or the reflector)
 *
 * \param scrambler to alter data (overwrites a chosen scrambler)
 *
 */
void generateScrambler(int cramblers[3+1][26]);

#endif // KEY_H_INCLUDED

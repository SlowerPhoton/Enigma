#ifndef PLUGBOARD_H_INCLUDED
#define PLUGBOARD_H_INCLUDED


/** \brief enters set_plugboard mode
 *  that enables user to plug two letters together, unplug, print plugs
 *  exit by typing 'return'
 *
 */
void setPlugboard();

/** \brief resets the plugboard, so no letters are plugged
 *  needs to be called at the beginning of the program
 *
 */
void resetPlugboard();

/** \brief looks up a letter in plugboard, if it is plugged, switches it to its counterpart
 *
 * \param letter to look up in plugboard
 * \return the same letter, if unplugged, its counterpart otherwise
 *
 */
int afterPlug(char a);

#endif // PLUGBOARD_H_INCLUDED

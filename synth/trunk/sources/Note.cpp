
/** \file Note.cpp Implementation file for Note class
 *
 *  This file contains the definitions for the Note class.  This
 *      class stores values handy for musical notes, such as get/set
 *      functionality for pitch, octave, sharps/flats, duration and
 *      position with respect to rest of the piece.
 *
 * \author Samuel L. Banina, 901278567, CSE21212-02
 *
 * revision history:
 *      2007-01-30   originally submitted
 *      2007-02-06   updated by position slot and methods
 *      2007-03-03   streamlined for final (added freq data)
 */
#include <iostream>
using std::cerr;
using std::endl;

#include "Note.h"

float freq(char pitch, int octave, int alter);

/** \brief Constructor with default arguments
 *
 * Constructor takes in pitch, duration, octave, and alter
 *	and validates them through the set member functions.
 * \param val (char) pitch A-G or R for rest
 * \param oct (int) which octave the note is in ( >=0 )
 * \param alt (int) how many halfsteps to alter by ( -2 <= alt >= 2 )
 */
Note::Note( char val, int oct, int alt )
{
	setPitch(val);
	setOct(oct);
	setAlter(alt);
	frequency = freq(pitch_step, octave, alter);
}

/** \brief returns the pitch name or R if rest
 *
 * \return (char) note name
 */
char Note::getPitch(void) const
{
	return pitch_step;
}

/** \brief returns the alter value
 *
 * \return (int) alter value
 */
int Note::getAlter(void) const
{
	return alter;
}

/** \brief returns the octave number
 *
 * \return (int) octave number
 */
int Note::getOct(void) const
{
	return octave;
}

/** \brief validates and sets pitch (default = R)
 * 
 * setPitch ensures the pitch is a letter A through G or R for rest.
 * \param val (char) pitch value
 */
void Note::setPitch(const char val)
{
	if( ((val >= 'A') && (val <= 'G')) || (val == 'R') )
		pitch_step = val;
	else
		cerr << "Pitch value (" << val << ") not legal" << endl;
}

/** \brief set octave number of the note
 *
 * setOct sets a lower bound of 0 on the octave number
 * \param (int) octave number
 */
void Note::setOct(const int oct)
{
	if ( oct >= 0 )
		octave = oct;
	else
		cerr << "Octave value (" << oct << ") not legal" << endl;
}

/** \brief set half-steps to alter pitch by
 *
 * setAlter validates the alter given between -2 and 2
 * \param alt (int) alter value (in half-steps)
 */
void Note::setAlter(const int alt)
{
	if( (alt >= -2) && (alt <= 2) )
		alter = alt;
	else
		cerr << "Alter value (" << alt << ") not legal" << endl;
}

float Note::getFreq(void)
{
	return frequency;
}


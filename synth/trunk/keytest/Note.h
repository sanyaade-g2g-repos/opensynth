/** \file Note.h Header file for Note class
 *
 *  This file contains the declarations for the Note class.  This
 *      class stores values handy for musical notes, such as get/set
 *      functionality for pitch, octave, sharps/flats, duration and
 *      position with respect to rest of the piece.
 *
 * \author Samuel L. Banina, 901278567, CSE21212-02
 *
 * revision history:
 *      2007-01-30   originally submitted
 *      2007-02-06   updated by position slot and methods
 */
#ifndef NOTE_H
#define NOTE_H

//struct used by freqtable
typedef struct _ft {
 char pitch; // letter on scale
 int octave; // octave 
 int alter; // -1 flat, 0 natural, 1 sharp
 float frequency;
 } ft;

/** \class Note
 * \brief The Note class allows storing of Musical Notes
 *
 * This class supports storing note pitch, duration, octave, and accidental (alter) number.
 *	It performs input validation checking and assigns default values to properties
 *	not specified in the constructor.
 */
class Note {

public:
	/** \brief Constructor with default arguments
	*
	* Constructor takes in pitch, duration, octave, and alter
	*	and validates them through the set member functions.
	* \param val (char) pitch A-G or R for rest
	* \param oct (int) which octave the note is in ( >=0 )
	* \param alt (int) how many halfsteps to alter by ( -2 <= alt >= 2 )
	*/
	Note(char val = 'R', int oct = 3, int alt = 0);

	/** \brief returns the pitch name or R if rest
	*
	* \return (char) note name
	*/
	char getPitch(void) const;
	
	/** \brief returns the alter value
	*
	* \return (int) alter value
	*/
	int getAlter(void) const;
	
	/** \brief returns the octave number
	*
	* \return (int) octave number
	*/
	int getOct(void) const;
	
	/** \brief validates and sets pitch (default = R)
	* 
	* setPitch ensures the pitch is a letter A through G or R for rest.
	* \param val (char) pitch value
	*/
	void setPitch(char);
	
	/** \brief set half-steps to alter pitch by
	*
	* setAlter validates the alter given between -2 and 2
	* \param alt (int) alter value (in half-steps)
	*/
	void setAlter(int);
	
	/** \brief set octave number of the note
	*
	* setOct sets a lower bound of 0 on the octave number
	* \param (int) octave number
	*/
	void setOct(int);

	float getFreq(void);
	
private:
	char pitch_step; //A-G and R
	int alter; //-2 through 2
	int octave;
	float frequency;

};
#endif

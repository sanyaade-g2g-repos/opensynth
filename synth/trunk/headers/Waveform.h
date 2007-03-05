/** \file Waveform.h
 * \author Samuel Lenz Banina
 *
 * This contains the headers for the class Waveform, which will be the
 * 	fundamental type in the operation of the synthesizer.
 *
 * revision history
 *	03-03-2007  originally written
 */

#ifndef WAVEFORM_H
#define WAVEFORM_H

class Waveform
{
	public:
		Waveform();
		~Waveform();

		Waveform operator+(const Waveform &);

	private:
		int volume;
		float frequency;

		float notetofreq(char pitch, int octave, int alter);
#endif

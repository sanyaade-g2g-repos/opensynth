/** \file Waveform.cpp Implementation for WaveForm Object
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file implements the WaveForm class which is the fundamental
 *   unit in the heirarchy of the synthesizer.  It dynamically creates
 *   samples of the specified waveform and returns the next sample scaled
 *   to the appropriate values for the position in the envelope.
 */
#include <cmath>
#include <sys/time.h>
#include <iostream>
using namespace std;

#include <QString>
#include "WaveForm.h"

/** \brief Constructor which generates the sample
 * 
 * This function sets all the private variables of the WaveForm class.
 *   It then computes the length (in samples) of one wavelength of the
 *   waveform.  Then depending on the type of waveform makes it from a function.
 * 
 * \param n, QString, name of the WaveForm
 * \param f, int, frequency of the WaveForm
 * \param wt, wavetype, type of the waveform (sine, square, etc.)
 * \param aa, int, attack time in ms
 * \param dd, int, decay time in ms
 * \param ss, int, sustain level in percentage of max volume
 * \param rr, int release time in ms
 */
WaveForm::WaveForm(QString n, int f, wavetype wt,
			int aa, int dd, int ss, int rr)
	:a(aa),d(dd),s(ss),r(rr),envcount(0),maxvol(2500)
{

	name = n;
	frequency = f;
	size = 44100/frequency;
	dsize = (double)size;
	sample = new double[size];
	index = 0;
	release = false;
	tempvol = 0;
	
	for(int i = 0; i < size; ++i)
	{

		if( wt == SIN ) {
			sample[i] = sin(frequency * 2 * M_PI * i / 44100); //sine wave
		} else if( wt == SQR ) {
			sample[i] = ( (i<(size/2)?1:(-1)) ); //square wave
		} else if( wt == TRI ) {
			sample[i] = 4*abs(round(i/dsize) - i/dsize ) -1; //triangle wave
		} else if( wt == SAW ) {
			sample[i] = 2 * (i/dsize - floor(i/dsize + 0.5)); //saw wave
		}

	}
}

WaveForm::WaveForm(QString n)
	:size(0), index(0), frequency(0)
{
	name = n;
	sample = new double[1]; //just so it can be deleted later
}

/** \brief Destructor for WaveForm
 * 
 * This function deletes the dynamically generated sample
 * 
 */
WaveForm::~WaveForm()
{
	delete [] sample;
}

/** \brief Returns next sample scaled to appropriate volume
 * 
 * This function looks to see if the note has been released.
 *   If so, it turns down the volume until it's less than zero,
 *   then emits a signal that it's ready to be deleted. Otherwise
 *   it tests for whether it is in the attack, decay, or sustain 
 *   phases and increases, decreases, and set the volume appropriately.
 * 
 * \param void
 * \return double, current sample
 */
double WaveForm::nextSample(void)
{
//	QMutexLocker locker(&mutex);
	int val;
	//increment the envelope counter
	envcount = envcount + 1;
	//if key has been released
	if ( release ) {
		//if there is still volume, continue to decrease it
		if( tempvol > 0 )
			tempvol = (0-relvol)*(envcount/50)/(r+1) + relvol;
		//otherwise set volume to 0 and tell AudioBuffer to delete itself
		else { 
			tempvol = 0;
		       	emit finished(name);
			return 0;
		}
	}
	//if envcount is still under attack time
	else if( (val = envcount/50) < a )
		tempvol = maxvol*val/a;
	
	//if envcount is still under decay time
	else if( (val = envcount/50 - a) < d )
		tempvol = ((s*maxvol / 100) - maxvol)*val/d + maxvol;
	
	//otherwise set to some percent of the maximum volume
	else
		tempvol = s * maxvol / 100; 

	int returnindex = (index+1)%size;
	double returnsample = sample[returnindex];
	++index;

	return (double)tempvol * returnsample;
}

/** \brief Slot which sets key to release mode
 * 
 * This set release to true, resets the envelope
 *   count, and set the starting value for the 
 *   envelope fade out to the current volume, otherwise
 *   it would jump to the max volume to fade out
 * \param void
 * \return void
 */
void WaveForm::releaseIt(void) 
{ 
//	QMutexLocker lockme(&mutex);
	release = true; 
	envcount = 0; 
	relvol = tempvol;
}


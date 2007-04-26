/** \file AudioThread.cpp Implementation of AudioThread class
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file implements a thread class which is used to continuously
 *   play the waveforms passed into the AudioBuffer instance which spawned
 *   this thread.  It is designed to work with the generic /dev/dsp device
 *   common to *nix systems.  
 */
#include "AudioThread.h"
#include "WaveForm.h"

#include <QString>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/soundcard.h>
#include <iostream>
#include <cmath>
using namespace std;

/** \brief Constructor for AudioThread class
 * 
 * This function assigns the private reference to a waveform map
 *   to the waveform map maintained by the parent AudioBuffer.  It
 *   also sends the parent pointer back to the parent class QThread.
 */
AudioThread::AudioThread(QObject *parent, map<QString, WaveForm *> & wfs)
	: QThread(parent), wf(wfs), playflag(true)
{
}

/** \brief Main event loop for AudioThread
 * 
 * This function opens up the audio device for writing, sets the buffer
 *   to a size reasonable for real-time audio, sets the format options for
 *   the sound card, and continuously plays samples from the waveform's 
 *   stored in it's waveform map.
 * \param void
 * \return void
 */
void AudioThread::run()
{
	int c,out;
	short temp;
	cout << "starting audio thread" << endl;;
	
  	out = open("/dev/dsp",O_WRONLY);
	if( out < 0) { cerr << "opening /dev/dsp failed" << endl; }
	
	int arg = 0x00100008; 			//These are the magic lines that fixed the delay
	ioctl(out,SNDCTL_DSP_SETFRAGMENT,&arg); //and stopped most of my frustration. They simply
						//set bounds on the buffering for the soundcard.

	//set sound card to accept 16-bit samples (shorts)
	c=16;
	ioctl(out,SOUND_PCM_WRITE_BITS,&c);
	//set sound card to operate in mono mode
	c=1;
	ioctl(out,SOUND_PCM_WRITE_CHANNELS,&c);
	//set sound card to 44100Hz sample rate
	c=44100;
	ioctl(out,SOUND_PCM_WRITE_RATE,&c);

	//initialize iterator to go through the wf map
	map< QString, WaveForm *>::const_iterator j;
	
	//while it should play add the next samples from all waveforms
	//  in the map and write it out to the sound card 
	while(playflag)
	{
		temp = 0;
		mutex.lock();
		for (j = wf.begin(); j != wf.end(); ++j)
		{
			temp += (short)(j->second->nextSample());
		}
		mutex.unlock();
		write(out, &temp, sizeof(short));
	}

	close(out);
	exit();
}

/** \brief Slot to set playflag to false
 * 
 * This slot gets a memory lock and sets
 *  playflag to false.
 * \param void
 * \return void
 */
void AudioThread::quitIt() 
{ 
	mutex.lock(); 
	playflag = false; 
	mutex.unlock(); 
}


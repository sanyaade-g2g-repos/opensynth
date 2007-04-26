/** \file AudioBuffer.cpp Implementation of the AudioBuffer class
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file implements the AudioBuffer class which acts as a wrapper class
 *   for the AudioThread class, which actually plays the audio in the audio
 *   "buffer".
 */
#include "AudioBuffer.h"
#include <iostream>
using namespace std;

/**  \brief Constructor initializes new AudioThread
 * 
 * This constructor passes the currentNotes map to the thread,
 *   starts the thread, and connects the signal and slot to tell
 *   the thread to quit running.
 * 
 * \param void
 */
AudioBuffer::AudioBuffer(void)
{
	playthread = new AudioThread(this, currentNotes);
	playthread->start();

	connect(this, SIGNAL(closePlay()), playthread, SLOT(quitIt()));
}

/** \brief Destructor tells AudioThread to quit
 * 
 * Emits signal to AudioThread slot "quitIt()" telling it to stop
 */
AudioBuffer::~AudioBuffer()
{
	emit closePlay();
	playthread->exit();
	delete playthread;
}

/** \brief Adds Waveforms to the current AudioBuffer
 * 
 * This function takes in a pointer to a new'ed Waveform and adds
 *   that pointer to its map relating waveform names to waveform pointers.
 *   If it finds a waveform by the same name (i.e. a key was restruck
 *   before it faded out) it deletes that waveform and adds the new one.
 *   It also connects the AudioBuffer slot "deleteWave" to the "finished"
 *   signal of the new waveform so that it can be asynchronously removed
 *   from the map later.
 * 
 * \param wf, WaveForm *, pointer to waveform to add to buffer
 * \return void
 */
void AudioBuffer::add(WaveForm * wf)
{
	if( currentNotes.end() != currentNotes.find(wf->name) ) {
		currentNotes.erase(wf->name);
		delete currentNotes[wf->name];
	}

	currentNotes[wf->name] = wf;
	connect(wf, SIGNAL(finished(QString)), 
			this, SLOT(deleteWave(QString)));
}

/** \brief Removes a WaveForm from the current AudioBuffer
 * 
 * This function takes in the name of the WaveForm which should
 *   be removed from the buffer.  If it's indeed in the buffer, it
 *   calls the WaveForm's "releaseIt()" function.
 * 
 * \param wfn, QString, waveform name
 * \return void
 */
void AudioBuffer::remove(QString wfn)
{
	if( currentNotes.end() != currentNotes.find(wfn) )
	{
		currentNotes[wfn]->releaseIt();
	}
}


/** \brief Slot that deletes a WaveForm
 * 
 * This slot is triggered by the "finished" signal from the 
 *   waveform which has finished fading.  If the given name is
 *   indeed in the buffer, the waveform is deleted and the pointer 
 *   to it removed from the map.
 * 
 * \param n, QString, name of the waveform to be deleted
 * \return void
 */
void AudioBuffer::deleteWave(QString n)
{
	if( currentNotes.end() != currentNotes.find(n)) {
		mutex.lock();
		delete currentNotes[n];
		currentNotes.erase(n);
		mutex.unlock();
	}
}


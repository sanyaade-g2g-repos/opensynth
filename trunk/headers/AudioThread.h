/** \file AudioThread.h Header for AudioThread class
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file declares a thread class which is used to continuously
 *   play the waveforms passed into the AudioBuffer instance which spawned
 *   this thread.  It is designed to work with the generic /dev/dsp device
 *   common to *nix systems.
 */
#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QtGui>
#include "WaveForm.h"
#include <map>
using namespace std;

/** \class AudioThread
 * \brief Thread class which inherits from QThread to continuously play audio
 * 
 * This class really only has one function.  The "run" function opens the 
 *   sound card file "/dev/dsp" for writing, sends various initialization 
 *   commands to the file and enters a while loop writing the sum of 
 *   samples from waveforms to the sound card.
 */
class AudioThread : public QThread
{
	Q_OBJECT
	public:
		/** \brief Constructor for AudioThread class
		 * 
		 * This function assigns the private reference to a waveform map
		 *   to the waveform map maintained by the parent AudioBuffer.  It
		 *   also sends the parent pointer back to the parent class QThread.
		 */
		AudioThread(QObject *parent, map<QString, WaveForm *> & wfs);
		
		/** \brief Main event loop for AudioThread
		 * 
		 * This function opens up the audio device for writing, sets the buffer
		 *   to a size reasonable for real-time audio, sets the format options for
		 *   the sound card, and continuously plays samples from the waveform's 
		 *   stored in it's waveform map.
		 * \param void
		 * \return void
		 */
		void run();

	public slots:
		/** \brief Slot to set playflag to false
		 * 
		 * This slot gets a memory lock and sets
		 *  playflag to false.
		 * \param void
		 * \return void
		 */
		void quitIt(void);

	private:
		//mutex to lock memory read/writes
		QMutex mutex;
		//reference to the waveform map in parent AudioBuffer
		map< QString, WaveForm * > & wf;
		//flag which controls playback
		bool playflag;
};

#endif

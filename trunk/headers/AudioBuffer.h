/** \file AudioBuffer.h header for AudioBuffer class
 *  \author Samuel L. Banina 901278567 CSE21212.02
 *
 * This class provides a layer of abstraction from the AudioThread.
 *   The API is thus simplified to telling the audiobuffer to add or remove
 *   a wavefrom instead of actually calling slots of the AudioThread which
 *   plays the audio.
 * 
 */
#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include "AudioThread.h"
#include <QObject>
#include <map>
using namespace std;

/** \class AudioBuffer
 * 
 * AudioBuffer inherits from QObject so that it can
 *   recieve signals from the notes it maintains.
 */
class AudioBuffer:public QObject
{
	Q_OBJECT
	public:
		/**  \brief Constructor initializes new AudioThread
		 * 
		 * This constructor passes the currentNotes map to the thread,
		 *   starts the thread, and connects the signal and slot to tell
		 *   the thread to quit running.
		 * 
		 * \param void
		 */
		AudioBuffer();
		
		/** \brief Destructor tells AudioThread to quit
		 * 
		 * Emits signal to AudioThread slot "quitIt()" telling it to stop
		 */
		~AudioBuffer();
		
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
		void add(WaveForm *);
		
		/** \brief Removes a WaveForm from the current AudioBuffer
		 * 
		 * This function takes in the name of the WaveForm which should
		 *   be removed from the buffer.  If it's indeed in the buffer, it
		 *   calls the WaveForm's "releaseIt()" function.
		 * 
		 * \param wfn, QString, waveform name
		 * \return void
		 */
		void remove(QString);
	
	public slots:
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
		void deleteWave(QString);

	signals:
		/** \brief Signal to close thread
		 * 
		 * This signal is connected to the spawned AudioThread's 
		 *   "quitIt()" slot to make it quit running.
		 */
		void closePlay(void);

	private:
		//memory locker to avoid bad memory access
		QMutex mutex;
		
		//map to store pointers to all currently played notes
		map< QString, WaveForm * > currentNotes;
		
		//pointer to AudioThread which is new'ed in the 
		//  constructor.
		AudioThread * playthread;


};

#endif

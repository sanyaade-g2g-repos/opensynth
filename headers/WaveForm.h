/** \file Waveform.h Header for WaveForm Object
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file declares the WaveForm class which is the fundamental
 *   unit in the heirarchy of the synthesizer.  It dynamically creates
 *   samples of the specified waveform and returns the next sample scaled
 *   to the appropriate values for the position in the envelope.
 */
#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QObject>
#include <QString>
#include <QMutex>

enum wavetype {
	SIN, SQR, TRI, SAW
};

class WaveForm:public QObject
{
	Q_OBJECT

	friend class AudioBuffer;
	
	public:	
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
		WaveForm(QString n, int f, wavetype, int aa = 500, int dd = 250, int ss = 75, int rr = 0);
		WaveForm(QString n);
		
		/** \brief Destructor for WaveForm
		 * 
		 * This function deletes the dynamically generated sample
		 * 
		 */
		~WaveForm();

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
		double nextSample(void);
		/** \brief Slot which sets key to release mode
		 * 
		 * This set release to true, resets the envelope
		 *   count, and set the starting value for the 
		 *   envelope fade out to the current volume, otherwise
		 *   it would jump to the max volume to fade out
		 * \param void
		 * \return void
		 */
		void releaseIt(void);

	signals:
		/** \brief Signal denoting end of fade-out
		 * 
		 * This signal is triggered when the volume goes to zero and
		 *   is caught by the AudioBuffer handling the WaveForm, which
		 *   then deletes it.
		 */
		void finished(QString);

	private:
		QMutex mutex;
		//pointer to array of samples
		double * sample;
		//size of a wavelength (and of samples array)
		int size;
		//double version of above (used in calculations)
		double dsize;
		//current index in sample
		int index;
		//frequency of the waveform
		int frequency;
		//name of the waveform
		QString name;
		//waveform type
		wavetype wt;
		//maximum volume for use by envelope
		int maxvol;
		int a,d,s,r; //a -> time to reach full volume (ms)
			     //d -> time to decay to sustained volume
			     //s -> sustained volume
			     //r -> time to fade out from sustain
		//counts number of times nextSample has been called
		int envcount;
		//hold scaled volume
		int tempvol;
		//flag indicating release of the key
		bool release;
		//starting volume for release fadeout
		int relvol;
};

#endif


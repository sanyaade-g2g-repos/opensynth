#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QString>

enum wavetype {
	SIN, SQR, TRI, SAW
};

class WaveForm
{
	friend class AudioThread;
	friend class AudioBuffer;
	public:
		WaveForm(QString n, int f, wavetype, int aa = 500, int dd = 250, int ss = 2000, int rr = 0);
		WaveForm(QString n);
		~WaveForm();

		int getAndIncrementIndex(void);
		double nextSample(void);
		bool released(void);

	private:
		double * sample;
		int size;
		double dsize;
		int index;
		int frequency;
		QString name;
		wavetype wt;
		int maxvol; //maximum volume for use by envelope
		int a,d,s,r; //a -> time to reach full volume (ms)
			     //d -> time to decay to sustained volume
			     //s -> sustained volume
			     //r -> time to fade out from sustain
		int envcount; //contains number of sample wraps
		int tempvol;
		bool release;
};

#endif


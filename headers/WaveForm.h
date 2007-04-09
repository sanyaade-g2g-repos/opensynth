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
		WaveForm(QString n, int f, wavetype);
		WaveForm(QString n);
		~WaveForm();

		int getAndIncrementIndex(void);

	private:
		double * sample;
		int size;
		double dsize;
		int index;
		int frequency;
		QString name;
		wavetype wt;
};

#endif


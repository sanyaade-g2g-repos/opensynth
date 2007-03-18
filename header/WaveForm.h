#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QString>

class WaveForm
{
	friend class AudioThread;
	friend class AudioBuffer;
	public:
		WaveForm(QString n, int f);
		WaveForm(QString n);
		~WaveForm();

		int getAndIncrementIndex(void);

	private:
		double * sample;
		int size;
		int index;
		int frequency;
		QString name;
};

#endif


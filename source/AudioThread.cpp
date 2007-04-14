#include "AudioThread.h"
#include "WaveForm.h"
#include <QHash>
#include <QString>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/soundcard.h>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

#define FADEBUF -1

AudioThread::AudioThread(QObject *parent, QHash<QString, WaveForm *> & waveforms)
	: QThread(parent), wf(waveforms)
{
}

void AudioThread::setBuffer( int s, bool * pf)
{
	size = s;
	playflag = pf;
	*playflag = false;
}

void AudioThread::run()
{
	int c,out;
	short temp;
	short fake = 0;
	qDebug() << "starting audio thread";
	
  	out = open("/dev/dsp",O_WRONLY);
	if( out < 0) { qDebug() << "opening /dev/dsp failed"; }
	
	int arg = 0x00080008;
	ioctl(out,SNDCTL_DSP_SETFRAGMENT,&arg);
	c=16; /* 16 bits */
	ioctl(out,SOUND_PCM_WRITE_BITS,&c);
	c=1;  /* 1 channel */
	ioctl(out,SOUND_PCM_WRITE_CHANNELS,&c);
	c=44100; /* 44.1KHz */
	ioctl(out,SOUND_PCM_WRITE_RATE,&c);

	c = 0;
	int i = -1;
	QHash<QString, WaveForm *>::const_iterator j;
	while(1)
	{
		temp = 0;
		mutex.lock();
		for (j = wf.begin(); j != wf.end(); ++j)
		{
			temp += (short)(j.value()->nextSample());
		}
		usleep(1);
		mutex.unlock();
		write(out, &temp, sizeof(short));
//		ioctl(out,SNDCTL_DSP_SYNC);
	}

	close(out);
	exit();
}

void AudioThread::caughtAdd()
{
	cout << "Wave Added!!!!!" << endl;
}


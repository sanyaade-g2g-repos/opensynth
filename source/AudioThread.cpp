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
using namespace std;

AudioThread::AudioThread(QObject *parent, map<QString, WaveForm *> & wfs)
	: QThread(parent), wf(wfs), playflag(true)
{
}

void AudioThread::run()
{
	int c,out;
	short temp;
	qDebug() << "starting audio thread";
	
  	out = open("/dev/dsp",O_WRONLY);
	if( out < 0) { qDebug() << "opening /dev/dsp failed"; }
	
	int arg = 0x00100008; 			//These are the magic lines that fixed the delay
	ioctl(out,SNDCTL_DSP_SETFRAGMENT,&arg); //and stopped most of my frustration. They simply
						//set bounds on the buffering for the soundcard.

	c=16; /* 16 bits */
	ioctl(out,SOUND_PCM_WRITE_BITS,&c);
	c=1;  /* 1 channel */
	ioctl(out,SOUND_PCM_WRITE_CHANNELS,&c);
	c=44100; /* 44.1KHz */
	ioctl(out,SOUND_PCM_WRITE_RATE,&c);

//	QHash<QString, WaveForm *>::const_iterator j;
	map< QString, WaveForm *>::const_iterator j;
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

void AudioThread::quitIt() { mutex.lock(); playflag = false; mutex.unlock(); }


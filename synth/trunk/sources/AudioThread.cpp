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

AudioThread::AudioThread(QObject *parent)
	: QThread(parent)
{
}

void AudioThread::setBuffer(QHash<QString, WaveForm *> * wf_p, int s, bool * pf)
{
//	ab = ptr;
	wf_ptr = wf_p;
	size = s;
	playflag = pf;
	*playflag = false;
}

void AudioThread::run()
{
	int c,out;
	short temp;
	qDebug() << "starting audio thread";
	
  	out = open("/dev/dsp",O_RDWR);
	if( out < 0) { qDebug() << "opening /dev/dsp failed"; }
	
	c=16; /* 16 bits */
	ioctl(out,SOUND_PCM_WRITE_BITS,&c);
	c=1;  /* 1 channel */
	ioctl(out,SOUND_PCM_WRITE_CHANNELS,&c);
	c=44100; /* 44.1KHz */
	ioctl(out,SOUND_PCM_WRITE_RATE,&c);

//	cout << "buffer size: " << size << endl;
//	cout << "buffer location: " << ab << endl;

//	qDebug() << "about to start rendering...";
//	memset(ab, '\0', sizeof(unsigned short int)*size);
//	QHashIterator<QString, WaveForm *> j((*wf_ptr));
	c = 0;
	while(1)
	{
		if( (*playflag) )
		{
//			qDebug() << "playflag set";
			for( int i = 0; i < size; ++i)
			{
//				qDebug() << wf_ptr->size() << " notes playing";
				if( wf_ptr->size() ) {
					temp = 0;
					foreach (QString str, wf_ptr->keys() ) {
//						qDebug() << str;
						temp += (short)(2000*(sin(wf_ptr->value(str)->frequency * 2 * M_PI * i /44100)));
					}
					write(out, &temp, sizeof(short));
				}
//				temp = 0;
//				while( j.hasNext() ) {
//					j.next();
//					qDebug() << "adding WaveForm with frequency " << j.value()->getFreq();
//					temp += (short)(2000*(sin(j.value()->getFreq() * 2 * M_PI * i /44100)));
//				}
//				write(out, &temp, sizeof(short));
			}
		}
		else {
			usleep(10);
		}
	}

	close(out);
	exit();
}


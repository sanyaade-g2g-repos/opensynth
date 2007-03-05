#include "AudioThread.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/soundcard.h>
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

#define FADEBUF 5

AudioThread::AudioThread(QObject *parent)
	: QThread(parent)
{
}

void AudioThread::setBuffer(short * ptr, int s, bool * pf)
{
	ab = ptr;
	size = s;
	playflag = pf;
	*playflag = false;
}

void AudioThread::run()
{
	int c,out,result;
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
	memset(ab, '\0', sizeof(unsigned short int)*size);
	while(1)
	{
		if( !(*playflag) )
			usleep(100);
		else {
			for( c = 0; c < size; ++c )
			{
				if( c <= FADEBUF ) {
					temp = (ab[c] * c / FADEBUF);
		//			cout << "fadein: ab[c]: " << ab[c] << " temp: " << temp << endl;
					write(out, &temp, sizeof(short));
				} else if ( (size - c - 1) <= FADEBUF ) {
					temp = (ab[c] * (size - c - 1) / FADEBUF);
		//			cout << "fadeout: ab[c]: " << ab[c] << " temp: " << temp << endl;
					write(out, &temp, sizeof(short));
				} else {
	//				temp = ( ab[(c-1)%size] + ab[c%size] + ab[(c+1)%size] ) / 3;
					result = write(out, ab+c, sizeof(short));
				}
			}
//			cout << "result: " << result << endl;
		}
	}

	close(out);
	exit();
}


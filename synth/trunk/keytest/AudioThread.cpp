#include "AudioThread.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/soundcard.h>
#include <iostream>
using std::cout;
using std::endl;

AudioThread::AudioThread(QObject *parent)
	: QThread(parent)
{
}

void AudioThread::setBuffer(unsigned short int * ptr, int s, bool * pf)
{
	ab = ptr;
	size = s;
	playflag = pf;
	*playflag = false;
}

void AudioThread::run()
{
	int c,out,result;
	qDebug() << "starting audio thread";
	
  	out = open("/dev/dsp",O_RDWR);
	if( out < 0) { qDebug() << "opening /dev/dsp failed"; }
	
	c=16; /* 16 bits */
	ioctl(out,SOUND_PCM_WRITE_BITS,&c);
	c=1;  /* 1 channel */
	ioctl(out,SOUND_PCM_WRITE_CHANNELS,&c);
	c=44100; /* 44.1KHz */

	cout << "buffer size: " << size << endl;
	cout << "buffer location: " << ab << endl;

	qDebug() << "about to start rendering...";
	memset(ab, '\0', sizeof(unsigned short int)*size);
	while(1)
	{
		if( !(*playflag) )
			usleep(100);
		else {
		       cout << "about to start playing..." << endl;	
			result = write(out, ab, sizeof(unsigned short int)*size);
			cout << "result: " << result << endl;
		//	for( int i = 0; i < size; ++i )
		//		write(out, (char*)(audiobuffer+i), sizeof(audiobuffer));
				//cout << audiobuffer[i] << " ";
		}
	}
//	while(1){
//	for( int i = 0; i < size; ++i )
//		cout << audiobuffer[i] << " ";
//	}
	close(out);
	exit();
}


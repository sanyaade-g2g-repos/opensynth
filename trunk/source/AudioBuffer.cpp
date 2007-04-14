#include "AudioBuffer.h"
#include <sys/time.h>
#include <iostream>
using namespace std;

AudioBuffer::AudioBuffer()
{
	playflag = new bool;
	*playflag = false;
	playthread = new AudioThread(this, currentNotes);
	playthread->setBuffer(1000, playflag);
	playthread->start();

//	connect(this, SIGNAL(addedWave()), playthread, SLOT(caughtAdd()));
}

AudioBuffer::~AudioBuffer()
{
	delete playflag;
	playthread->exit();
}

void AudioBuffer::add(WaveForm * wf)
{
//	struct timeval tv;
//	gettimeofday(&tv, NULL);
//	cout << "added wave to hash at sec: " << tv.tv_sec << "  usec: " << tv.tv_usec << endl;
	if( !currentNotes.contains(wf->name) )
		currentNotes.insert(wf->name, wf);
}

void AudioBuffer::remove(QString wfn)
{
	if( currentNotes.contains(wfn) )
	{
		delete currentNotes[wfn];
		currentNotes.remove(wfn);
	}
}


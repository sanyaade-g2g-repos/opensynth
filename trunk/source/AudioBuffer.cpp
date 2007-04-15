#include "AudioBuffer.h"
#include <iostream>
using namespace std;

AudioBuffer::AudioBuffer()
{
//	playflag = new bool;
//	*playflag = false;
	playthread = new AudioThread(this, currentNotes);
//	playthread->setBuffer(1000, playflag);
	playthread->start();

	connect(this, SIGNAL(closePlay()), playthread, SLOT(quitIt()));
}

AudioBuffer::~AudioBuffer()
{
//	delete playflag;
	emit closePlay();
	playthread->exit();
}

void AudioBuffer::add(WaveForm * wf)
{
	if( !currentNotes.contains(wf->name) )
		currentNotes.insert(wf->name, wf);
}

void AudioBuffer::remove(QString wfn)
{
	if( currentNotes.contains(wfn) )
	{
		while( !currentNotes[wfn]->released() ) {usleep(100);}
		delete currentNotes[wfn];
		currentNotes.remove(wfn);
	}
}


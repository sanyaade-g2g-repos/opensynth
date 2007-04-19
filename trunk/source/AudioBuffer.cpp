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
	if( currentNotes.end() != currentNotes.find(wf->name) ) {
		currentNotes.erase(wf->name);
		delete currentNotes[wf->name];
	}

	currentNotes[wf->name] = wf;
	connect(wf, SIGNAL(finished(QString)), 
			this, SLOT(deleteWave(QString)));
}

void AudioBuffer::remove(QString wfn)
{
	if( currentNotes.end() != currentNotes.find(wfn) )
	{
		currentNotes[wfn]->releaseIt();
//		while( !currentNotes[wfn]->isReleased() ) { usleep(100); }
//		delete currentNotes[wfn];
//		currentNotes.remove(wfn);
	}
}

void AudioBuffer::deleteWave(QString n)
{
	if( currentNotes.end() != currentNotes.find(n)) {
		mutex.lock();
		delete currentNotes[n];
		currentNotes.erase(n);
		mutex.unlock();
//		cout << "deleted! current size: " << currentNotes.size() << endl;
	}
}


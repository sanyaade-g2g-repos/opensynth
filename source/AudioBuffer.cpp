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
	if( !currentNotes.contains(wf->name) ) {
//		mutex.lock();
		currentNotes.insert(wf->name, wf);
//		mutex.unlock();
		connect(currentNotes[wf->name], SIGNAL(finished(QString)), 
				this, SLOT(deleteWave(QString)));
	}
}

void AudioBuffer::remove(QString wfn)
{
	if( currentNotes.contains(wfn) )
	{
		currentNotes[wfn]->releaseIt();
//		while( !currentNotes[wfn]->isReleased() ) { usleep(100); }
//		delete currentNotes[wfn];
//		currentNotes.remove(wfn);
	}
}

void AudioBuffer::deleteWave(QString n)
{
	if( currentNotes.contains(n)) {
		mutex.lock();
		delete currentNotes[n];
		currentNotes.remove(n);
		mutex.unlock();
//		cout << "deleted! current size: " << currentNotes.size() << endl;
	}
}


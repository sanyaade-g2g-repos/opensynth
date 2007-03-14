#include "AudioBuffer.h"

AudioBuffer::AudioBuffer()
{
	playflag = new bool;
	*playflag = false;
	playthread = new AudioThread(this, currentNotes);
	playthread->setBuffer(1000, playflag);
	playthread->start();
}

AudioBuffer::~AudioBuffer()
{
	delete playflag;
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
		delete currentNotes[wfn];
		currentNotes.remove(wfn);
	}
}


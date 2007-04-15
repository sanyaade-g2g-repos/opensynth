#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include "AudioThread.h"
#include <QObject>

class AudioBuffer:public QObject
{
	Q_OBJECT
	public:
		AudioBuffer();
		~AudioBuffer();
		void add(WaveForm *);
		void remove(QString);
	
	signals:
		void closePlay(void);

	private:
		QHash<QString, WaveForm *> currentNotes;
	//	bool * playflag;
		AudioThread * playthread;


};

#endif

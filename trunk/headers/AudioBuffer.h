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
	
	public slots:
		void deleteWave(QString);

	signals:
		void closePlay(void);

	private:
		QMutex mutex;
		QHash<QString, WaveForm *> currentNotes;
	//	bool * playflag;
		AudioThread * playthread;


};

#endif

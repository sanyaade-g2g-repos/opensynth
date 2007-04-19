#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include "AudioThread.h"
#include <QObject>
#include <map>
using namespace std;

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
		map< QString, WaveForm * > currentNotes;
//		QHash<QString, WaveForm *> currentNotes;
	//	bool * playflag;
		AudioThread * playthread;


};

#endif

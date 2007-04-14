#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QtGui>
#include <QHash>
#include <WaveForm.h>

class AudioThread : public QThread
{
	Q_OBJECT
	public:
		AudioThread(QObject *parent, QHash<QString, WaveForm *> & waveforms);
		void run();
		void setBuffer( int s, bool * play);

	public slots:
		void caughtAdd(void);

	private:
//		short * ab;
		QMutex mutex;
		QHash<QString, WaveForm *> & wf;
		int size;
		bool * playflag;
};

#endif

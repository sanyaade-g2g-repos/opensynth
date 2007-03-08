#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QtGui>
#include <QHash>
#include <WaveForm.h>

class AudioThread : public QThread
{
	Q_OBJECT
	public:
		AudioThread(QObject *parent);
		void run();
		void setBuffer(QHash<QString, WaveForm *> * wf_ptr, int s, bool * play);
	private:
//		short * ab;
		QHash<QString, WaveForm *> * wf_ptr;
		int size;
		bool * playflag;
};

#endif

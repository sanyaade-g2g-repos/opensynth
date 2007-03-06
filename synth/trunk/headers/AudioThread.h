#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QtGui>

class AudioThread : public QThread
{
	Q_OBJECT
	public:
		AudioThread(QObject *parent);
		void run();
		void setBuffer(short * ab, int size, bool * play);
	private:
		short * ab;
		int size;
		bool * playflag;
};

#endif

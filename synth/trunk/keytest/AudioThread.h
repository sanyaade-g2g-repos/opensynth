#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QtGui>

class AudioThread : public QThread
{
	Q_OBJECT
	public:
		AudioThread(QObject *parent);
		void run();
		void setBuffer(unsigned short int *, int, bool *);
	private:
		unsigned short int * ab;
		int size;
		bool * playflag;
};

#endif

#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QtGui>
#include <QHash>
#include <WaveForm.h>
#include <map>
using namespace std;

class AudioThread : public QThread
{
	Q_OBJECT
	public:
		AudioThread(QObject *parent, map<QString, WaveForm *> & wfs);
		void run();

	public slots:
		void quitIt(void);

	private:
		QMutex mutex;
		//QHash<QString, WaveForm *> & wf;
		map< QString, WaveForm * > & wf;
		int size;
		bool playflag;
};

#endif

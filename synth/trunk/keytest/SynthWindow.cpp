

#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <cmath>
using namespace std;

#include "SynthWindow.h"
#include "Note.h"
#include "AudioThread.h"

SynthWindow::SynthWindow()
{
	playflag = new bool;
	playthread = new AudioThread(this);
	playthread->setBuffer(audiobuffer, AUDBUFLEN, playflag);
	playthread->start();
}

void SynthWindow::keyPressEvent( QKeyEvent *event )
{
	if( !event->isAutoRepeat() ) {

	int key = event->key();
	bool got_one = false;

	if( key ==  Qt::Key_A ) {
		cout << " Ab ";
		got_one = true;
		if( !currentNotes.contains("A,2,-1") )
			currentNotes["A,2,-1"] = new Note('A',2,-1);
	}
	if( key == Qt::Key_Z ) {
		cout << " A ";
		got_one = true;
	}
	if( key == Qt::Key_S ) {
		cout << " Bb ";
		got_one = true;
	}
	if( key == Qt::Key_X ) {
		cout << " B ";
		got_one = true;
	}
	if( key == Qt::Key_C ) {
		cout << " C ";
		got_one = true;
	}
	if( key == Qt::Key_F ) {
		cout << " C# ";
		got_one = true;
	}
	if( key == Qt::Key_V ) {
		cout << " D ";
		got_one = true;
	}
	if( key == Qt::Key_G ) {
		cout << " D# ";
		got_one = true;
	}
	if( key == Qt::Key_B ) {
		cout << " E ";
		got_one = true;
	}
	if( !got_one )
		QWidget::keyPressEvent(event);
	cout.flush();

	memset(audiobuffer, '\0', sizeof(short)*AUDBUFLEN);
	QHashIterator<QString, Note *> j(currentNotes);
	qDebug() << "audiobuffer in window: " << audiobuffer << "with length: " << AUDBUFLEN << endl;
	while( j.hasNext() ) {
		j.next();
		for( int i = 0; i < AUDBUFLEN; i++ ){
			audiobuffer[i] = 8000*sin(220*2*M_PI*i/44100);
//			audiobuffer[i] += (short)(8000*sin( j.value()->getFreq() * 2 * M_PI * i / 44100 ));
//			qDebug() << audiobuffer[i];
		}
		qDebug() << "added " << j.key() << " to audiobuffer (with freq:" << j.value()->getFreq() << endl;
		*playflag = true;
	}
	}
}
//void keyReleaseEvent( QKeyEvent *event ){};



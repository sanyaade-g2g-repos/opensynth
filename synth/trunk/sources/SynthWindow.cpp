
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
		if( !currentNotes.contains("A,3,-1") )
			currentNotes["A,3,-1"] = new Note('A',3,-1);
	}
	if( key == Qt::Key_Z ) {
		cout << " A ";
		got_one = true;
		if( !currentNotes.contains("A,3,0") )
			currentNotes["A,3,0"] = new Note('A',3,0);
	}
	if( key == Qt::Key_S ) {
		cout << " Bb ";
		got_one = true;
		if( !currentNotes.contains("B,3,-1") )
			currentNotes["B,3,-1"] = new Note('B',3,-1);
	}
	if( key == Qt::Key_X ) {
		cout << " B ";
		got_one = true;
		if( !currentNotes.contains("B,3,0") )
			currentNotes["B,3,0"] = new Note('B',3,0);
	}
	if( key == Qt::Key_C ) {
		cout << " C ";
		got_one = true;
		if( !currentNotes.contains("C,4,0") )
			currentNotes["C,4,0"] = new Note('C',4,0);
	}
	if( key == Qt::Key_F ) {
		cout << " C# ";
		got_one = true;
		if( !currentNotes.contains("C,4,1") )
			currentNotes["C,4,1"] = new Note('C',4,1);
	}
	if( key == Qt::Key_V ) {
		cout << " D ";
		got_one = true;
		if( !currentNotes.contains("D,4,0") )
			currentNotes["D,4,0"] = new Note('D',4,0);
	}
	if( key == Qt::Key_G ) {
		cout << " D# ";
		got_one = true;
		if( !currentNotes.contains("D,4,1") )
			currentNotes["D,4,1"] = new Note('D',4,1);
	}
	if( key == Qt::Key_B ) {
		cout << " E ";
		got_one = true;
		if( !currentNotes.contains("E,4,0") )
			currentNotes["E,4,0"] = new Note('E',4,0);
	}
	if( key == Qt::Key_N ) {
		cout << " F ";
		got_one = true;
		if( !currentNotes.contains("F,4,0") )
			currentNotes["F,4,0"] = new Note('F',4,0);
	}
	if( key == Qt::Key_J ) {
		cout << " F# ";
		got_one = true;
		if( !currentNotes.contains("F,4,1") )
			currentNotes["F,4,1"] = new Note('F',4,1);
	}
	if( key == Qt::Key_M ) {
		cout << " G ";
		got_one = true;
		if( !currentNotes.contains("G,4,0") )
			currentNotes["G,4,0"] = new Note('G',4,0);
	}
	if( key == Qt::Key_K ) {
		cout << " G# ";
		got_one = true;
		if( !currentNotes.contains("G,4,1") )
			currentNotes["G,4,1"] = new Note('G',4,1);
	}
	if( key == Qt::Key_Comma ) {
		cout << " A ";
		got_one = true;
		if( !currentNotes.contains("A,4,0") )
			currentNotes["A,4,0"] = new Note('A',4,0);
	}
	

	cout.flush();
	if( !got_one )
		QWidget::keyPressEvent(event);
	else {
		if( !currentNotes.empty() ) {
	//		memset(audiobuffer, '\0', sizeof(short)*AUDBUFLEN);
			QHashIterator<QString, Note *> j(currentNotes);
//			qDebug() << "audiobuffer in window: " << audiobuffer << "with length: " << AUDBUFLEN << endl;
			while( j.hasNext() ) {
				j.next();
				for( int i = 0; i < AUDBUFLEN; i++ ){
					audiobuffer[i] += (8000*sin( (short)(j.value()->getFreq()) * 2 * M_PI * i / 44100 ));
				}
//				qDebug() << "added " << j.key() << " to audiobuffer (with freq:" << j.value()->getFreq() << ")" << endl;
				*playflag = true;
			}
		} else {
			*playflag = false;
			memset(audiobuffer, '\0', sizeof(short)*AUDBUFLEN);
		}
	}

	}
}

void SynthWindow::keyReleaseEvent( QKeyEvent *event )
{
	int key = event->key();
	bool got_one = false;

	if( !event->isAutoRepeat() ) {
	//	cout << "key release" << endl;

	if( key ==  Qt::Key_A ) {
		cout << " Ab ";
		got_one = true;
		currentNotes.remove("A,3,-1");
	}
	if( key == Qt::Key_Z ) {
		cout << " A ";
		got_one = true;
		currentNotes.remove("A,3,0");
	}
	if( key == Qt::Key_S ) {
		cout << " Bb ";
		got_one = true;
		currentNotes.remove("B,3,-1");
	}
	if( key == Qt::Key_X ) {
		cout << " B ";
		got_one = true;
		currentNotes.remove("B,3,0");
	}
	if( key == Qt::Key_C ) {
		cout << " C ";
		got_one = true;
		currentNotes.remove("C,4,0");
	}
	if( key == Qt::Key_F ) {
		cout << " C# ";
		got_one = true;
		currentNotes.remove("C,4,1");
	}
	if( key == Qt::Key_V ) {
		cout << " D ";
		got_one = true;
		currentNotes.remove("D,4,0");
	}
	if( key == Qt::Key_G ) {
		cout << " D# ";
		got_one = true;
		currentNotes.remove("D,4,1");
	}
	if( key == Qt::Key_B ) {
		cout << " E ";
		got_one = true;
		currentNotes.remove("E,4,0");
	}
	if( key == Qt::Key_N ) {
		cout << " F ";
		got_one = true;
		currentNotes.remove("F,4,0");
	}
	if( key == Qt::Key_J ) {
		cout << " F# ";
		got_one = true;
		currentNotes.remove("F,4,1");
	}
	if( key == Qt::Key_M ) {
		cout << " G ";
		got_one = true;
		currentNotes.remove("G,4,0");
	}
	if( key == Qt::Key_K ) {
		cout << " G# ";
		got_one = true;
		currentNotes.remove("G,4,1");
	}
	if( key == Qt::Key_Comma ) {
		cout << " A ";
		got_one = true;
		currentNotes.remove("A,4,0");
	}
	cout.flush();
	if( !got_one )
		QWidget::keyPressEvent(event);
	else {
		if( !currentNotes.empty()) {

			memset(audiobuffer, '\0', sizeof(short)*AUDBUFLEN);
			QHashIterator<QString, Note *> j(currentNotes);
		//	qDebug() << "audiobuffer in window: " << audiobuffer << "with length: " << AUDBUFLEN << endl;
			while( j.hasNext() ) {
				j.next();
				for( int i = 0; i < AUDBUFLEN; i++ ){
					audiobuffer[i] += (8000*sin( (short)(j.value()->getFreq()) * 2 * M_PI * i / 44100 ));
				}
		//		qDebug() << "added " << j.key() << " to audiobuffer (with freq:" << j.value()->getFreq() << ")" << endl;
				*playflag = true;
			}
		} else {
			*playflag = false;
			memset(audiobuffer, '\0', sizeof(short)*AUDBUFLEN);
		}

	}

	}
}




#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <cmath>
using namespace std;

#include "SynthWindow.h"
#include "Note.h"
#include "AudioThread.h"
#include "AudioBuffer.h"

float freq(char pitch, int octave, int alter);

SynthWindow::SynthWindow()
{
	playflag = new bool;
//	playthread = new AudioThread(this);
//	playthread->setBuffer(audiobuffer, AUDBUFLEN, playflag);
//	playthread->start();
}

void SynthWindow::keyPressEvent( QKeyEvent *event )
{
	if( !event->isAutoRepeat() ) {

	int key = event->key();
	bool got_one = false;

	if( key ==  Qt::Key_A ) {
		cout << " Ab ";
		got_one = true;
		ab.add(new WaveForm("A,3,-1", (int)(freq('A',3,-1))));
	}
	if( key == Qt::Key_Z ) {
		cout << " A ";
		got_one = true;
		ab.add(new WaveForm("A,3,0", (int)(freq('A',3,0))));
	}
	if( key == Qt::Key_S ) {
		cout << " Bb ";
		got_one = true;
		ab.add(new WaveForm("B,3,-1", (int)(freq('B',3,-1))));
	}
	if( key == Qt::Key_X ) {
		cout << " B ";
		got_one = true;
		ab.add(new WaveForm("B,3,0", (int)(freq('B',3,0))));
	}
	if( key == Qt::Key_C ) {
		cout << " C ";
		got_one = true;
		ab.add(new WaveForm("C,4,0", (int)(freq('C',4,0))));
	}
	if( key == Qt::Key_F ) {
		cout << " C# ";
		got_one = true;
		ab.add(new WaveForm("C,4,1", (int)(freq('C',4,1))));
	}
	if( key == Qt::Key_V ) {
		cout << " D ";
		got_one = true;
		ab.add(new WaveForm("D,4,0", (int)(freq('D',4,0))));
	}
	if( key == Qt::Key_G ) {
		cout << " D# ";
		got_one = true;
		ab.add(new WaveForm("D,4,1", (int)(freq('D',4,1))));
	}
	if( key == Qt::Key_B ) {
		cout << " E ";
		got_one = true;
		ab.add(new WaveForm("E,4,0", (int)(freq('E',4,0))));
	}
	if( key == Qt::Key_N ) {
		cout << " F ";
		got_one = true;
		ab.add(new WaveForm("F,4,0", (int)(freq('F',4,0))));
	}
	if( key == Qt::Key_J ) {
		cout << " F# ";
		got_one = true;
		ab.add(new WaveForm("F,4,1", (int)(freq('F',4,1))));
	}
	if( key == Qt::Key_M ) {
		cout << " G ";
		got_one = true;
		ab.add(new WaveForm("G,4,0", (int)(freq('G',4,0))));
	}
	if( key == Qt::Key_K ) {
		cout << " G# ";
		got_one = true;
		ab.add(new WaveForm("G,4,1", (int)(freq('G',4,1))));
	}
	if( key == Qt::Key_Comma ) {
		cout << " A ";
		got_one = true;
		ab.add(new WaveForm("A,4,0", (int)(freq('A',4,0))));
	}
	

	cout.flush();
	if( !got_one )
		QWidget::keyPressEvent(event);

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
		ab.remove("A,3,-1");
	}
	if( key == Qt::Key_Z ) {
		cout << " A ";
		got_one = true;
		ab.remove("A,3,0");
		//currentNotes.remove("A,3,0");
	}
	if( key == Qt::Key_S ) {
		cout << " Bb ";
		got_one = true;
		ab.remove("B,3,-1");
	}
	if( key == Qt::Key_X ) {
		cout << " B ";
		got_one = true;
		ab.remove("B,3,0");
	}
	if( key == Qt::Key_C ) {
		cout << " C ";
		got_one = true;
		ab.remove("C,4,0");
	}
	if( key == Qt::Key_F ) {
		cout << " C# ";
		got_one = true;
		ab.remove("C,4,1");
	}
	if( key == Qt::Key_V ) {
		cout << " D ";
		got_one = true;
		ab.remove("D,4,0");
	}
	if( key == Qt::Key_G ) {
		cout << " D# ";
		got_one = true;
		ab.remove("D,4,1");
	}
	if( key == Qt::Key_B ) {
		cout << " E ";
		got_one = true;
		ab.remove("E,4,0");
	}
	if( key == Qt::Key_N ) {
		cout << " F ";
		got_one = true;
		ab.remove("F,4,0");
	}
	if( key == Qt::Key_J ) {
		cout << " F# ";
		got_one = true;
		ab.remove("F,4,1");
	}
	if( key == Qt::Key_M ) {
		cout << " G ";
		got_one = true;
		ab.remove("G,4,0");
	}
	if( key == Qt::Key_K ) {
		cout << " G# ";
		got_one = true;
		ab.remove("G,4,1");
	}
	if( key == Qt::Key_Comma ) {
		cout << " A ";
		got_one = true;
		ab.remove("A,4,0");
	}
	cout.flush();
	if( !got_one )
		QWidget::keyPressEvent(event);

	}
}



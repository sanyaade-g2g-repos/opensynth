
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

	switch (key)
	{
		case Qt::Key_A:
//		cout << " Ab ";
		ab.add(new WaveForm("A,3,-1", (int)(freq('A',3,-1))));
		break;

		case Qt::Key_Z:
//		cout << " A ";
		ab.add(new WaveForm("A,3,0", (int)(freq('A',3,0))));
		break;

		case Qt::Key_S:
//		cout << " Bb ";
		ab.add(new WaveForm("B,3,-1", (int)(freq('B',3,-1))));
		break;

		case Qt::Key_X:
//		cout << " B ";
		ab.add(new WaveForm("B,3,0", (int)(freq('B',3,0))));
		break;

		case Qt::Key_C:
//		cout << " C ";
		ab.add(new WaveForm("C,4,0", (int)(freq('C',4,0))));
		break;

		case Qt::Key_F:
//		cout << " C# ";
		ab.add(new WaveForm("C,4,1", (int)(freq('C',4,1))));
		break;

		case Qt::Key_V:
//		cout << " D ";
		ab.add(new WaveForm("D,4,0", (int)(freq('D',4,0))));
		break;

		case Qt::Key_G:
//		cout << " D# ";
		ab.add(new WaveForm("D,4,1", (int)(freq('D',4,1))));
		break;

		case Qt::Key_B:
//		cout << " E ";
		ab.add(new WaveForm("E,4,0", (int)(freq('E',4,0))));
		break;

		case Qt::Key_N:
//		cout << " F ";
		ab.add(new WaveForm("F,4,0", (int)(freq('F',4,0))));
		break;

		case Qt::Key_J:
//		cout << " F# ";
		ab.add(new WaveForm("F,4,1", (int)(freq('F',4,1))));
		break;

		case Qt::Key_M:
//		cout << " G ";
		ab.add(new WaveForm("G,4,0", (int)(freq('G',4,0))));
		break;

		case Qt::Key_K:
//		cout << " G# ";
		ab.add(new WaveForm("G,4,1", (int)(freq('G',4,1))));
		break;

		case Qt::Key_Comma:
//		cout << " A ";
		ab.add(new WaveForm("A,4,0", (int)(freq('A',4,0))));
		break;
		
		default:
		QWidget::keyPressEvent(event);

	}
//	cout.flush();

	}
}

void SynthWindow::keyReleaseEvent( QKeyEvent *event )
{
	int key = event->key();

	if( !event->isAutoRepeat() ) {
	//	cout << "key release" << endl;

	switch ( key )
	{
		case Qt::Key_A:
//		cout << " Ab ";
		ab.remove("A,3,-1");
		break;

		case Qt::Key_Z:
//		cout << " A ";
		ab.remove("A,3,0");
		break;

		case Qt::Key_S:
//		cout << " Bb ";
		ab.remove("B,3,-1");
		break;

		case Qt::Key_X:
//		cout << " B ";
		ab.remove("B,3,0");
		break;

		case Qt::Key_C:
//		cout << " C ";
		ab.remove("C,4,0");
		break;

		case Qt::Key_F:
//		cout << " C# ";
		ab.remove("C,4,1");
		break;

		case Qt::Key_V:
//		cout << " D ";
		ab.remove("D,4,0");
		break;

		case Qt::Key_G:
//		cout << " D# ";
		ab.remove("D,4,1");
		break;

		case Qt::Key_B:
//		cout << " E ";
		ab.remove("E,4,0");
		break;

		case Qt::Key_N:
//		cout << " F ";
		ab.remove("F,4,0");
		break;

		case Qt::Key_J:
//		cout << " F# ";
		ab.remove("F,4,1");
		break;

		case Qt::Key_M:
//		cout << " G ";
		ab.remove("G,4,0");
		break;

		case Qt::Key_K:
//		cout << " G# ";
		ab.remove("G,4,1");
		break;

		case Qt::Key_Comma:
//		cout << " A ";
		ab.remove("A,4,0");
		break;

		default:
		QWidget::keyPressEvent(event);
	}
//	cout.flush();

	}
}



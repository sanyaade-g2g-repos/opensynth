
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <cmath>
using namespace std;

#include "SynthWindow.h"
#include "AudioThread.h"
#include "AudioBuffer.h"

float freq(char pitch, int octave, int alter);

SynthWindow::SynthWindow()
{
	wt = SIN;
	a = 25;
	d = 75;
	r = 25;
	s = 75;
	o = 3;

	wavelayout = new QVBoxLayout;
	wholelayout = new QHBoxLayout;

	sinebutton = new QRadioButton("&Sine", this);
	squarebutton = new QRadioButton("S&quare", this);
	trianglebutton = new QRadioButton("&Triangle", this);
	sawbutton = new QRadioButton("Sa&w", this);

	lwaves = new QLabel("Waveforms", this);
	lwaves->setAlignment(Qt::AlignCenter);
	
	connect(sinebutton, SIGNAL(clicked()), this, SLOT(setSineWave()));
	connect(squarebutton, SIGNAL(clicked()), this, SLOT(setSquareWave()));
	connect(trianglebutton, SIGNAL(clicked()), this, SLOT(setTriangleWave()));
	connect(sawbutton, SIGNAL(clicked()), this, SLOT(setSawWave()));

	voctave = new QVBoxLayout;
	oct1 = new QRadioButton("1", this);
	oct2 = new QRadioButton("2", this);
	oct3 = new QRadioButton("3", this);
	oct3->setChecked(true);
	oct4 = new QRadioButton("4", this);

	loctave = new QLabel("Octave", this);
	loctave->setAlignment(Qt::AlignCenter);

	connect(oct1, SIGNAL(clicked()), this, SLOT(setOctave1()));
	connect(oct2, SIGNAL(clicked()), this, SLOT(setOctave2()));
	connect(oct3, SIGNAL(clicked()), this, SLOT(setOctave3()));
	connect(oct4, SIGNAL(clicked()), this, SLOT(setOctave4()));

	voctave->addWidget(loctave);
	voctave->addWidget(oct1);
	voctave->addWidget(oct2);
	voctave->addWidget(oct3);
	voctave->addWidget(oct4);

	octgroup = new QButtonGroup;

	octgroup->addButton(oct1);
	octgroup->addButton(oct2);
	octgroup->addButton(oct3);
	octgroup->addButton(oct4);

	sinebutton->setChecked(true);
	
	attack = new QDial(this);
	attack->setNotchesVisible(true);
	attack->setValue(a);

	decay = new QDial(this);
	decay->setNotchesVisible(true);
	decay->setValue(d);

	release = new QDial(this);
	release->setNotchesVisible(true);
	release->setValue(r);

	sustain = new QDial(this);
	sustain->setNotchesVisible(true);
	sustain->setValue(s);

	attack->setMinimum(0);
	decay->setMinimum(0);
	release->setMinimum(0);
	sustain->setMinimum(0);

	attack->setMaximum(1000);
	decay->setMaximum(1000);
	release->setMaximum(1000);
	sustain->setMaximum(100);

	attack->setSingleStep(10);
	decay->setSingleStep(10);
	release->setSingleStep(10);
	sustain->setSingleStep(5);

	connect(attack, SIGNAL(valueChanged(int)), this, SLOT(setAttack(int)));
	connect(decay, SIGNAL(valueChanged(int)), this, SLOT(setDecay(int)));
	connect(release, SIGNAL(valueChanged(int)), this, SLOT(setRelease(int)));
	connect(sustain, SIGNAL(valueChanged(int)), this, SLOT(setSustain(int)));

	lattack = new QLabel("Attack",this);
	lattack->setAlignment(Qt::AlignCenter);
	ldecay = new QLabel("Decay",this);
	ldecay->setAlignment(Qt::AlignCenter);
	lrelease = new QLabel("Release",this);
	lrelease->setAlignment(Qt::AlignCenter);
	lsustain = new QLabel("Sustain",this);
	lsustain->setAlignment(Qt::AlignCenter);

	vattack = new QVBoxLayout;
	vdecay = new QVBoxLayout;
	vrelease = new QVBoxLayout;
	vsustain = new QVBoxLayout;

	wavelayout->addWidget(lwaves);
	wavelayout->addWidget(sinebutton);
	wavelayout->addWidget(squarebutton);
	wavelayout->addWidget(trianglebutton);
	wavelayout->addWidget(sawbutton);
	wholelayout->addLayout(wavelayout);

	wholelayout->addLayout(voctave);

	vattack->addWidget(lattack);
	vattack->addWidget(attack);
	wholelayout->addLayout(vattack);

	vdecay->addWidget(ldecay);
	vdecay->addWidget(decay);
	wholelayout->addLayout(vdecay);

	vrelease->addWidget(lrelease);
	vrelease->addWidget(release);
	wholelayout->addLayout(vrelease);

	vsustain->addWidget(lsustain);
	vsustain->addWidget(sustain);
	wholelayout->addLayout(vsustain);

	setLayout(wholelayout);
}

void SynthWindow::setSineWave() { wt = SIN; }
void SynthWindow::setSquareWave() { wt = SQR; }
void SynthWindow::setTriangleWave() { wt = TRI; }
void SynthWindow::setSawWave() { wt = SAW; }

void SynthWindow::setAttack(int aa) { a = aa; }
void SynthWindow::setDecay(int dd) { d = dd; }
void SynthWindow::setRelease(int rr) { r = rr; }
void SynthWindow::setSustain(int ss) { s = ss; }

void SynthWindow::setOctave1() { o = 1; }
void SynthWindow::setOctave2() { o = 2; }
void SynthWindow::setOctave3() { o = 3; }
void SynthWindow::setOctave4() { o = 4; }

void SynthWindow::keyPressEvent( QKeyEvent *event )
{
	if( !event->isAutoRepeat() ) {

	int key = event->key();

	if( event->nativeScanCode() == 62 )
		ab.add(new WaveForm( "D,5,0", (int)(freq('D',o+2,0)), wt, a, d, s, r));
	else if( event->nativeScanCode() == 50 )
		ab.add(new WaveForm( "G,3,0", (int)(freq('G',o,0)), wt, a, d, s, r));

	switch (key)
	{
		case Qt::Key_A:
		ab.add(new WaveForm( "A,3,-1", (int)(freq('A',o,-1)), wt, a, d, s, r));
		break;

		case Qt::Key_Z:
		ab.add(new WaveForm( "A,3,0", (int)(freq('A',o,0)), wt, a, d, s, r));
		break;

		case Qt::Key_S:
		ab.add(new WaveForm( "B,3,-1", (int)(freq('B',o,-1)), wt, a, d, s, r));
		break;

		case Qt::Key_X:
		ab.add(new WaveForm( "B,3,0", (int)(freq('B',o,0)), wt, a, d, s, r));
		break;

		case Qt::Key_C:
		ab.add(new WaveForm( "C,4,0", (int)(freq('C',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_F:
		ab.add(new WaveForm( "C,4,1", (int)(freq('C',o+1,1)), wt, a, d, s, r));
		break;

		case Qt::Key_V:
		ab.add(new WaveForm( "D,4,0", (int)(freq('D',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_G:
		ab.add(new WaveForm( "D,4,1", (int)(freq('D',o+1,1)), wt, a, d, s, r));
		break;

		case Qt::Key_B:
		ab.add(new WaveForm( "E,4,0", (int)(freq('E',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_N:
		ab.add(new WaveForm( "F,4,0", (int)(freq('F',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_J:
		ab.add(new WaveForm( "F,4,1", (int)(freq('F',o+1,1)), wt, a, d, s, r));
		break;

		case Qt::Key_M:
		ab.add(new WaveForm( "G,4,0", (int)(freq('G',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_K:
		ab.add(new WaveForm( "G,4,1", (int)(freq('G',o+1,1)), wt, a, d, s, r));
		break;

		case Qt::Key_Comma:
		ab.add(new WaveForm( "A,4,0", (int)(freq('A',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_L:
		ab.add(new WaveForm( "A,4,1", (int)(freq('A',o+1,1)), wt, a, d, s, r));
		break;

		case Qt::Key_Period:
		ab.add(new WaveForm( "B,4,0", (int)(freq('B',o+1,0)), wt, a, d, s, r));
		break;

		case Qt::Key_Slash:
		ab.add(new WaveForm( "C,5,0", (int)(freq('C',o+2,0)), wt, a, d, s, r));
		break;

		case Qt::Key_Apostrophe:
		ab.add(new WaveForm( "C,5,1", (int)(freq('C',o+2,1)), wt, a, d, s, r));
		break;
		
		default:
		QWidget::keyPressEvent(event);

	}

	}
}

void SynthWindow::keyReleaseEvent( QKeyEvent *event )
{
	int key = event->key();

	if( !event->isAutoRepeat() ) {

	if( event->nativeScanCode() == 62 )
		ab.remove( "D,5,0");
	else if( event->nativeScanCode() == 50 )
		ab.remove( "G,3,0");

	switch ( key )
	{
		case Qt::Key_A:
		ab.remove("A,3,-1");
		break;

		case Qt::Key_Z:
		ab.remove("A,3,0");
		break;

		case Qt::Key_S:
		ab.remove("B,3,-1");
		break;

		case Qt::Key_X:
		ab.remove("B,3,0");
		break;

		case Qt::Key_C:
		ab.remove("C,4,0");
		break;

		case Qt::Key_F:
		ab.remove("C,4,1");
		break;

		case Qt::Key_V:
		ab.remove("D,4,0");
		break;

		case Qt::Key_G:
		ab.remove("D,4,1");
		break;

		case Qt::Key_B:
		ab.remove("E,4,0");
		break;

		case Qt::Key_N:
		ab.remove("F,4,0");
		break;

		case Qt::Key_J:
		ab.remove("F,4,1");
		break;

		case Qt::Key_M:
		ab.remove("G,4,0");
		break;

		case Qt::Key_K:
		ab.remove("G,4,1");
		break;

		case Qt::Key_Comma:
		ab.remove("A,4,0");
		break;

		case Qt::Key_L:
		ab.remove("A,4,1");
		break;

		case Qt::Key_Period:
		ab.remove("B,4,0");
		break;

		case Qt::Key_Slash:
		ab.remove("C,5,0");
		break;

		case Qt::Key_Apostrophe:
		ab.remove("C,5,1");
		break;

		default:
		QWidget::keyPressEvent(event);
	}

	}
}



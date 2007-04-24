
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
	wt2 = TRI;
	a = a2 = 25;
	d = d2 = 75;
	r = r2 = 25;
	s = s2 = 75;
	o = o2 = 3;

	wavelayout = new QVBoxLayout;
	wholelayout = new QHBoxLayout;

	//-------------------- Create Waveform Column -------------------//

	lwaves = new QLabel("Waveforms", this);
	lwaves->setAlignment(Qt::AlignCenter);

	sinebutton = new QRadioButton("&Sine", this);
	squarebutton = new QRadioButton("S&quare", this);
	trianglebutton = new QRadioButton("&Triangle", this);
	sawbutton = new QRadioButton("Sa&w", this);

	wavegroup = new QButtonGroup;
	wavegroup->addButton(sinebutton, 1);
	wavegroup->addButton(squarebutton, 2);
	wavegroup->addButton(trianglebutton, 3);
	wavegroup->addButton(sawbutton, 4);

	sinebutton2 = new QRadioButton("&Sine", this);
	squarebutton2 = new QRadioButton("S&quare", this);
	trianglebutton2 = new QRadioButton("&Triangle", this);
	sawbutton2 = new QRadioButton("Sa&w", this);

	wavegroup2 = new QButtonGroup;
	wavegroup2->addButton(sinebutton2, 1);
	wavegroup2->addButton(squarebutton2, 2);
	wavegroup2->addButton(trianglebutton2, 3);
	wavegroup2->addButton(sawbutton2, 4);

	connect(wavegroup, SIGNAL(buttonClicked(int)), this, SLOT(setWave1(int)));
	connect(wavegroup2, SIGNAL(buttonClicked(int)), this, SLOT(setWave2(int)));

	//-------------------- Create Octave Column ---------------------//
	
	loctave = new QLabel("Octave", this);
	loctave->setAlignment(Qt::AlignCenter);

	voctave = new QVBoxLayout;
	oct1 = new QRadioButton("1", this);
	oct2 = new QRadioButton("2", this);
	oct3 = new QRadioButton("3", this);
	oct4 = new QRadioButton("4", this);

	octgroup = new QButtonGroup;
	octgroup->addButton(oct1, 1);
	octgroup->addButton(oct2, 2);
	octgroup->addButton(oct3, 3);
	octgroup->addButton(oct4, 4);

	oct12 = new QRadioButton("1", this);
	oct22 = new QRadioButton("2", this);
	oct32 = new QRadioButton("3", this);
	oct42 = new QRadioButton("4", this);

	octgroup2 = new QButtonGroup;
	octgroup2->addButton(oct12, 1);
	octgroup2->addButton(oct22, 2);
	octgroup2->addButton(oct32, 3);
	octgroup2->addButton(oct42, 4);

	connect( octgroup, SIGNAL(buttonClicked(int)), this, SLOT(setOctave1(int)));
	connect( octgroup2, SIGNAL(buttonClicked(int)), this, SLOT(setOctave2(int)));

	voctave->addWidget(loctave);
	voctave->addWidget(oct1);
	voctave->addWidget(oct2);
	voctave->addWidget(oct3);
	voctave->addWidget(oct4);
	voctave->addWidget(oct12);
	voctave->addWidget(oct22);
	voctave->addWidget(oct32);
	voctave->addWidget(oct42);

	//----------------- Set Default Selections ----------------------//

	sinebutton->setChecked(true);
	oct3->setChecked(true);
	trianglebutton2->setChecked(true);
	oct32->setChecked(true);

	//-------------------- Create Dials -----------------------------//
	
	lattack = new QLabel("Attack",this);
	lattack->setAlignment(Qt::AlignCenter);
	ldecay = new QLabel("Decay",this);
	ldecay->setAlignment(Qt::AlignCenter);
	lrelease = new QLabel("Release",this);
	lrelease->setAlignment(Qt::AlignCenter);
	lsustain = new QLabel("Sustain",this);
	lsustain->setAlignment(Qt::AlignCenter);

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

	attack2 = new QDial(this);
	attack2->setNotchesVisible(true);
	attack2->setValue(a2);

	decay2 = new QDial(this);
	decay2->setNotchesVisible(true);
	decay2->setValue(d2);

	release2 = new QDial(this);
	release2->setNotchesVisible(true);
	release2->setValue(r2);

	sustain2 = new QDial(this);
	sustain2->setNotchesVisible(true);
	sustain2->setValue(s2);

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

	attack2->setMinimum(0);
	decay2->setMinimum(0);
	release2->setMinimum(0);
	sustain2->setMinimum(0);

	attack2->setMaximum(1000);
	decay2->setMaximum(1000);
	release2->setMaximum(1000);
	sustain2->setMaximum(100);

	attack2->setSingleStep(10);
	decay2->setSingleStep(10);
	release2->setSingleStep(10);
	sustain2->setSingleStep(5);

	connect(attack2, SIGNAL(valueChanged(int)), this, SLOT(setAttack2(int)));
	connect(decay2, SIGNAL(valueChanged(int)), this, SLOT(setDecay2(int)));
	connect(release2, SIGNAL(valueChanged(int)), this, SLOT(setRelease2(int)));
	connect(sustain2, SIGNAL(valueChanged(int)), this, SLOT(setSustain2(int)));

	vattack = new QVBoxLayout;
	vdecay = new QVBoxLayout;
	vrelease = new QVBoxLayout;
	vsustain = new QVBoxLayout;

	wavelayout->addWidget(lwaves);
	wavelayout->addWidget(sinebutton);
	wavelayout->addWidget(squarebutton);
	wavelayout->addWidget(trianglebutton);
	wavelayout->addWidget(sawbutton);
	wavelayout->addWidget(sinebutton2);
	wavelayout->addWidget(squarebutton2);
	wavelayout->addWidget(trianglebutton2);
	wavelayout->addWidget(sawbutton2);

	wholelayout->addLayout(wavelayout);

	wholelayout->addLayout(voctave);

	vattack->addWidget(lattack);
	vattack->addWidget(attack);
	vattack->addWidget(attack2);
	wholelayout->addLayout(vattack);

	vdecay->addWidget(ldecay);
	vdecay->addWidget(decay);
	vdecay->addWidget(decay2);
	wholelayout->addLayout(vdecay);

	vrelease->addWidget(lrelease);
	vrelease->addWidget(release);
	vrelease->addWidget(release2);
	wholelayout->addLayout(vrelease);

	vsustain->addWidget(lsustain);
	vsustain->addWidget(sustain);
	vsustain->addWidget(sustain2);
	wholelayout->addLayout(vsustain);

	setLayout(wholelayout);
	cout << "reached end of SynthWindow Constructor" << endl;
}

void SynthWindow::setAttack(int aa) { a = aa; }
void SynthWindow::setDecay(int dd) { d = dd; }
void SynthWindow::setRelease(int rr) { r = rr; }
void SynthWindow::setSustain(int ss) { s = ss; }

void SynthWindow::setAttack2(int aa) { a2 = aa; }
void SynthWindow::setDecay2(int dd) { d2 = dd; }
void SynthWindow::setRelease2(int rr) { r2 = rr; }
void SynthWindow::setSustain2(int ss) { s2 = ss; }

void SynthWindow::setOctave1(int oo) { o = oo; }
void SynthWindow::setOctave2(int oo) { o2 = oo; }

void SynthWindow::setWave1(int ww)
{
	switch(ww) {
		case 1:
			wt = SIN;
			break;
		case 2:
			wt = SQR;
			break;
		case 3:
			wt = TRI;
			break;
		case 4:
			wt = SAW;
			break;
		default:
			wt = SIN;
	}
}

void SynthWindow::setWave2(int ww)
{
	switch(ww) {
		case 1:
			wt2 = SIN;
			break;
		case 2:
			wt2 = SQR;
			break;
		case 3:
			wt2 = TRI;
			break;
		case 4:
			wt2 = SAW;
			break;
		default:
			wt2 = SIN;
	}
}

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
		
		case Qt::Key_Q:
		ab.add(new WaveForm( "c,4,0", (int)(freq('C',o2+1,0)), wt2, a2, d2, s2, r2));
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

		case Qt::Key_Q:
		ab.remove("c,4,0");
		break;

		default:
		QWidget::keyPressEvent(event);
	}

	}
}



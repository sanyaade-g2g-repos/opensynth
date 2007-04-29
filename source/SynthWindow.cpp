/** \file SynthWindow.cpp Implementation of the GUI
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file implements the user interface for the virtual synthesizer.
 *   The interface is laid out using box layouts and includes controls
 *   for two separate synthesizer mappings.  These controls include selection
 *   of waveform type (sine, square, triangle, and saw), octave (1-4), and
 *   dials to control the envelope.  Attack, Decay, and Release are timing
 *   values.  They control how long it takes the waveform to go into
 *   the next state.  They have a minimum value of 0 and a maximum of 1 second.
 *   The sustain dial controls what percentage of the maximum value at which
 *   the waveform will sustain.
 * 
 */
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <cmath>
using namespace std;

#include "SynthWindow.h"
#include "AudioThread.h"
#include "AudioBuffer.h"

//declaration for external function freq
float freq(char pitch, int octave, int alter);

/** \brief SynthWindow Constructor for GUI
 * 
 * This function does the grunt work in setting up the interface.  It fact
 *   it does all the work setting up the interface.  It composes the layers
 *   of control into 6 vertical box layouts for waveform, octave, attack, decay,
 *   release and sustain.  Then these 6 layouts are composed into a horizontal layout.
 *   The different radio buttons are also grouped into 4 groups to manage selectivity.
 */
SynthWindow::SynthWindow()
{
	//set initial values for all global variables
	wt = SIN;
	wt2 = TRI;
	a = a2 = 25;
	d = d2 = 75;
	r = r2 = 25;
	s = s2 = 75;
	o = o2 = 3;

	//create horizontal layout to hold everything
	wholelayout = new QHBoxLayout; 

	//-------------------- Create Waveform Column -------------------//

	//create label for top of the column
	lwaves = new QLabel("Waveforms", this);
	lwaves->setAlignment(Qt::AlignCenter);

	//create new vertical layout for the column
	wavelayout = new QVBoxLayout;
	
	//add first group of wave selectors
	sinebutton = new QRadioButton("&Sine", this);
	squarebutton = new QRadioButton("S&quare", this);
	trianglebutton = new QRadioButton("&Triangle", this);
	sawbutton = new QRadioButton("Sa&w", this);

	//put first group into a ButtonGroup
	wavegroup = new QButtonGroup;
	wavegroup->addButton(sinebutton, 1);
	wavegroup->addButton(squarebutton, 2);
	wavegroup->addButton(trianglebutton, 3);
	wavegroup->addButton(sawbutton, 4);

	//add second group of wave selectors
	sinebutton2 = new QRadioButton("&Sine", this);
	squarebutton2 = new QRadioButton("S&quare", this);
	trianglebutton2 = new QRadioButton("&Triangle", this);
	sawbutton2 = new QRadioButton("Sa&w", this);

	//put second group into a ButtonGroup
	wavegroup2 = new QButtonGroup;
	wavegroup2->addButton(sinebutton2, 1);
	wavegroup2->addButton(squarebutton2, 2);
	wavegroup2->addButton(trianglebutton2, 3);
	wavegroup2->addButton(sawbutton2, 4);

	//connect each button group to the slot which sets the waveforms
	connect(wavegroup, SIGNAL(buttonClicked(int)), this, SLOT(setWave1(int)));
	connect(wavegroup2, SIGNAL(buttonClicked(int)), this, SLOT(setWave2(int)));
	
	//put the label and buttons into the wave column layout
	wavelayout->addWidget(lwaves);
	wavelayout->addWidget(sinebutton2);
	wavelayout->addWidget(squarebutton2);
	wavelayout->addWidget(trianglebutton2);
	wavelayout->addWidget(sawbutton2);
	wavelayout->addWidget(sinebutton);
	wavelayout->addWidget(squarebutton);
	wavelayout->addWidget(trianglebutton);
	wavelayout->addWidget(sawbutton);
	
	//add the wave column to the total layout
	wholelayout->addLayout(wavelayout);

	//-------------------- Create Octave Column ---------------------//
	
	//create label for the top of the column
	loctave = new QLabel("Octave", this);
	loctave->setAlignment(Qt::AlignCenter);

	//create new vertical layout for the column
	voctave = new QVBoxLayout;
	
	//add first group of octave selectors
	oct1 = new QRadioButton("1", this);
	oct2 = new QRadioButton("2", this);
	oct3 = new QRadioButton("3", this);
	oct4 = new QRadioButton("4", this);

	//put first group into a ButtonGroup
	octgroup = new QButtonGroup;
	octgroup->addButton(oct1, 1);
	octgroup->addButton(oct2, 2);
	octgroup->addButton(oct3, 3);
	octgroup->addButton(oct4, 4);

	//add second group of octave selectors
	oct12 = new QRadioButton("1", this);
	oct22 = new QRadioButton("2", this);
	oct32 = new QRadioButton("3", this);
	oct42 = new QRadioButton("4", this);

	//put second group into a ButtonGroup
	octgroup2 = new QButtonGroup;
	octgroup2->addButton(oct12, 1);
	octgroup2->addButton(oct22, 2);
	octgroup2->addButton(oct32, 3);
	octgroup2->addButton(oct42, 4);

	//connect each button group to the slot which sets the octaves
	connect( octgroup, SIGNAL(buttonClicked(int)), this, SLOT(setOctave1(int)));
	connect( octgroup2, SIGNAL(buttonClicked(int)), this, SLOT(setOctave2(int)));

	//add the label and all radio buttons to the octave column
	voctave->addWidget(loctave);
	voctave->addWidget(oct12);
	voctave->addWidget(oct22);
	voctave->addWidget(oct32);
	voctave->addWidget(oct42);
	voctave->addWidget(oct1);
	voctave->addWidget(oct2);
	voctave->addWidget(oct3);
	voctave->addWidget(oct4);
	
	//add the octave column to the total layout
	wholelayout->addLayout(voctave);
	
	//----------------- Set Default Selections ----------------------//

	//these make the initial appearance of the button selection match
	//  the default values above
	sinebutton->setChecked(true);
	oct3->setChecked(true);
	trianglebutton2->setChecked(true);
	oct32->setChecked(true);

	//-------------------- Create Envelope Dials --------------------//
	
	//------------------------ Attack Column -------------------//
	
	//create label for the top of attack column
	lattack = new QLabel("Attack",this);
	lattack->setAlignment(Qt::AlignCenter);
	
	//create vertical layout to hold widgets in attack column
	vattack = new QVBoxLayout;
	
	//create new dial for tier 1 attack
	attack = new QDial(this);
	attack->setNotchesVisible(true);
	attack->setValue(a);
	attack->setMinimum(0);
	attack->setMaximum(1000);
	attack->setSingleStep(10);

	//create new dial for tier 2 attack
	attack2 = new QDial(this);
	attack2->setNotchesVisible(true);
	attack2->setValue(a2);
	attack2->setMinimum(0);
	attack2->setMaximum(1000);
	attack2->setSingleStep(10);
	
	//connect dials to handling slots
	connect(attack, SIGNAL(valueChanged(int)), this, SLOT(setAttack(int)));
	connect(attack2, SIGNAL(valueChanged(int)), this, SLOT(setAttack2(int)));
	
	//add label and dials to attack column
	vattack->addWidget(lattack);
	vattack->addWidget(attack2);
	vattack->addWidget(attack);
	
	//add attack column to total layout
	wholelayout->addLayout(vattack);
	
	//------------------------ Decay Column --------------------//
	
	//create label for the top of decay column
	ldecay = new QLabel("Decay",this);
	ldecay->setAlignment(Qt::AlignCenter);
	
	//create vertical layout to hold widgets in decay column
	vdecay = new QVBoxLayout;
	
	//create new dial for tier 1 decay
	decay = new QDial(this);
	decay->setNotchesVisible(true);
	decay->setValue(d);
	decay->setMinimum(0);
	decay->setMaximum(1000);
	decay->setSingleStep(10);
	
	//create new dial for tier 2 decay
	decay2 = new QDial(this);
	decay2->setNotchesVisible(true);
	decay2->setValue(d2);
	decay2->setMinimum(0);
	decay2->setMaximum(1000);
	decay2->setSingleStep(10);
	
	//connect dials to handling slots
	connect(decay, SIGNAL(valueChanged(int)), this, SLOT(setDecay(int)));
	connect(decay2, SIGNAL(valueChanged(int)), this, SLOT(setDecay2(int)));
	
	//add label and dials to decay column
	vdecay->addWidget(ldecay);
	vdecay->addWidget(decay2);
	vdecay->addWidget(decay);
	
	//add decay column to total layout
	wholelayout->addLayout(vdecay);
	
	//------------------------ Release Column ------------------//

	//create label for the top of release column
	lrelease = new QLabel("Release",this);
	lrelease->setAlignment(Qt::AlignCenter);
	
	//create vertical layout to hold widgets in release column
	vrelease = new QVBoxLayout;
	
	//create new dial for tier 1 release
	release = new QDial(this);
	release->setNotchesVisible(true);
	release->setValue(r);
	release->setMinimum(0);
	release->setMaximum(1000);	
	release->setSingleStep(10);
	
	//create new dial for tier 2 release
	release2 = new QDial(this);
	release2->setNotchesVisible(true);
	release2->setValue(r2);
	release2->setMinimum(0);
	release2->setMaximum(1000);
	release2->setSingleStep(10);

	//connect dials to handling slots
	connect(release, SIGNAL(valueChanged(int)), this, SLOT(setRelease(int)));
	connect(release2, SIGNAL(valueChanged(int)), this, SLOT(setRelease2(int)));
	
	//add label and dials to release column
	vrelease->addWidget(lrelease);
	vrelease->addWidget(release2);
	vrelease->addWidget(release);
	
	//add release column to total layout
	wholelayout->addLayout(vrelease);

	//------------------------ Sustain Column ------------------//
	
	//create label for the top of sustain column
	lsustain = new QLabel("Sustain",this);
	lsustain->setAlignment(Qt::AlignCenter);

	//create vertical layout to hold widgets in sustain column
	vsustain = new QVBoxLayout;
	
	//create new dial for tier 1 sustain
	sustain = new QDial(this);
	sustain->setNotchesVisible(true);
	sustain->setValue(s);
	sustain->setMinimum(0);
	sustain->setMaximum(100);
	sustain->setSingleStep(5);
	
	//create new dial for tier 2 sustain
	sustain2 = new QDial(this);
	sustain2->setNotchesVisible(true);
	sustain2->setValue(s2);
	sustain2->setMinimum(0);
	sustain2->setMaximum(100);
	sustain2->setSingleStep(5);
	
	//connect dials to handling slots
	connect(sustain, SIGNAL(valueChanged(int)), this, SLOT(setSustain(int)));
	connect(sustain2, SIGNAL(valueChanged(int)), this, SLOT(setSustain2(int)));
	
	//add label and dials to sustain column
	vsustain->addWidget(lsustain);
	vsustain->addWidget(sustain2);
	vsustain->addWidget(sustain);
	
	//add sustain column to total layout
	wholelayout->addLayout(vsustain);
	
	//------------------------ End Envelope ----------------------//

	//apply wholelayout to SynthWindow widget
	setLayout(wholelayout);
}

/** \brief Set tier 1 attack
 * \param aa, int, new value
 * \return void
 */
void SynthWindow::setAttack(int aa) { a = aa; }

/** \brief Set tier 1 decay
 * \param dd, int, new value
 * \return void
 */
void SynthWindow::setDecay(int dd) { d = dd; }

/** \brief Set tier 1 release
 * \param rr, int, new value
 * \return void
 */
void SynthWindow::setRelease(int rr) { r = rr; }

/** \brief Set tier 1 sustain
 * \param ss, int, new value
 * \return void
 */
void SynthWindow::setSustain(int ss) { s = ss; }

/** \brief Set tier 2 attack
 * \param aa, int, new value
 * \return void
 */
void SynthWindow::setAttack2(int aa) { a2 = aa; }

/** \brief Set tier 2 decay
 * \param dd, int, new value
 * \return void
 */
void SynthWindow::setDecay2(int dd) { d2 = dd; }

/** \brief Set tier 2 release
 * \param rr, int, new value
 * \return void
 */
void SynthWindow::setRelease2(int rr) { r2 = rr; }

/** \brief Set tier 2 sustain
 * \param ss, int, new value
 * \return void
 */
void SynthWindow::setSustain2(int ss) { s2 = ss; }

/** \brief Set tier 1 octave
 * \param oo, int, new octave value
 * \return void
 */
void SynthWindow::setOctave1(int oo) { o = oo; }

/** \brief Set tier 2 octave
 * \param oo, int, new octave value
 * \return void
 */
void SynthWindow::setOctave2(int oo) { o2 = oo; }

/** \brief Set tier 1 waveform type
 * \param ww, int, number 1-4 used to select wavetype
 * \return void
 */
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

/** \brief Set tier 2 waveform type
 * \param ww, int, number 1-4 used to select wavetype
 * \return void
 */
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

/** \brief Maps key hits to note generation
 * 
 * This function maps all the keys on the keyboard to note generation
 *   in a piano-like way.  LeftShift through RightShift are G-D with all
 *   intermediate notes acting like a piano layout.  Keys Q through \ act
 *   the same and span C-A.
 * 
 * \param event, QKeyEvent *, pointer to QKeyEvent which just happened
 * \return void
 */
void SynthWindow::keyPressEvent( QKeyEvent *event )
{
	//if key isn't an autorepeat signal from keyboard process it
	if( !event->isAutoRepeat() ) {

	//get the Qt::Key code of the key
	int key = event->key();

	//These two lines are necessary because using the Qt way, both shifts 
	//  have the same key code.  Note: using nativeScanCode's may not be portable.
	if( event->nativeScanCode() == 62 )
		ab.add(new WaveForm( "D,5,0", (int)(freq('D',o+2,0)), wt, a, d, s, r));
	else if( event->nativeScanCode() == 50 )
		ab.add(new WaveForm( "G,3,0", (int)(freq('G',o,0)), wt, a, d, s, r));

	//create a waveform based on the key which was hit.  they are added using the 
	//  audiobuffer wrapper class with instantiation 'ab'.  a name is passed first,
	//  then frequency returned by frequency function with varying octaves.  then
	//  the wavetype and envelope information.
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

		// ----------------------------------- Start Upper Tier ---------------------//
		
		case Qt::Key_1:
		ab.add(new WaveForm( "b,3,0", (int)(freq('B',o2,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_Q:
		ab.add(new WaveForm( "c,4,0", (int)(freq('C',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_2:
		ab.add(new WaveForm( "c,4,1", (int)(freq('C',o2+1,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_W:
		ab.add(new WaveForm( "d,4,0", (int)(freq('D',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_3:
		ab.add(new WaveForm( "d,4,1", (int)(freq('D',o2+1,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_E:
		ab.add(new WaveForm( "e,4,0", (int)(freq('E',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_R:
		ab.add(new WaveForm( "f,4,0", (int)(freq('F',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_5:
		ab.add(new WaveForm( "f,4,1", (int)(freq('F',o2+1,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_T:
		ab.add(new WaveForm( "g,4,0", (int)(freq('G',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_6:
		ab.add(new WaveForm( "g,4,1", (int)(freq('G',o2+1,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_Y:
		ab.add(new WaveForm( "a,4,0", (int)(freq('A',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_7:
		ab.add(new WaveForm( "a,4,1", (int)(freq('A',o2+1,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_U:
		ab.add(new WaveForm( "b,4,0", (int)(freq('B',o2+1,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_I:
		ab.add(new WaveForm( "c,5,0", (int)(freq('C',o2+2,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_9:
		ab.add(new WaveForm( "c,5,1", (int)(freq('C',o2+2,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_O:
		ab.add(new WaveForm( "d,5,0", (int)(freq('D',o2+2,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_0:
		ab.add(new WaveForm( "d,5,1", (int)(freq('D',o2+2,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_P:
		ab.add(new WaveForm( "e,5,0", (int)(freq('E',o2+2,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_BracketLeft:
		ab.add(new WaveForm( "f,5,0", (int)(freq('F',o2+2,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_Equal:
		ab.add(new WaveForm( "f,5,1", (int)(freq('F',o2+2,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_BracketRight:
		ab.add(new WaveForm( "g,5,0", (int)(freq('G',o2+2,0)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_Backspace:
		ab.add(new WaveForm( "g,5,1", (int)(freq('G',o2+2,1)), wt2, a2, d2, s2, r2));
		break;

		case Qt::Key_Backslash:
		ab.add(new WaveForm( "a,5,0", (int)(freq('A',o2+2,0)), wt2, a2, d2, s2, r2));
		break;

		//if key combo isn't covered here, pass on up the chain
		default:
		QWidget::keyPressEvent(event);

	}

	}
}

/** \brief deletes notes when the key is released
 * 
 * This function functions almost exactly like the key hit function, but
 *   instead of creating notes, it sends the name of the note which should
 *   be deleted to audiobuffer ab.
 * 
 * \param event, QKeyEvent *, key release event which just happened
 * \return void
 */
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

		//-------------------- Start First Tier Removals -------//

		case Qt::Key_1:
		ab.remove("b,3,0");
		break;

		case Qt::Key_Q:
		ab.remove("c,4,0");
		break;

		case Qt::Key_2:
		ab.remove("c,4,1");
		break;

		case Qt::Key_W:
		ab.remove("d,4,0");
		break;

		case Qt::Key_3:
		ab.remove("d,4,1");
		break;

		case Qt::Key_E:
		ab.remove("e,4,0");
		break;

		case Qt::Key_R:
		ab.remove("f,4,0");
		break;

		case Qt::Key_5:
		ab.remove("f,4,1");
		break;

		case Qt::Key_T:
		ab.remove("g,4,0");
		break;

		case Qt::Key_6:
		ab.remove("g,4,1");
		break;

		case Qt::Key_Y:
		ab.remove("a,4,0");
		break;

		case Qt::Key_7:
		ab.remove("a,4,1");
		break;

		case Qt::Key_U:
		ab.remove("b,4,0");
		break;

		case Qt::Key_I:
		ab.remove("c,5,0");
		break;

		case Qt::Key_9:
		ab.remove("c,5,1");
		break;

		case Qt::Key_O:
		ab.remove("d,5,0");
		break;

		case Qt::Key_0:
		ab.remove("d,5,1");
		break;

		case Qt::Key_P:
		ab.remove("e,5,0");
		break;

		case Qt::Key_BracketLeft:
		ab.remove("f,5,0");
		break;

		case Qt::Key_Equal:
		ab.remove("f,5,1");
		break;

		case Qt::Key_BracketRight:
		ab.remove("g,5,0");
		break;

		case Qt::Key_Backspace:
		ab.remove("g,5,1");
		break;

		case Qt::Key_Backslash:
		ab.remove("a,5,0");
		break;

		default:
		QWidget::keyPressEvent(event);
	}

	}
}


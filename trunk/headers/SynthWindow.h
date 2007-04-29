/** \file SynthWindow.h Header for synthesizer GUI
 * \author Samuel L. Banina 901278567 CSE21212.02
 * 
 * This file declares all the functions and variables which will be
 *   used by the GUI for the synthesizer.  
 */
#ifndef SYNTH_WIN_H
#define SYNTH_WIN_H

#include <QWidget>
#include <QKeyEvent>
#include <QHash>
#include <QString>

#include "AudioThread.h"
#include "AudioBuffer.h"

/** \class SynthWindow
 * \brief GUI for synthesizer
 * 
 * This class defines a Qt widget consisting of controls for the synthesizer.
 *    The controls offer a full keyboard mapping for two tiers of input, 
 *    dials to control envelop settings, and radio buttons to select
 *   the waveform type and which octave in which to produce notes.
 */
class SynthWindow : public QWidget
{
	Q_OBJECT

	public:
		/** \brief SynthWindow Constructor for GUI
		 *
		 * This function does the grunt work in setting up the interface.  It fact
		 *   it does all the work setting up the interface.  It composes the layers
		 *   of control into 6 vertical box layouts for waveform, octave, attack, decay,
		 *   release and sustain.  Then these 6 layouts are composed into a horizontal layout.
		 *   The different radio buttons are also grouped into 4 groups to manage selectivity.
		 */
		SynthWindow();

	public slots:
		
		/** \brief Set tier 1 attack
		 * \param aa, int, new value
		 * \return void
 		*/
		void setAttack(int);
		/** \brief Set tier 1 decay
		 * \param dd, int, new value
		 * \return void
		 */
		void setDecay(int);
		
		/** \brief Set tier 1 release
		 * \param rr, int, new value
		 * \return void
		 */
		void setRelease(int);
		
		/** \brief Set tier 1 sustain
		 * \param ss, int, new value
		 * \return void
		 */
		void setSustain(int);
		
		/** \brief Set tier 2 attack
		 * \param aa, int, new value
		 * \return void
		 */
		void setOctave1(int);
		
		/** \brief Set tier 2 decay
		 * \param dd, int, new value
		 * \return void
		 */
		void setWave1(int);
		
		/** \brief Set tier 2 release
		 * \param rr, int, new value
		 * \return void
		 */
		void setAttack2(int);
		
		/** \brief Set tier 2 sustain
		 * \param ss, int, new value
		 * \return void
		 */
		void setDecay2(int);
		
		/** \brief Set tier 1 octave
		 * \param oo, int, new octave value
		 * \return void
		 */
		void setRelease2(int);
		
		/** \brief Set tier 2 octave
		 * \param oo, int, new octave value
		 * \return void
		 */
		void setSustain2(int);
		
		/** \brief Set tier 1 waveform type
		 * \param ww, int, number 1-4 used to select wavetype
		 * \return void
		 */
		void setOctave2(int);
		
		/** \brief Set tier 2 waveform type
		 * \param ww, int, number 1-4 used to select wavetype
		 * \return void
		 */
		void setWave2(int);

	protected:
		
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
		void keyPressEvent( QKeyEvent *event );
		
		/** \brief deletes notes when the key is released
		 * 
		 * This function functions almost exactly like the key hit function, but
		 *   instead of creating notes, it sends the name of the note which should
		 *   be deleted to audiobuffer ab.
		 * 
		 * \param event, QKeyEvent *, key release event which just happened
		 * \return void
		 */
		void keyReleaseEvent( QKeyEvent *event );

	private:
		//audiobuffer which recieves the notes
		AudioBuffer ab;
		
		//radiobuttons and their buttongroup
		QRadioButton *sinebutton;
		QRadioButton *squarebutton;
		QRadioButton *trianglebutton;
		QRadioButton *sawbutton;
		QButtonGroup *wavegroup;

		//radiobuttons and their buttongroup
		QRadioButton *sinebutton2;
		QRadioButton *squarebutton2;
		QRadioButton *trianglebutton2;
		QRadioButton *sawbutton2;
		QButtonGroup *wavegroup2;

		//envelope dials
		QDial *attack;
		QDial *decay;
		QDial *sustain;
		QDial *release;
		QDial *attack2;
		QDial *decay2;
		QDial *sustain2;
		QDial *release2;

		//all layouts
		QVBoxLayout *wavelayout;
		QVBoxLayout *voctave;
		QVBoxLayout *vattack, *vdecay, *vrelease, *vsustain;
		QHBoxLayout *wholelayout;

		//waveform types
		wavetype wt, wt2;
		
		//envelopes for two tiers		
		int a,d,r,s;
		int a2,d2,r2,s2;
		
		//octave variables for both tiers
		int o, o2;

		//octave buttons and buttongroups
		QRadioButton *oct1, *oct2, *oct3, *oct4;
		QButtonGroup *octgroup;
		QRadioButton *oct12, *oct22, *oct32, *oct42;
		QButtonGroup *octgroup2;

		//labels for columns
		QLabel *loctave, *lwaves;
		QLabel * lattack, *ldecay, *lrelease, *lsustain;
		
};

#endif


#ifndef SYNTH_WIN_H
#define SYNTH_WIN_H

#define AUDBUFLEN 44100

#include <QWidget>
#include <QKeyEvent>
#include <QHash>
#include <QString>

#include "AudioThread.h"
#include "AudioBuffer.h"

//enum wavetype {
//	SIN, SQR, TRI
//};

class SynthWindow : public QWidget
{
	Q_OBJECT

	public:
		SynthWindow();

	public slots:
		void setAttack(int);
		void setDecay(int);
		void setRelease(int);
		void setSustain(int);
		void setOctave1(int);
		void setWave1(int);
		void setAttack2(int);
		void setDecay2(int);
		void setRelease2(int);
		void setSustain2(int);
		void setOctave2(int);
		void setWave2(int);

	protected:
		void keyPressEvent( QKeyEvent *event );
		void keyReleaseEvent( QKeyEvent *event );

	private:
		AudioBuffer ab;
		QRadioButton *sinebutton;
		QRadioButton *squarebutton;
		QRadioButton *trianglebutton;
		QRadioButton *sawbutton;
		QButtonGroup *wavegroup;

		QRadioButton *sinebutton2;
		QRadioButton *squarebutton2;
		QRadioButton *trianglebutton2;
		QRadioButton *sawbutton2;
		QButtonGroup *wavegroup2;

		QDial *attack;
		QDial *decay;
		QDial *sustain;
		QDial *release;
		QDial *attack2;
		QDial *decay2;
		QDial *sustain2;
		QDial *release2;

		QVBoxLayout *wavelayout;
		QHBoxLayout *wholelayout;

		wavetype wt, wt2;		
		int a,d,r,s;
		int a2,d2,r2,s2;
		int o, o2; //octave

		QRadioButton *oct1, *oct2, *oct3, *oct4;
		QButtonGroup *octgroup;
		QRadioButton *oct12, *oct22, *oct32, *oct42;
		QButtonGroup *octgroup2;
		QVBoxLayout *voctave;
		QLabel *loctave, *lwaves;
		QLabel * lattack, *ldecay, *lrelease, *lsustain;
		QVBoxLayout *vattack, *vdecay, *vrelease, *vsustain;
};

#endif


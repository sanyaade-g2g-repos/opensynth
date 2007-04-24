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
		void setSineWave(void);
		void setSquareWave(void);
		void setTriangleWave(void);
		void setSawWave(void);
		void setAttack(int);
		void setDecay(int);
		void setRelease(int);
		void setSustain(int);
		void setOctave1(void);
		void setOctave2(void);
		void setOctave3(void);
		void setOctave4(void);

	protected:
		void keyPressEvent( QKeyEvent *event );
		void keyReleaseEvent( QKeyEvent *event );

	private:
		AudioBuffer ab;
		QRadioButton *sinebutton;
		QRadioButton *squarebutton;
		QRadioButton *trianglebutton;
		QRadioButton *sawbutton;
		QDial *attack;
		QDial *decay;
		QDial *sustain;
		QDial *release;
		QVBoxLayout *wavelayout;
		QHBoxLayout *wholelayout;
		wavetype wt;		
		int a,d,r,s;
		int o; //octave
		QRadioButton *oct1;
		QRadioButton *oct2;
		QRadioButton *oct3;
		QRadioButton *oct4;
		QButtonGroup *octgroup;
		QVBoxLayout *voctave;
		QLabel *loctave, *lwaves;
		QLabel * lattack, *ldecay, *lrelease, *lsustain;
		QVBoxLayout *vattack, *vdecay, *vrelease, *vsustain;
};

#endif


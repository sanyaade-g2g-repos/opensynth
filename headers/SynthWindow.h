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


	protected:
		void keyPressEvent( QKeyEvent *event );
		void keyReleaseEvent( QKeyEvent *event );

	private:
		AudioBuffer ab;
		QRadioButton *sinebutton;
		QRadioButton *squarebutton;
		QRadioButton *trianglebutton;
		QVBoxLayout *wavelayout;
		wavetype wt;		
};

#endif


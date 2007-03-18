#ifndef SYNTH_WIN_H
#define SYNTH_WIN_H

#define AUDBUFLEN 44100

#include <QWidget>
#include <QKeyEvent>
#include <QHash>
#include <QString>

#include "AudioThread.h"
#include "AudioBuffer.h"

class SynthWindow : public QWidget
{
	Q_OBJECT

	public:
		SynthWindow();

	protected:
		void keyPressEvent( QKeyEvent *event );
		void keyReleaseEvent( QKeyEvent *event );

	private:
		AudioBuffer ab;
};

#endif


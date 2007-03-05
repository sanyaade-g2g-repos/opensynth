/** main.cpp
 *
 * tests key press handling for qt
 *
 */

#include <QtGui>
#include <QFrame>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
using namespace std;

#include "SynthWindow.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	
	SynthWindow mysynth;

	mysynth.show();
	return app.exec();
}


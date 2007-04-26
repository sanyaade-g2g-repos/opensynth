/** \file main.cpp Main file for opensynth final project
 * \author Samuel L. Banina 901278567 CSE21212.02
 *
 * This file creates an instance of the synthesizer and
 *   starts it.
 *
 */

#include <QtGui>
#include <QFrame>
#include <QWidget>
#include <QKeyEvent>
using namespace std;

#include "SynthWindow.h"

/** \brief Starts Qt app for opensynth
 * 
 * This function creates a Qt app and adds
 *   a SynthWindow widget to it.
 */
int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	
	SynthWindow mysynth;

	mysynth.show();
	return app.exec();
}


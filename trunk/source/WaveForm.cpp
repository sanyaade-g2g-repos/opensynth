#include <cmath>
#include <iostream>
using namespace std;

#include <QString>
#include "WaveForm.h"

WaveForm::WaveForm(QString n, int f, wavetype wt)
{
	name = n;
	frequency = f;
	size = 44100/frequency;
	dsize = (double)size;
	sample = new double[size];
	index = 0;
	
	for(int i = 0; i < size; ++i)
	{
		if( i == 0 ) { sample[i] = 0; continue; }

		if( wt == SIN ) {
			sample[i] = sin(frequency * 2 * M_PI * i / 44100); //sine wave
		} else if( wt == SQR ) {
			sample[i] = ( (i<(size/2)?1:(-1)) ); //square wave
		} else if( wt == TRI ) {
			sample[i] = 4*abs(round(i/dsize) - i/dsize ) -1;
		} else if( wt == SAW ) {
			sample[i] = 2 * (i/dsize - floor(i/dsize + 0.5));
		}

//		cout << sample[i] << " ";
		sample[i] *= 2000;
	}
//	cout << endl << endl;
}

WaveForm::WaveForm(QString n)
	:size(0), index(0), frequency(0)
{
	name = n;
	sample = new double[1]; //just so it can be deleted later
}

WaveForm::~WaveForm()
{
	delete [] sample;
}

int WaveForm::getAndIncrementIndex(void)
{
	return (index = (index+1)%size);
}


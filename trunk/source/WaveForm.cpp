#include <cmath>
#include <sys/time.h>
#include <iostream>
using namespace std;

#include <QString>
#include "WaveForm.h"

WaveForm::WaveForm(QString n, int f, wavetype wt,
			int aa, int dd, int ss, int rr)
	:a(aa),d(dd),s(ss),r(rr),envcount(0),maxvol(2500)
{

	name = n;
	frequency = f;
	size = 44100/frequency;
	dsize = (double)size;
	sample = new double[size];
	index = 0;
	release = false;
	tempvol = 0;
	
	for(int i = 0; i < size; ++i)
	{

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
//		sample[i] *= 2000;
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

double WaveForm::nextSample(void)
{
//	QMutexLocker locker(&mutex);
	int val;
	envcount = envcount + 1;
	if ( release ) {
		if( tempvol > 0 )
			tempvol = (0-relvol)*(envcount/50)/(r+1) + relvol;
		else { 
			tempvol = 0;
			/*if( sample[index] == 0 )*/
		       	emit finished(name);
			return 0;
		}
	}
	else if( (val = envcount/50) < a )
		tempvol = maxvol*val/a;
	
	else if( (val = envcount/50 - a) < d )
		tempvol = (s - maxvol)*val/d + maxvol;
	
	else
		{tempvol = s; }

	int returnindex = (index+1)%size;
	double returnsample = sample[returnindex];
	++index;

	return (double)tempvol * returnsample;
}

bool WaveForm::isReleased(void) { return (tempvol<1)?true:false; }

void WaveForm::releaseIt(void) 
{ 
//	QMutexLocker lockme(&mutex);
	release = true; 
	envcount = 0; 
	relvol = tempvol;
}


#include <cmath>
using namespace std;

#include <QString>
#include "WaveForm.h"

WaveForm::WaveForm(QString n, int f)
{
	name = n;
	frequency = f;
	size = 44100/frequency;
	sample = new double[size];
	index = 0;
	
	for(int i = 0; i < size; ++i)
	{
		sample[i] = 2000 * sin(frequency * 2 * M_PI * i / 44100);
	}
}

WaveForm::WaveForm(QString n)
	:size(0), frequency(0), index(0)
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


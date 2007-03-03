#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/soundcard.h>
int main(void)
{
  unsigned short int wave[44100]; /* our wavetable */
  int c; /* a counter */
  int out; /* audio out */
  int result;
  /* open /dev/dsp for write only */
  out = open("/dev/dsp",O_RDWR);
  if( out < 0) perror("open (/dev/dsp):");
  /* now we use ioctl to set audio quality */
  c=16; /* 16 bits */
  result =  ioctl(out,SOUND_PCM_WRITE_BITS,&c);
  c=1;  /* 1 channel */
  result = ioctl(out,SOUND_PCM_WRITE_CHANNELS,&c);
  c=44100; /* 44.1KHz */
  printf("result: %d\n",result);
  /* this generates the wavetable of our sines
   * it's standard trig, so play around with
   * whatever crazy equations you want to hear!
   */
  for (c=0; c<44100; c++) {
    wave[c] =8000*sin(220*2*M_PI*(c+13)/44100);
    wave[c]+=7000*sin(277*2*M_PI*(c+29)/44100);
    wave[c]+=6000*sin(330*2*M_PI*(c+41)/44100);
    wave[c]+=5000*sin(440*2*M_PI*(c+67)/44100);
  }
  /* now we write the wavetable to /dev/dsp
   * as though writing to a simple file
   * we'll loop for 5 seconds of sheer joy
   */
  for (c=0; c<5; c++)
  {
    result = write(out, wave, sizeof(wave) );
  }

  close(out); /* close /dev/dsp ! */
  return 0; /* satisfy gcc */
}


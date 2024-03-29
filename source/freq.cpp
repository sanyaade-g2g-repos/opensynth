#include <iostream>
using namespace std;

// P Flynn 2/7/07
//
// this table maps musical notes to frequencies. The table contains
// a pitch  (the name of the note, no accidental, e.g. 'A'), the
// octave in standard form (e.g., A4 = 440 Hz), and an alter value
// to encode sharps and flats. -1  is a flat, and 1 is a sharp. 0 is a
// natural.  Note this table encodes the weird enharmonics like E#/F and Fb/E,
// just in case.

typedef struct _ft {
 char pitch; // letter on scale
 int octave; // octave 
 int alter; // -1 flat, 0 natural, 1 sharp
 float frequency;
 } ft;

ft freqtable[] = {
 { 'C', 0, 0, 16.35 }, { 'C', 0, 1, 17.32 },
 { 'D', 0, -1, 17.32}, { 'D', 0, 0, 18.35 }, { 'D', 0, 1, 19.45 },
 { 'E', 0, -1, 19.45 }, { 'E', 0, 0, 20.6 }, { 'F', 0, -1, 20.6 },
 { 'E', 0, 1, 21.83 }, { 'F', 0, 0, 21.83 }, { 'F', 0, 1, 23.12 },
 { 'G', 0, -1, 23.12 }, { 'G', 0, 0, 24.5 }, { 'G', 0, 1, 25.96 },
 { 'A', 0, -1, 25.96 }, { 'A', 0, 0, 27.5 }, { 'A', 0, 1, 29.14 },
 { 'B', 0, -1, 29.14 }, { 'B', 0, 0, 30.87 }, { 'C', 1, -1, 30.87 },
 { 'B', 0, 1, 32.7 }, { 'C', 1, 0, 32.7 }, { 'C', 1, 1, 34.65 },
 { 'D', 1, -1, 34.65 }, { 'D', 1, 0, 36.71 }, { 'D', 1, 1, 38.89 },
 { 'E', 1, -1, 38.89 }, { 'E', 1, 0, 41.2 }, { 'F', 1, -1, 41.2 },
 { 'E', 1, 1, 43.65 }, { 'F', 1, 0, 43.65 }, { 'F', 1, 1, 46.25 },
 { 'G', 1, -1, 46.25 }, { 'G', 1, 0, 49 }, { 'G', 1, 1, 51.91 },
 { 'A', 1, -1, 51.91 }, { 'A', 1, 0, 55 }, { 'A', 1, 1, 58.27 },
 { 'B', 1, -1, 58.27 }, { 'B', 1, 0, 61.74 }, { 'C', 2, -1, 61.74 },
 { 'B', 1, 1, 65.41 }, { 'C', 2, 0, 65.41 }, { 'C', 2, 1, 69.3 },
 { 'D', 2, -1, 69.3 }, { 'D', 2, 0, 73.42 }, { 'D', 2, 1, 77.78 },
 { 'E', 2, -1, 77.78}, { 'E', 2, 0, 82.41 }, { 'F', 2, -1, 82.41 },
 { 'E', 2, 1, 87.31}, {'F', 2, 0, 87.31 }, { 'F', 2, 1, 92.5 },
 { 'G', 2, -1, 92.5}, {'G', 2, 0, 98 }, {'G', 2, 1, 103.83 },
 { 'A', 2, -1, 103.83}, {'A', 2, 0, 110}, {'A', 2, 1, 116.54},
 { 'B', 2, -1, 116.54 }, {'B', 2, 0, 123.47 }, {'C', 3, -1, 123.47 },
 { 'B', 2, 1, 123.47}, {'C', 3, 0, 130.81}, {'C', 3, 1, 138.59},
 { 'D', 3, -1, 138.59 }, {'D', 3, 0, 146.83}, {'D', 3, 1, 155.56 },
 { 'E', 3, -1, 155.56}, {'E', 3, 0, 164.81}, {'F', 3, -1, 164.81 },
 { 'E', 3, 1, 174.61 }, {'F', 3, 0, 174.61}, {'F', 3, 1, 185 },
 { 'G', 3, -1, 185}, {'G', 3, 0, 196}, {'G', 3, 1, 207.65},
 { 'A', 3, -1, 207.65}, {'A', 3, 0, 220}, {'A', 3, 1, 233.08 },
 { 'B', 3, -1, 233.08}, {'B', 3, 0, 246.94}, {'C', 4, -1, 246.94},
 { 'B', 3, 1, 261.63}, {'C', 4, 0, 261.63}, {'C', 4, 1, 277.18},
 { 'D', 4, -1, 277.18}, {'D', 4, 0, 293.66}, {'D', 4, 1, 311.13},
 { 'E', 4, -1, 311.13}, {'E', 4, 0, 329.63}, {'F', 4, -1, 329.63},
 { 'E', 4, 1, 349.23}, {'F', 4, 0, 349.23}, {'F', 4, 1, 369.99 },
 { 'G', 4, -1, 369.99}, {'G', 4, 0, 392}, {'G', 4, 1, 415.3},
 { 'A', 4, -1, 415.3}, {'A', 4, 0, 440}, {'A', 4, 1, 466.16},
 { 'B', 4, -1, 466.16}, {'B', 4, 0, 493.88}, {'C', 5, -1, 493.88},
 { 'B', 4, 1, 523.25}, {'C', 5, 0, 523.25}, {'C', 5, 1, 554.37 },
 { 'D', 5, -1, 554.37}, {'D', 5, 0, 587.33}, {'D', 5, 1, 622.25},
 { 'E', 5, -1, 622.25}, {'E', 5, 0, 659.26}, {'F', 5, -1, 659.26},
 { 'E', 5, 1, 698.46}, {'F', 5, 0, 698.46}, {'F', 5, 1, 739.99},
 { 'G', 5, -1, 739.99}, {'G', 5, 0, 783.99}, { 'G', 5, 1, 830.61},
 { 'A', 5, -1, 830.61}, {'A', 5, 0, 880}, {'A', 5, 1, 932.33 },
 { 'B', 5, -1, 932.33}, {'B', 5, 0, 987.77}, {'C', 6, -1, 987.77},
 { 'B', 5, 1, 1046.5}, {'C', 6, 0, 1046.5}, {'C', 6, 1, 1108.73},
 { 'D', 6, -1, 1108.73}, {'D', 6, 0, 1174.66}, {'D', 6, 1, 1244.51},
 { 'E', 6, -1, 1244.51}, {'E', 6, 0, 1318.51}, {'F', 6, -1, 1318.51},
 { 'E', 6, 1, 1396.91}, {'F', 6, 0, 1396.91}, {'F', 6, 1, 1479.98},
 { 'G', 6, -1, 1479.98}, {'G', 6, 0, 1567.98}, {'G', 6, 1, 1661.22},
 { 'A', 6, -1, 1661.22}, {'A', 6, 0, 1760}, { 'A', 6, 1, 1864.66},
 { 'B', 6, -1, 1864.66}, {'B', 6, 0, 1975.53}, {'C', 7, -1, 1975.53},
 { 'B', 6, 1, 2093}, {'C', 7, 0, 2093}, {'C', 7, 1, 2217.46},
 { 'D', 7, -1, 2217.46}, {'D', 7, 0, 2349.32}, { 'D', 7, 1, 2489.02},
 { 'E', 7, -1, 2489.02}, {'E', 7, 0, 2637.02}, {'F', 7, -1, 2637.02},
 { 'E', 7, 1, 2793.83}, {'F', 7, 0, 2793.83}, {'F', 7, 1, 2959.96},
 { 'G', 7, -1, 2959.96}, { 'G', 7, 0, 3135.96}, {'G', 7, 1, 3322.44},
 { 'A', 7, -1, 3322.44}, {'A', 7, 0, 3520}, { 'A', 7, 1, 3729.31},
 { 'B', 7, -1, 3729.31}, {'B', 7, 0, 3951.07}, {'C', 8, -1, 3951.07},
 { 'B', 7, 1, 4186.01}, { 'C', 8, 0, 4186.01}, {'C', 8, 1, 4434.92},
 { 'D', 8, -1, 4434.92}, {'D', 8, 0, 4698.64}, {'D', 8, 1, 4978.03}
 };

float freq(char pitch, int octave, int alter) {
 int i;
 for(i=0;i<sizeof(freqtable);i++) {
  if ((pitch==freqtable[i].pitch) && (octave==freqtable[i].octave) && (alter==freqtable[i].alter)) return freqtable[i].frequency;
  }
 cerr << "Error: freq for " << pitch << "," << octave << "," << alter << " not found." << endl;
 return 0.0;
 }

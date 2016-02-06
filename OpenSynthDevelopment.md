# Development #

OpenSynth is written in C++, using Qt4.2, and interfaces with the Linux sound interface.  This page chronicles the ongoing concerns and progress with the design and implementation of the software.

## Concerns ##

  * [RESOLVED!!]Because the application must be playable, speed and efficiency is a prime concern in the design and implementation of OpenSynth.  To that end the software currently has a large latency between pressing a key and hearing the note or releasing the key and termination of the note.  This is probably because of the use of QHash to manage currently playable WaveForms and other storage scheme's will be investigated. [It wasn't QHash, it was the sound card.  The playback buffer had to be manually resized.](.md)

  * Decision of making displayed keyboard (currently unwritten) mouse-playable.  If so, should the sound be triggered through the keystrokes or indirectly, wherein the keystrokes depress the virtual keyboard which trigger the notes.  This would simplify mouse implementation and potentially delay notes.

  * Thread management for continuous output to the speaker feels hackish and improperly implemented.  More research into event loops for QThreads is required.


## Progress ##

  * Interface
    * Radio Buttons for Waveforms
    * Dials for Attack, Decay, Release, and Sustain
  * Completed
    * Sine/Square/Saw/Triangle Waveforms
    * Continuous Playback
    * Keyboard Detection
    * Polyphony
    * Real-time playback!
    * ADSR Envelope

/*******************************************************************************

 Bare Conductive MIDI Objects
 ----------------------------
 
 Midi_object.h - MIDI object struct header file
 
 Very simple structures to allow for mapping two types of USB MIDI messages
 to Touch Board electrodes.

 Bare Conductive code written by Stefan Dzisiewski-Smith.
 
 This work is licensed under a MIT license https://opensource.org/licenses/MIT
 
 Copyright (c) 2016, Bare Conductive
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

#ifndef MIDI_OBJECT_H
#define MIDI_OBJECT_H

enum midi_output_t
{
	MIDI_DISABLED,	// if we're not using that object
	MIDI_NOTE,			// for on/off notes
	MIDI_CONTROL  	// for modulation / slider type outputs
};

struct midi_object_t
{
	// type of MIDI output;
	midi_output_t type;

	// for note objects
	unsigned char noteNumber;

	// touch and release thresholds
	unsigned int touchThreshold;
	unsigned int releaseThreshold;
	
	// for controller objects
	unsigned char controllerNumber;
	unsigned char outputMax;
	unsigned char outputMin;	
	unsigned char lastOutput;

	// raw inputs from electrode filtered data
	unsigned int inputMax;
	unsigned int inputMin;	

	// some sensible defaults
	midi_object_t():
	type(MIDI_DISABLED),
	noteNumber(0),
	touchThreshold(40),
	releaseThreshold(20),
	controllerNumber(0),
	outputMax(127),
	outputMin(0),
	lastOutput(0),
	inputMax(1023),
	inputMin(0)
	{}
};

#endif // MIDI_OBJECT_H
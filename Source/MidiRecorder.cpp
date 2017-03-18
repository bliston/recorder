/*
==============================================================================

MidiRecorder.cpp
Created: 27 Nov 2016 4:27:11pm
Author:  blist

==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

using namespace std;

class MidiRecorder : public Timer {
public:
	MidiRecorder() {

	}

	~MidiRecorder() {

	}

	bool isRecording() {
		return isRec;
	}

	void handleIncomingMidiMessage(MidiMessage &message) {
		if (!isRec)
		{
			return;
		}
		if (isRec && getSequence()->getNumEvents() == 1)
		{
			startRecording();
		}
		addEvent(message);
	}

	void enableRecording() {
		isRec = true;
		mms = new MidiMessageSequence();
		mms->clear();
		int microsecondsPerQuarter = (60000.f / tempo) * 1000.f;
		MidiMessage tempoEvent = MidiMessage::tempoMetaEvent(microsecondsPerQuarter);
		tempoEvent.setTimeStamp(0);
		mms->addEvent(tempoEvent);
	}

	void startRecording() {
		startTimer(0);
		startTime = Time::getMillisecondCounterHiRes();
	}

	void stopRecording() {
		isRec = false;
	}

	void addEvent(MidiMessage &message)
	{
		double timeStampInMS = Time::getMillisecondCounterHiRes() - startTime;
		message.setTimeStamp(ticks(timeStampInMS));
		mms->addEvent(message);
	}

	short getTimeFormat()
	{
		return ticksPerQuarterNote;
	}

	double getTempo()
	{
		return tempo;
	}

	void timerCallback() override
	{
		//double timeStampInMS = Time::getMillisecondCounterHiRes() - startTime;
		//if (timeStampInMS >= msPerTick * ticksPerQuarterNote * (prerollLengthInQuarterNotes + recordingLengthInQuarterNotes))
		//{
		//	metronome->stop();
		//	stopRecording();
		//	stopTimer();
		//}
		if (!isRec) {
			stopRecording();
			stopTimer();
		}
	}

	double ticks(double timeStampInMS)
	{
		return timeStampInMS / msPerTick;
	}

	MidiMessageSequence* getSequence()
	{
		return mms;
	}

	void writeMidiFile(File *myFile)
	{
		MidiFile myMIDIFile;
		myMIDIFile.setTicksPerQuarterNote(getTimeFormat());
		MidiMessageSequence *mySeq = getSequence();
		const MidiMessageSequence *editedSeq = new MidiMessageSequence(*mySeq);
		myMIDIFile.addTrack(*editedSeq);
		ScopedPointer<FileOutputStream> myStream = new FileOutputStream(*myFile);
		myMIDIFile.writeTo(*myStream);
		myStream.release();
	}

private:
	MidiMessageSequence* mms = new MidiMessageSequence();
	double startTime;
	double tempo = 120;
	int ticksPerQuarterNote = 960;
	double msPerTick = (60000.f / tempo) / ticksPerQuarterNote; //960 ticks per quarternote
	bool isRec = false;
};

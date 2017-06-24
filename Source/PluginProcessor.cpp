/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MidiRecorderAudioProcessor::MidiRecorderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	track = new MidiMessageSequence();
    midiPlaybackFile = new File();
    
}

MidiRecorderAudioProcessor::~MidiRecorderAudioProcessor()
{
}

//==============================================================================
const String MidiRecorderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiRecorderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiRecorderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MidiRecorderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiRecorderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiRecorderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiRecorderAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiRecorderAudioProcessor::getProgramName (int index)
{
    return String();
}

void MidiRecorderAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiRecorderAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	ignoreUnused(samplesPerBlock);
	rate = sampleRate;
}

void MidiRecorderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiRecorderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiRecorderAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midi)
{
	MidiMessage msg;
	int ignore;
	for (MidiBuffer::Iterator it(midi); it.getNextEvent(msg, ignore);)
	{
		midiRecorder.handleIncomingMidiMessage(msg);
	}
	if (midiIsPlaying) {
		int sampleDeltaToAdd = -samplesPlayed;
		midi.addEvents(*midiBuffer, samplesPlayed, buffer.getNumSamples(), sampleDeltaToAdd);
		endTimeInSamples = (int)(rate * convertTicksToSeconds(track->getEndTime()));
		samplesPlayed += buffer.getNumSamples();
		if (samplesPlayed >= endTimeInSamples)
		{
			samplesPlayed = 0;
			midiIsPlaying = false;
		}
	}
	if(noteOff) {
		MidiBuffer notesOffBuff = allNotesOffBuffer();
		midi.addEvents(notesOffBuff, 0, 1, 0);
		noteOff = false;
	}
	
}

//==============================================================================
bool MidiRecorderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiRecorderAudioProcessor::createEditor()
{
    return new MidiRecorderAudioProcessorEditor (*this);
}

//==============================================================================
void MidiRecorderAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	if (!midiPlaybackFile->existsAsFile())
	{
		return;
	}
	auto obj = new DynamicObject();
	String fileName = filePathToMidiPropertyString(midiPlaybackFile->getFullPathName());
	obj->setProperty("midiPlaybackFileName", fileName);
	MemoryOutputStream out(destData, false);
	JSON::writeToStream(out, var(obj));
}

void MidiRecorderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	MemoryInputStream in(data, sizeInBytes, false);
	var state = JSON::parse(in);
	var fileNameVar = state["midiPlaybackFileName"];
	if (fileNameVar.isString())
	{
		auto midiFileName = fileNameVar.toString();
		if (!midiFileName.isEmpty())
		{
			String finalPath = midiPropertyStringToFilePath(midiFileName);
			File *file = new File(finalPath);
			if (file->existsAsFile())
			{
				setMidiPlaybackFile(file);
			}

		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiRecorderAudioProcessor();
}

void MidiRecorderAudioProcessor::startRecording()
{

	midiRecorder.enableRecording();
}

void MidiRecorderAudioProcessor::stop()
{
    if (isPlaying()) {
        noteOff = true;
    }
    if (isRecording()) {
        midiRecorder.stopRecording();
        writeMidiFile();
    }
    samplesPlayed = 0;
	midiIsPlaying = false;
}

void MidiRecorderAudioProcessor::play()
{
	midiBuffer->clear();
	for (int i = 0; i < track->getNumEvents(); i++) {
		MidiMessage m = track->getEventPointer(i)->message;
		m.setTimeStamp(convertTicksToSeconds(m.getTimeStamp()));
		int sampleOffset = (int)(rate * m.getTimeStamp());
		midiBuffer->addEvent(m, sampleOffset);
	}
	samplesPlayed = 0;
	midiIsPlaying = true;
}

double MidiRecorderAudioProcessor:: convertTicksToSeconds(int timeStamp)
{
	double secsPerTick = 60.0 / (midiRecorder.getTempo() * midiRecorder.getTimeFormat());
	return secsPerTick * timeStamp;
}

MidiBuffer MidiRecorderAudioProcessor::allNotesOffBuffer()
{
	MidiBuffer midi;
	for (int i = 0; i < 128; i++)
	{
		MidiMessage messageOff1(MidiMessage::noteOff(1, i));
		MidiMessage messageOff2(MidiMessage::noteOff(2, i));
		midi.addEvent(messageOff1, 0);
		midi.addEvent(messageOff2, 0);
	}
	return midi;
}

void MidiRecorderAudioProcessor::setMidiPlaybackFile(File *newMidiPlaybackFile)
{
	midiPlaybackFile = new File(*newMidiPlaybackFile);
	loadMidi();
}

void MidiRecorderAudioProcessor::loadMidi()
{
	ScopedPointer<FileInputStream> myStream = new FileInputStream(*midiPlaybackFile);
	MidiFile myMIDIFile;
	myMIDIFile.readFrom(*myStream);
	const MidiMessageSequence *myTrack = myMIDIFile.getTrack(0);
	MidiMessageSequence *trimmedMms = new MidiMessageSequence(*myTrack);
	myStream.release();
	//trimmedMms->addTimeToMessages(-trimmedMms->getEventTime(1));
	setTrack(trimmedMms);
}

void MidiRecorderAudioProcessor::setTrack(MidiMessageSequence *trk)
{
	track = trk;
}

void MidiRecorderAudioProcessor::setMidiRecordLocation(File *fileToRecordTo)
{
	midiRecordingFile = fileToRecordTo;
}

void MidiRecorderAudioProcessor::writeMidiFile()
{
	if (midiRecorder.getSequence()->getEndTime() > 0 && !midiIsPlaying)
	{
		midiRecorder.writeMidiFile(midiRecordingFile);
		setMidiPlaybackFile(midiRecordingFile);
	}
}

String MidiRecorderAudioProcessor::filePathToMidiPropertyString(String filePath)
{
	File file(filePath);
	return file.getFileName();
}

String MidiRecorderAudioProcessor::midiPropertyStringToFilePath(String fileName)
{
	String finalPath;
	String documentsFolder = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName();
	String folder = documentsFolder + "/Middle/Projects/Recordings/MIDI/";
	finalPath = folder + fileName;
	return finalPath;
}

bool MidiRecorderAudioProcessor::isRecording () {
    return midiRecorder.isRecording();
}

bool MidiRecorderAudioProcessor::isPlaying () {
    return midiIsPlaying;
}

double MidiRecorderAudioProcessor::getPlaybackPositionTime() {
    return samplesPlayed;
}

double MidiRecorderAudioProcessor::getPlaybackEndTime() {
    return endTimeInSamples;
}

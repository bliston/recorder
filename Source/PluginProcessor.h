/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiRecorder.cpp"

//==============================================================================
/**
*/
class MidiRecorderAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MidiRecorderAudioProcessor();
    ~MidiRecorderAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void startRecording();
	void play();
	void stop();
	double convertTicksToSeconds(int timeStamp);
	MidiBuffer allNotesOffBuffer();
	void setMidiPlaybackFile(File *newMidiPlaybackFile);
	File *getMidiPlaybackFile() { return (midiPlaybackFile); }
	void loadMidi();
	void setTrack(MidiMessageSequence *trk);
	void setMidiRecordLocation(File *fileToRecordTo);
	void writeMidiFile();
	String filePathToMidiPropertyString(String filePath);
	String midiPropertyStringToFilePath(String fileName);

private:
	File *midiPlaybackFile;
	File *midiRecordingFile;
	MidiRecorder midiRecorder;
	MidiMessageSequence *track;
	ScopedPointer<MidiBuffer> midiBuffer = new MidiBuffer();
	double rate;
	int samplesPlayed = 0;
	bool midiIsPlaying = false;
	bool noteOff = false;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiRecorderAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED

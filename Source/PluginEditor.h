/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "TemplateOptionButton.h"

//==============================================================================
/**
*/
class MidiRecorderAudioProcessorEditor  : public AudioProcessorEditor,
										  public Button::Listener
{
public:
    MidiRecorderAudioProcessorEditor (MidiRecorderAudioProcessor&);
    ~MidiRecorderAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	MidiRecorderAudioProcessor *getProcessor() const { return static_cast<MidiRecorderAudioProcessor *>(getAudioProcessor()); }
	void buttonClicked(Button* button) override;
	void buttonStateChanged(Button* button) override;
	void chooseFile();
	void setFile(File *newFile);
	void updateFile(File *file);
	void showPath();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiRecorderAudioProcessor& processor;
	Label fileLabel;
	OpenButton openButton;
	RecordButton recordButton;
	StopButton stopButton;
	PlayButton playButton;
    CustomLookAndFeel lookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiRecorderAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED

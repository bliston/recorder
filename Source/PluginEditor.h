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
#include "MiddleLookAndFeel.h"

namespace Icons
{
    const String Done = String::charToString(0xE5CA);
    const String Play = String::charToString(0xE037);
    const String Pause = String::charToString(0xE034);
    const String Rewind = String::charToString(0xE045);
    const String FastForward = String::charToString(0xE044);
    const String Record = String::charToString(0xE061);
    const String Stop = String::charToString(0xE047);
    const String FolderOpen = String::charToString(0xE2C7);
    const String Smiley1 = String::charToString(0xE813); 
}

//==============================================================================
/**
*/
class MidiRecorderAudioProcessorEditor  : public AudioProcessorEditor,
										  public Button::Listener,
                                          private Timer
{
public:
    MidiRecorderAudioProcessorEditor (MidiRecorderAudioProcessor&);
    ~MidiRecorderAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	MidiRecorderAudioProcessor *getProcessor() const { return static_cast<MidiRecorderAudioProcessor *>(getAudioProcessor()); }
	void buttonClicked(Button* button) override;
	void chooseFile();
	void setFile(File *newFile);
	void updateFile(File *file);
	void showPath();
    void updateButtonState();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiRecorderAudioProcessor& processor;
	Label fileLabel;
	TextButton openButton;
	TextButton recordButton;
	TextButton stopButton;
	TextButton playButton;
    Slider playHeadSlider;
    MiddleLookAndFeel lookAndFeel;
    void timerCallback() override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiRecorderAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED

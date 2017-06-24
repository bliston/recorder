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
    const String Done = CharPointer_UTF8("\uE5CA");
    const String Play = CharPointer_UTF8("\uE037");
    const String Pause = CharPointer_UTF8("\uE034");
    const String Rewind = CharPointer_UTF8("\uE045");
    const String FastForward = CharPointer_UTF8("\uE044");
    const String Record = CharPointer_UTF8("\uE061");
    const String Stop = CharPointer_UTF8("\uE047");
    const String FolderOpen = CharPointer_UTF8("\uE2C7");
    const String Smiley1 = CharPointer_UTF8("\uE813");
    
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

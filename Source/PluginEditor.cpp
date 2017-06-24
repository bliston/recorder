/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiRecorderAudioProcessorEditor::MidiRecorderAudioProcessorEditor (MidiRecorderAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
	fileLabel.setJustificationType(Justification::centred);
	fileLabel.setColour(Label::textColourId, findColour(mainAccentColourId));
	Font font(20, Font::plain);
	fileLabel.setFont(font);
	addAndMakeVisible(&fileLabel);

    recordButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
    recordButton.setColour(TextButton::ColourIds::buttonColourId, findColour(mainBackgroundColourId));
    recordButton.setConnectedEdges(3);
    recordButton.setButtonText(Icons::Record + "~");
	recordButton.addListener(this);
	addAndMakeVisible(&recordButton);

    playButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
    playButton.setColour(TextButton::ColourIds::buttonColourId, findColour(mainBackgroundColourId));
    playButton.setConnectedEdges(3);
    playButton.setButtonText(Icons::Play + "~");
	playButton.addListener(this);
	addAndMakeVisible(&playButton);
    
    stopButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
    stopButton.setColour(TextButton::ColourIds::buttonColourId, findColour(mainBackgroundColourId));
    stopButton.setConnectedEdges(3);
    stopButton.setButtonText(Icons::Stop + "~");
    stopButton.addListener(this);
    addAndMakeVisible(&stopButton);
    
    openButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
    openButton.setColour(TextButton::ColourIds::buttonColourId, findColour(mainBackgroundColourId));
    openButton.setConnectedEdges(3);
    openButton.setButtonText(Icons::FolderOpen + "~");
	openButton.addListener(this);
	addAndMakeVisible(&openButton);
    
    addAndMakeVisible(&playHeadSlider);
    playHeadSlider.setEnabled(false);
    playHeadSlider.setSliderStyle (Slider::LinearHorizontal);
    playHeadSlider.setTextBoxStyle (Slider::TextBoxAbove, false, 40, 20);
    playHeadSlider.setTextBoxIsEditable(false);
    
    setFile(processor.getMidiPlaybackFile());
    
    //start timer for updating the playHeadSlider
    startTimer (100);
    
}

MidiRecorderAudioProcessorEditor::~MidiRecorderAudioProcessorEditor()
{
	recordButton.removeListener(this);
	stopButton.removeListener(this);
	playButton.removeListener(this);
}

//==============================================================================
void MidiRecorderAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (findColour(mainBackgroundColourId));

}

void MidiRecorderAudioProcessorEditor::resized()
{
    
    
    int colWidth = proportionOfWidth(1.0f);
    int rowHeight = proportionOfHeight(1.0f);
    auto rowArea = getLocalBounds().reduced(0);
    auto r1 = rowArea.removeFromTop(rowHeight/4);
    recordButton.setBounds(r1.removeFromLeft(colWidth/4).reduced(0));
    playButton.setBounds(r1.removeFromLeft(colWidth/4).reduced(0));
    stopButton.setBounds(r1.removeFromLeft(colWidth/4).reduced(0));
    openButton.setBounds(r1.removeFromLeft(colWidth/4).reduced(0));
    auto r2 = rowArea.removeFromTop(rowHeight/4);
    fileLabel.setBounds(r2.removeFromTop(colWidth).reduced(5));
    auto r3 = rowArea.removeFromTop(rowHeight/8);
    playHeadSlider.setBounds(r3.removeFromTop(colWidth).reduced(5));
}

void MidiRecorderAudioProcessorEditor::timerCallback()
{
    if (processor.getPlaybackEndTime() > 0)
    playHeadSlider.setRange (0, processor.getPlaybackEndTime(), 0);
    
    playHeadSlider.setValue(processor.getPlaybackPositionTime());
    
    if (processor.isPlaying() || processor.isRecording()) {
        stopButton.setEnabled(true);
    }
    else {
        stopButton.setEnabled(false);
    }
    
    if (processor.getMidiPlaybackFile()) {
        playButton.setEnabled(true);
    }
    else {
        playButton.setEnabled(false);
    }
    
    if (!processor.isRecording()) {
        playButton.setEnabled(true);
    }
    else {
        playButton.setEnabled(false);
    }
}

void MidiRecorderAudioProcessorEditor::buttonClicked(Button* button)
{
	String finalPath;
	String documentsFolder = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName();
	String folder = documentsFolder + "/Middle/Projects/Recordings/MIDI";
	File fileToRecordTo(File(folder)
		.getNonexistentChildFile("MidiRecording", ".mid"));
	processor.setMidiRecordLocation(&fileToRecordTo);
	if (button == &recordButton)
	{
		if (!processor.isRecording() && !processor.isPlaying()) {
			processor.startRecording();
            recordButton.setColour(TextButton::textColourOnId, Colours::orangered);
            recordButton.setColour(TextButton::textColourOffId, Colours::orangered);
            recordButton.repaint();

		}
	}
	else if (button == &stopButton) {
		processor.stop();
		setFile(processor.getMidiPlaybackFile());
        recordButton.setColour(TextButton::textColourOnId, findColour(mainAccentColourId));
        recordButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
        recordButton.repaint();
        playButton.setColour(TextButton::textColourOnId, findColour(mainAccentColourId));
        playButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
        playButton.repaint();
	}
	else if (button == &playButton) {
        if (!processor.isRecording()) {
            processor.play();
            recordButton.setColour(TextButton::textColourOnId, findColour(mainAccentColourId));
            recordButton.setColour(TextButton::textColourOffId, findColour(mainAccentColourId));
            recordButton.repaint();
        }
	}
	else if (button == &openButton)
	{
		chooseFile();
	}
    //updateButtonState();
}

void MidiRecorderAudioProcessorEditor::chooseFile()
{
    String documentsFolder = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName();
    String folder = documentsFolder + "/Middle/Projects/Recordings/MIDI";
	FileChooser chooser("Select an midi file...", File(folder), "*.mid;*.midi;");
	if (chooser.browseForFileToOpen())
	{
		File midiPlaybackFile = chooser.getResult();
		setFile(&midiPlaybackFile);
	}
}

void MidiRecorderAudioProcessorEditor::setFile(File *newFile)
{
    if(!newFile->existsAsFile())
    {
        return;
    }
	auto processor = getProcessor();

	processor->setMidiPlaybackFile(newFile);

	updateFile(newFile);
}

void MidiRecorderAudioProcessorEditor::updateFile(File *file)
{
	fileLabel.setText(file->getFileName(), dontSendNotification);
	showPath();
}

void MidiRecorderAudioProcessorEditor::showPath()
{
	auto processor = getProcessor();
	File *file = processor->getMidiPlaybackFile();
}

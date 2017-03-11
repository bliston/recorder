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
    : AudioProcessorEditor (&p), processor (p), fileLabel(String::empty, "File... (click here to choose)"), pathLabel(String::empty)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	addAndMakeVisible(&fileLabel);
	fileLabel.addClickListener(this);

	addAndMakeVisible(&pathLabel);
	pathLabel.addClickListener(this);

	recordButton.setButtonText("Record");
	recordButton.addListener(this);
	addAndMakeVisible(&recordButton);

	stopButton.setButtonText("Stop");
	stopButton.addListener(this);
	addAndMakeVisible(&stopButton);

	playButton.setButtonText("Play");
	playButton.addListener(this);
	addAndMakeVisible(&playButton);

	setFile(processor.getMidiPlaybackFile());
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
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
}

void MidiRecorderAudioProcessorEditor::resized()
{
	int numComponents = 5;
	recordButton.setBounds(0, 0, getWidth() / numComponents, getHeight());
	stopButton.setBounds(getWidth() / numComponents, 0, getWidth() / numComponents, getHeight());
	playButton.setBounds(2 * getWidth() / numComponents, 0, getWidth() / numComponents, getHeight());
	fileLabel.setBounds(3 * getWidth() / numComponents, 0, getWidth() / numComponents, getHeight());
	pathLabel.setBounds(4 * getWidth() / numComponents, 0, getWidth() / numComponents, getHeight());
}

void MidiRecorderAudioProcessorEditor::buttonClicked(Button* button)
{
	File fileToRecordTo(File::getSpecialLocation(File::userDocumentsDirectory)
		.getNonexistentChildFile("MidiRecording", ".mid"));
//	File fileToRecordTo(File("C:\\Middle\\Recordings\\midi")
//		.getNonexistentChildFile("MidiRecording", ".mid"));
	processor.setMidiRecordLocation(&fileToRecordTo);
	if (button == &recordButton)
	{
		processor.startRecording();
	}
	else if (button == &stopButton) {
		processor.stop();
		setFile(processor.getMidiPlaybackFile());
	}
	else if (button == &playButton) {
		processor.play();
	}
}

void MidiRecorderAudioProcessorEditor::labelClicked(Label *clickedLabel)
{
	if (clickedLabel == &fileLabel)
	{
		chooseFile();
	}
}

void MidiRecorderAudioProcessorEditor::chooseFile()
{
	FileChooser chooser("Select an midi file...", File::nonexistent, "*.mid;*.midi;");

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
	pathLabel.setText(file->getParentDirectory().getFullPathName(), dontSendNotification);
}

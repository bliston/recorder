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
    setSize (600, 300);

	fileLabel.setJustificationType(Justification::centred);
	fileLabel.setColour(Label::textColourId, Colours::grey);
	Font font(20, Font::plain);
	fileLabel.setFont(font);
	addAndMakeVisible(&fileLabel);

	recordButton.addListener(this);
	addAndMakeVisible(&recordButton);

	stopButton.addListener(this);
	addAndMakeVisible(&stopButton);

	playButton.addListener(this);
	addAndMakeVisible(&playButton);

	openButton.addListener(this);
	addAndMakeVisible(&openButton);

	setFile(processor.getMidiPlaybackFile());
    
    updateButtonState();
    // keeps updating button highlighting based on button states
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
    g.fillAll (Colours::white);
}

void MidiRecorderAudioProcessorEditor::resized()
{
    Rectangle<int> allOpts = getLocalBounds().reduced (10, 10);
    allOpts.removeFromBottom (allOpts.getHeight() / 2);
    
    const int numHorizIcons = 4;
    const int optStep = allOpts.getWidth() / numHorizIcons;
    recordButton.setBounds (Rectangle<int> (allOpts.getX() + (0 % numHorizIcons) * optStep,
                                            allOpts.getY() + 0 * allOpts.getHeight(),
                                            optStep, allOpts.getHeight() / 1)
                            .reduced (10, 10));
    stopButton.setBounds (Rectangle<int> (allOpts.getX() + (1 % numHorizIcons) * optStep,
                                          allOpts.getY() + 0 * allOpts.getHeight(),
                                          optStep, allOpts.getHeight() / 1)
                          .reduced (10, 10));
    playButton.setBounds (Rectangle<int> (allOpts.getX() + (2 % numHorizIcons) * optStep,
                                          allOpts.getY() + 0 * allOpts.getHeight(),
                                          optStep, allOpts.getHeight() / 1)
                          .reduced (10, 10));
	openButton.setBounds (Rectangle<int>(allOpts.getX() + (3 % numHorizIcons) * optStep,
		allOpts.getY() + 0 * allOpts.getHeight(),
		optStep, allOpts.getHeight() / 1)
		.reduced(10, 10));
    
    Rectangle<int> openButtonBounds = getLocalBounds();
    openButtonBounds.removeFromBottom (proportionOfHeight (0.12f));
    openButtonBounds = openButtonBounds.removeFromBottom (120);
    openButtonBounds.reduce (10, 10);
	fileLabel.setBounds (openButtonBounds.reduced (0));
    
    updateButtonState();
}

void MidiRecorderAudioProcessorEditor::timerCallback()
{
    updateButtonState();
}

void MidiRecorderAudioProcessorEditor::updateButtonState ()
{
    playButton.setIsPlaying(processor.isPlaying());
    recordButton.setIsRecording(processor.isRecording());
    playButton.repaint();
    stopButton.repaint();
    recordButton.repaint();
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

		}
	}
	else if (button == &stopButton) {
		processor.stop();
		setFile(processor.getMidiPlaybackFile());
	}
	else if (button == &playButton) {
		if (!processor.isRecording()) {
			processor.play();
		}
	}
	else if (button == &openButton)
	{
		chooseFile();
	}
    updateButtonState();
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

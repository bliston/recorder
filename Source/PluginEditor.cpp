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
    Rectangle<int> allOpts = getLocalBounds().reduced (10, 10);
    allOpts.removeFromBottom (allOpts.getHeight() / 2);
    
    const int numHorizIcons = 3;
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
    
    Rectangle<int> openButtonBounds = getLocalBounds();
    openButtonBounds.removeFromBottom (proportionOfHeight (0.12f));
    openButtonBounds = openButtonBounds.removeFromBottom (120);
    openButtonBounds.reduce (10, 10);
    fileLabel.setBounds (openButtonBounds.removeFromLeft ((allOpts.getWidth() / 2) - 20));
    pathLabel.setBounds (openButtonBounds.reduced (10, 0));
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
            recordButton.setIsRecording(true);
            recordButton.repaint();
            playButton.setIsPlaying(false);
            recordButton.repaint();
        }
	}
	else if (button == &stopButton) {
        recordButton.setIsRecording(false);
        playButton.setIsPlaying(false);
        recordButton.repaint();
        playButton.repaint();
		processor.stop();
		setFile(processor.getMidiPlaybackFile());
	}
	else if (button == &playButton) {
        if (!processor.isRecording()) {
            processor.play();
            playButton.setIsPlaying(true);
            playButton.repaint();
            recordButton.setIsRecording(false);
            recordButton.repaint();
        }
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

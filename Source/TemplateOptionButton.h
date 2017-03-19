/*
  ==============================================================================

    TemplateOptionButton.h
    Created: 12 Mar 2017 9:00:09am
    Author:  Andrew Liston

  ==============================================================================
*/

#ifndef TEMPLATEOPTIONBUTTON_H_INCLUDED
#define TEMPLATEOPTIONBUTTON_H_INCLUDED

#include "BinaryData.h"
#include "AppColours.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
Record Button
*/
class RecordButton   : public DrawableButton
{
public:
    RecordButton ()
    : DrawableButton (String(), DrawableButton::ImageFitted)
    {
        LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
                
        const char* thumbSvg;
        thumbSvg = BinaryData::keymapper_record_svg;
                
        // svg for thumbnail icon
        ScopedPointer<XmlElement> svg (XmlDocument::parse (thumbSvg));
        jassert (svg != nullptr);
                
        thumb = Drawable::createFromSVG (*svg);
        thumb->replaceColour(Colour (0xff000000), findColour(mainAccentColourId));
                
        // svg for thumbnail background highlight
        ScopedPointer<XmlElement> backSvg (XmlDocument::parse (BinaryData::middle_highlight_svg));
        jassert (backSvg != nullptr);
                
        hoverBackground = Drawable::createFromSVG (*backSvg);
        hoverBackground->replaceColour(Colour (0xffDDDDDD), Colours::white);
                
        description = "<insert description>";
                
        name = "Record";
        
    }
    
    void paintButton(Graphics& g, bool isMouseOverButton, bool /*isButtonDown*/) override
    {
        const Rectangle<float> r(getLocalBounds().toFloat());
        
        if (isRecording == false) {
            name = "Record";
            hoverBackground->replaceColour(Colours::red.withAlpha(0.3f), Colours::white);
            hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
            thumb->replaceColour(Colour (0xff000000), findColour(mainAccentColourId));
            thumb->drawWithin(g, r, RectanglePlacement::centred, 1.0);
        }
        else {
            name = "Recording";
            hoverBackground->replaceColour(Colours::white, Colours::red.withAlpha(0.3f));
            hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
            thumb->replaceColour(findColour(mainAccentColourId), Colour (0xff000000));
            thumb->drawWithin(g, r, RectanglePlacement::centred, 1.0);
        }
        
        Rectangle<float> textTarget;
        textTarget = RectanglePlacement(RectanglePlacement::centred).appliedTo(thumb->getDrawableBounds(), r);
        textTarget = textTarget.removeFromBottom(textTarget.getHeight() * 0.3f);
        g.setColour(findColour(mainBackgroundColourId).contrasting());
        g.drawText(name, textTarget, Justification::centred, true);
    }
            
    void resized() override
    {
        thumb->setBoundsToFit (0, 0, getWidth(), getHeight(), Justification::centred, false);
    }
            
    void setDescription (String descript) noexcept
    {
        description = descript;
    }
            
    String getDescription() const noexcept
    {
        return description;
    }
            
    void setIsRecording(bool isRec) noexcept {
        isRecording = isRec;
    }
            
    bool getIsRecording() const noexcept {
        return isRecording;
    }
            
private:
    bool isRecording;
    CustomLookAndFeel lookAndFeel;
    ScopedPointer<Drawable> thumb, hoverBackground;
    String name, description;
            
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecordButton)
};

//==============================================================================
/**
Stop Button
*/
class StopButton   : public DrawableButton
{
public:
    StopButton ()
    : DrawableButton (String(), DrawableButton::ImageFitted)
    {
        LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
        
        const char* thumbSvg;
        thumbSvg = BinaryData::keymapper_stop_svg;
        
        // svg for thumbnail icon
        ScopedPointer<XmlElement> svg (XmlDocument::parse (thumbSvg));
        jassert (svg != nullptr);
        
        thumb = Drawable::createFromSVG (*svg);
        thumb->replaceColour(Colour (0xff000000), findColour(mainAccentColourId));
        
        // svg for thumbnail background highlight
        ScopedPointer<XmlElement> backSvg (XmlDocument::parse (BinaryData::middle_highlight_svg));
        jassert (backSvg != nullptr);
        
        hoverBackground = Drawable::createFromSVG (*backSvg);
        hoverBackground->replaceColour(Colour (0xffDDDDDD), findColour(mainAccentColourId).withAlpha(0.0f));
        
        description = "<insert description>";
        
        name = "Stop";

    }
    
    void paintButton (Graphics& g, bool isMouseOverButton, bool /*isButtonDown*/) override
    {
        const Rectangle<float> r (getLocalBounds().toFloat());
        
        hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
        thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);

        Rectangle<float> textTarget;
        textTarget = RectanglePlacement (RectanglePlacement::centred).appliedTo (thumb->getDrawableBounds(), r);
        textTarget = textTarget.removeFromBottom (textTarget.getHeight() * 0.3f);
        g.setColour (findColour (mainBackgroundColourId).contrasting());
        g.drawText (name, textTarget, Justification::centred, true);
    }
    
    void resized() override
    {
        thumb->setBoundsToFit (0, 0, getWidth(), getHeight(), Justification::centred, false);
    }
    
    void setDescription (String descript) noexcept
    {
        description = descript;
    }
    
    String getDescription() const noexcept
    {
        return description;
    }
    
private:
    CustomLookAndFeel lookAndFeel;
    ScopedPointer<Drawable> thumb, hoverBackground;
    String name, description;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StopButton)
};

//==============================================================================
/**
Play Button
*/
class PlayButton : public DrawableButton
{
public:
	PlayButton()
		: DrawableButton(String(), DrawableButton::ImageFitted)
	{
		LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);

		const char* thumbSvg;
		thumbSvg = BinaryData::keymapper_play_svg;

		// svg for thumbnail icon
		ScopedPointer<XmlElement> svg(XmlDocument::parse(thumbSvg));
		jassert(svg != nullptr);

		thumb = Drawable::createFromSVG(*svg);
		thumb->replaceColour(Colour(0xff000000), findColour(mainAccentColourId));

		// svg for thumbnail background highlight
		ScopedPointer<XmlElement> backSvg(XmlDocument::parse(BinaryData::middle_highlight_svg));
		jassert(backSvg != nullptr);

		hoverBackground = Drawable::createFromSVG(*backSvg);
        hoverBackground->replaceColour(Colour(0xffDDDDDD), Colours::white);

		description = "<insert description>";

		name = "Play";

	}

	void paintButton(Graphics& g, bool isMouseOverButton, bool /*isButtonDown*/) override
	{
		const Rectangle<float> r(getLocalBounds().toFloat());
		
        if (isPlaying == false) {
            name = "Play";
            hoverBackground->replaceColour(findColour(mainAccentColourId).withAlpha(0.3f), Colours::white);
            hoverBackground->drawWithin(g, r, RectanglePlacement::centred, 1.0);
            thumb->drawWithin(g, r, RectanglePlacement::centred, 1.0);
        }
        else {
            name = "Playing";
            hoverBackground->replaceColour(Colours::white, findColour(mainAccentColourId).withAlpha(0.3f));
            hoverBackground->drawWithin(g, r, RectanglePlacement::centred, 1.0);
            thumb->drawWithin(g, r, RectanglePlacement::centred, 1.0);
        }

		Rectangle<float> textTarget;
        textTarget = RectanglePlacement(RectanglePlacement::centred).appliedTo(thumb->getDrawableBounds(), r);
        textTarget = textTarget.removeFromBottom(textTarget.getHeight() * 0.3f);
		g.setColour(findColour(mainBackgroundColourId).contrasting());
		g.drawText(name, textTarget, Justification::centred, true);
	}

	void resized() override
	{
		thumb->setBoundsToFit(0, 0, getWidth(), getHeight(), Justification::centred, false);
	}

	void setDescription(String descript) noexcept
	{
		description = descript;
	}

	String getDescription() const noexcept
	{
		return description;
	}

	void setIsPlaying(bool isPlay) noexcept {
		isPlaying = isPlay;
	}

	bool getIsPlaying() const noexcept {
		return isPlaying;
	}

private:
	bool isPlaying;
	CustomLookAndFeel lookAndFeel;
	ScopedPointer<Drawable> thumb, hoverBackground;
	String name, description;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayButton)
};

//==============================================================================
/**
Open button.
*/
class OpenButton : public DrawableButton
{
public:
	OpenButton()
		: DrawableButton(String(), DrawableButton::ImageFitted)
	{
		LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);

		const char* thumbSvg;
		thumbSvg = BinaryData::keymapper_open_svg;

		// svg for thumbnail icon
		ScopedPointer<XmlElement> svg(XmlDocument::parse(thumbSvg));
		jassert(svg != nullptr);

		thumb = Drawable::createFromSVG(*svg);
		thumb->replaceColour(Colour(0xff000000), findColour(mainAccentColourId));

		// svg for thumbnail background highlight
		ScopedPointer<XmlElement> backSvg(XmlDocument::parse(BinaryData::middle_highlight_svg));
		jassert(backSvg != nullptr);

		hoverBackground = Drawable::createFromSVG(*backSvg);
		hoverBackground->replaceColour(Colour(0xffDDDDDD), findColour(mainAccentColourId).withAlpha(0.0f));

		description = "<insert description>";

		name = "Open";
	}

    void paintButton (Graphics& g, bool isMouseOverButton, bool /*isButtonDown*/) override
    {
        const Rectangle<float> r (getLocalBounds().toFloat());
        
        hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
        thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);
        
        Rectangle<float> textTarget;
        textTarget = RectanglePlacement (RectanglePlacement::centred).appliedTo (thumb->getDrawableBounds(), r);
        textTarget = textTarget.removeFromBottom (textTarget.getHeight() * 0.3f);
        g.setColour (findColour (mainBackgroundColourId).contrasting());
        g.drawText (name, textTarget, Justification::centred, true);
    }

	void resized() override
	{
		thumb->setBoundsToFit(0, 0, getWidth(), getHeight(), Justification::centred, false);
	}

	void setDescription(String descript) noexcept
	{
		description = descript;
	}

	String getDescription() const noexcept
	{
		return description;
	}

private:
	CustomLookAndFeel lookAndFeel;
	ScopedPointer<Drawable> thumb, hoverBackground;
	String name, description;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OpenButton)
};

#endif  // TEMPLATEOPTIONBUTTON_H_INCLUDED

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
         Template option tile button.
         The drawable button object class for the tile icons and buttons in the TemplateTileBrowser
         */
        class RecordButton   : public DrawableButton
        {
        public:
            RecordButton ()
            : DrawableButton (String(), ImageFitted)
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
                isRecording = false;
        
            }
            
            void paintButton (Graphics& g, bool isMouseOverButton, bool /*isButtonDown*/) override
            {
                const Rectangle<float> r (getLocalBounds().toFloat());
                
                //if (isMouseOverButton)
                //{

                    if (getStyle() == ImageFitted)
                    {
                        if (isRecording == false)
                            hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                        thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                    }
                    else
                    {
                        g.setColour (findColour (mainAccentColourId).withAlpha (0.3f));
                        g.fillRoundedRectangle (r.reduced (0.0f), 10.0f);
                        g.setColour (findColour (mainAccentColourId));
                        g.drawRoundedRectangle (r.reduced (0.0f), 10.0f, 1.35f);
                    }
                //}
                //else
                //{
                    if (getStyle() == ImageFitted)
                    {
                        if (isRecording == true) {
                            name = "Recording";
                            hoverBackground->replaceColour(Colours::white, Colours::red.withAlpha(0.3f));
                            hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                            thumb->replaceColour(findColour(mainAccentColourId), Colours::red.withAlpha(0.3f));
                            thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                            
                        }
                        else {
                            name = "Record";
                            hoverBackground->replaceColour(Colours::red.withAlpha(0.3f), Colours::white);
                            hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                            thumb->replaceColour(Colours::red.withAlpha(0.3f), findColour(mainAccentColourId));
                            thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                        }
                        thumb->drawWithin (g, r, RectanglePlacement::centred, 1.0);
                    }
                    else
                    {
                        g.setColour (findColour (mainAccentColourId));
                        g.drawRoundedRectangle (r.reduced (0.0f), 10.0f, 1.35f);
                    }
                //}
                
                Rectangle<float> textTarget;
                
                // center the text for the text buttons or position the text in the image buttons
                if (getStyle() != ImageFitted)
                {
                    textTarget = getLocalBounds().toFloat();
                }
                else
                {
                    textTarget = RectanglePlacement (RectanglePlacement::centred).appliedTo (thumb->getDrawableBounds(), r);
                    textTarget = textTarget.removeFromBottom (textTarget.getHeight() * 0.3f);
                }
                
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
 Template option tile button.
 The drawable button object class for the tile icons and buttons in the TemplateTileBrowser
 */
class StopButton   : public DrawableButton
{
public:
    StopButton ()
    : DrawableButton (String(), ImageFitted)
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
        
        if (isMouseOverButton)
        {
            if (getStyle() == ImageFitted)
            {
                hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);
            }
            else
            {
                g.setColour (findColour (mainAccentColourId).withAlpha (0.3f));
                g.fillRoundedRectangle (r.reduced (0.0f), 10.0f);
                g.setColour (findColour (mainAccentColourId));
                g.drawRoundedRectangle (r.reduced (0.0f), 10.0f, 1.35f);
            }
        }
        else
        {
            if (getStyle() == ImageFitted)
            {
                thumb->drawWithin (g, r, RectanglePlacement::centred, 1.0);
            }
            else
            {
                g.setColour (findColour (mainAccentColourId));
                g.drawRoundedRectangle (r.reduced (0.0f), 10.0f, 1.35f);
            }
        }
        
        Rectangle<float> textTarget;
        
        // center the text for the text buttons or position the text in the image buttons
        if (getStyle() != ImageFitted)
        {
            textTarget = getLocalBounds().toFloat();
        }
        else
        {
            textTarget = RectanglePlacement (RectanglePlacement::centred).appliedTo (thumb->getDrawableBounds(), r);
            textTarget = textTarget.removeFromBottom (textTarget.getHeight() * 0.3f);
        }
        
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
 Template option tile button.
 The drawable button object class for the tile icons and buttons in the TemplateTileBrowser
 */
class PlayButton   : public DrawableButton
{
public:
    PlayButton ()
    : DrawableButton (String(), ImageFitted)
    {
        LookAndFeel::setDefaultLookAndFeel (&lookAndFeel);
        
        const char* thumbSvg;
        thumbSvg = BinaryData::keymapper_play_svg;
        
        // svg for thumbnail icon
        ScopedPointer<XmlElement> svg (XmlDocument::parse (thumbSvg));
        jassert (svg != nullptr);
        
        thumb = Drawable::createFromSVG (*svg);
        thumb->replaceColour(Colour (0xff000000), findColour(mainAccentColourId));
        
        // svg for thumbnail background highlight
        ScopedPointer<XmlElement> backSvg (XmlDocument::parse (BinaryData::middle_highlight_svg));
        jassert (backSvg != nullptr);
        
        hoverBackground = Drawable::createFromSVG (*backSvg);
        hoverBackground->replaceColour(Colour (0xffDDDDDD), findColour(mainAccentColourId).withAlpha(0.3f));
        
        description = "<insert description>";
        
        name = "Play";
    }
    
    void paintButton (Graphics& g, bool isMouseOverButton, bool /*isButtonDown*/) override
    {
        const Rectangle<float> r (getLocalBounds().toFloat());
        
        //if (isMouseOverButton)
        //{
        
        if (getStyle() == ImageFitted)
        {
            if (isPlaying == false)
                hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
                thumb->drawWithin (g, r , RectanglePlacement::centred, 1.0);
            }
        else
        {
            g.setColour (findColour (mainAccentColourId).withAlpha (0.3f));
            g.fillRoundedRectangle (r.reduced (0.0f), 10.0f);
            g.setColour (findColour (mainAccentColourId));
            g.drawRoundedRectangle (r.reduced (0.0f), 10.0f, 1.35f);
        }
        //}
        //else
        //{
        if (getStyle() == ImageFitted)
        {
            if (isPlaying == true) {
                name = "Playing";
                hoverBackground->replaceColour(Colours::white, findColour (mainAccentColourId).withAlpha (0.3f));
                hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
            }
            else {
                name = "play";
                hoverBackground->replaceColour(findColour (mainAccentColourId).withAlpha (0.3f), Colours::white);
                hoverBackground->drawWithin (g, r , RectanglePlacement::centred, 1.0);
            }
            thumb->drawWithin (g, r, RectanglePlacement::centred, 1.0);
        }
        else
        {
            g.setColour (findColour (mainAccentColourId));
            g.drawRoundedRectangle (r.reduced (0.0f), 10.0f, 1.35f);
        }
        //}
        
        Rectangle<float> textTarget;
        
        // center the text for the text buttons or position the text in the image buttons
        if (getStyle() != ImageFitted)
        {
            textTarget = getLocalBounds().toFloat();
        }
        else
        {
            textTarget = RectanglePlacement (RectanglePlacement::centred).appliedTo (thumb->getDrawableBounds(), r);
            textTarget = textTarget.removeFromBottom (textTarget.getHeight() * 0.3f);
        }
        
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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayButton)
};

#endif  // TEMPLATEOPTIONBUTTON_H_INCLUDED

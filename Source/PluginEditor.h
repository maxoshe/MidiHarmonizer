/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MidiHarmonizerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::ComboBox::Listener
{
public:
    MidiHarmonizerAudioProcessorEditor (MidiHarmonizerAudioProcessor&);
    ~MidiHarmonizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(juce::ComboBox *comboBox) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiHarmonizerAudioProcessor& audioProcessor;
    
    const juce::Colour textColour = juce::Colour::fromRGB(227, 227, 227);
    const juce::Colour rightBgColour = juce::Colour::fromRGB(34, 33, 31);
    const juce::Colour leftBgColour = juce::Colour::fromRGB(43,42,40);
    const juce::Colour comboBoxColour = juce::Colour::fromRGB(70, 70, 70);
    const juce::Colour buttonOnColour = juce::Colour::fromRGB(50, 110, 108);
    
    const int mainWindowWidth = 500;
    const int mainWindowHeight = 250;
    const int buttonWidth = 150;
    const int buttonHeight = 40;
    const int boxWidth = 300;
    const int boxHeight = 20;
    
    juce::Rectangle<int> leftPanel ,rightPanel, topPanel, topCentrePanel, bottomCentrePanel, bottomPanel, buttonRect, boxRect;
    
    juce::TextButton transposeButton, chordsButton, chordsInKeyButton;
    juce::ComboBox transposeBox, chordsBox, chordFormulaBox, keyBox, keyMinorMajorBox;
    juce::Label transposeLabel, chordsLabel, chordFormulaLabel, keyLabel, keyMinorMajorLabel;
    
    void setupTransposeButton();
    void setupChordsButton();
    void setupChordsInKeyButton();
    void setupTransposeBox();
    void setupChordsBox();
    void setupKeyBoxes();
    void setupChordFormulaBox();
    void setupTheme();
    void setupRectangles();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiHarmonizerAudioProcessorEditor)
    
};

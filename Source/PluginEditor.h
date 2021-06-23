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
    
    const juce::Colour textColour = juce::Colour::fromRGB(255, 255, 255);
    const juce::Colour rightBgColour = juce::Colour::fromRGB(41, 42, 48);
    const juce::Colour leftBgColour = juce::Colour::fromRGB(45, 48, 50);
    const juce::Colour comboBoxColour = juce::Colours::black.withAlpha(0.2f);
    const juce::Colour popupMenuColour = juce::Colour::fromRGB(32, 33, 38).withAlpha(0.95f);
    const juce::Colour borderColour = juce::Colour::fromRGB(80, 80, 85);
    const juce::Colour indicatorColour = juce::Colour::fromRGB(255, 122, 178);
    
    const int mainWindowWidth = 500;
    const int mainWindowHeight = 250;
    const int buttonWidth = 80;
    const int buttonHeight = 40;
    const int boxWidth = 300;
    const int boxHeight = 20;
    const int boxHorzPad = 10;
    const int indicatorWidth = 10;
    
    const juce::FlexItem::Margin buttonMargin  = juce::FlexItem::Margin(0, 10, 10, 10);
    const juce::FlexItem::Margin boxMargin  = juce::FlexItem::Margin(20, 0, 10, 0);
    
    juce::FlexBox leftFlexBox, rightFlexBox, keyFlexBox;
    juce::Array<juce::FlexItem> leftItems, rightItems, keyItems;
    
    juce::Rectangle<int> leftPanel ,rightPanel;
    
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
    void setupFlexBox();
    void drawRectangles(juce::Graphics& g);
    void drawButtonText(juce::Graphics& g);
    void drawIndicator(juce::Graphics& g);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiHarmonizerAudioProcessorEditor)
    
};

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
    
    juce::TextButton transposeButton;
    juce::TextButton chordsButton;
    juce::TextButton chordsInKeyButton;
    juce::ComboBox transposeBox;
    juce::ComboBox chordsBox;
    juce::ComboBox chordFormulaBox;
    juce::ComboBox keyBox;
    juce::ComboBox keyMinorMajorBox;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiHarmonizerAudioProcessorEditor)
    
};

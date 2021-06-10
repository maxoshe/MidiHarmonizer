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
    
    //old interface
    juce::ComboBox keyBox;
    juce::ComboBox keyMinorMajorBox;
    juce::ComboBox intervalBox;
    
    //new interface
    juce::TextButton transposeButton;
    juce::TextButton chordsButton;
    juce::TextButton chordsInKeyButton;
    
    juce::ComboBox transposeBox;
    juce::ComboBox chordsBox;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiHarmonizerAudioProcessorEditor)
    
};

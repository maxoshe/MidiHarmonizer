/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiHarmonizerAudioProcessorEditor::MidiHarmonizerAudioProcessorEditor (MidiHarmonizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(600, 300);
    
    //Transpose
    transposeButton.setButtonText("Transpose");
    transposeButton.setToggleState(1, juce::dontSendNotification);
    addAndMakeVisible(transposeButton);
    
    transposeBox.addItem("0 / Unison", 100);
    transposeBox.addItem("1 / Minor 2nd", 101);
    transposeBox.addItem("2 / Major 2nd", 102);
    transposeBox.addItem("3 / Minor 3d", 103);
    transposeBox.addItem("4 / Major 3rd", 104);
    transposeBox.addItem("5 / Perfect 4th", 105);
    transposeBox.addItem("6 / Tritone", 106);
    transposeBox.addItem("7 / Perfect 5th", 107);
    transposeBox.addItem("8 / Minor 6th", 108);
    transposeBox.addItem("9 / Major 6th", 109);
    transposeBox.addItem("10 / Minor 7th", 110);
    transposeBox.addItem("11 / Major 7th", 111);
    transposeBox.addItem("12 / Octave", 112);
    transposeBox.setSelectedId(100);
    transposeBox.addListener(this);
    addAndMakeVisible(transposeBox);
    
    //Chords
    chordsButton.setButtonText("Chords");
    chordsButton.setToggleState(1, juce::dontSendNotification);
    addAndMakeVisible(chordsButton);
    
    chordsBox.addItem("5th", 10);
    chordsBox.addItem("Major", 11);
    chordsBox.addItem("Minor", 12);
    chordsBox.addItem("Major 7th", 13);
    chordsBox.addItem("Minor 7th", 14);
    chordsBox.addItem("Dominant 7th", 15);
    chordsBox.addItem("Augmented", 16);
    chordsBox.addItem("Diminished", 17);
    chordsBox.addItem("Half Diminished 7th", 18);
    chordsBox.addItem("Diminished 7th", 19);
    chordsBox.setSelectedId(11);
    chordsBox.addListener(this);
    addAndMakeVisible(chordsBox);

    //Chords in Key
    chordsInKeyButton.setButtonText("Chords In Key");
    chordsInKeyButton.setToggleState(1, juce::dontSendNotification);
    addAndMakeVisible(chordsInKeyButton);
    
    chordFormulaBox.addItem("1-5", 1);
    chordFormulaBox.addItem("1-3-5", 2);
    chordFormulaBox.addItem("1-3-5-7", 3);
    chordFormulaBox.addItem("1-4-5", 4);
    chordFormulaBox.addItem("1-4-7", 5);
    chordFormulaBox.setSelectedId(1);
    chordFormulaBox.addListener(this);
    addAndMakeVisible(chordFormulaBox);
    
    keyBox.addItem("C", 12);
    keyBox.addItem("C# / Db", 13);
    keyBox.addItem("D", 14);
    keyBox.addItem("D# / Eb", 15);
    keyBox.addItem("E", 16);
    keyBox.addItem("F", 17);
    keyBox.addItem("F# / Gb", 18);
    keyBox.addItem("G", 19);
    keyBox.addItem("G# / Ab", 20);
    keyBox.addItem("A", 21);
    keyBox.addItem("A# / Bb", 22);
    keyBox.addItem("B", 23);
    keyBox.setSelectedId(12);
    keyBox.addListener(this);
    addAndMakeVisible(keyBox);
    
    keyMinorMajorBox.addItem("Major", 1);
    keyMinorMajorBox.addItem("Minor", 2);
    keyMinorMajorBox.setSelectedId(1);
    keyMinorMajorBox.addListener(this);
    addAndMakeVisible(keyMinorMajorBox);
    
}

MidiHarmonizerAudioProcessorEditor::~MidiHarmonizerAudioProcessorEditor()
{
}

//==============================================================================
void MidiHarmonizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightslategrey.brighter(3));
    
    transposeButton.setBounds(50, 50, 150, 40);
    g.drawText("Semitones / Interval", 250, 50, 300, 20, juce::Justification::centredBottom);
    transposeBox.setBounds(250, 70, 300, 20);
    
    
    chordsButton.setBounds(50, 100, 150, 40);
    g.drawText("Chord Type", 250, 100, 300, 20, juce::Justification::centredBottom);
    chordsBox.setBounds(250, 120, 300, 20);
    
    chordsInKeyButton.setBounds(50, 150, 150, 80);
    g.drawText("Key", 250, 150, 300, 20, juce::Justification::centredBottom);
    keyBox.setBounds(250, 170, 150, 20);
    keyMinorMajorBox.setBounds(400, 170, 150, 20);
    g.drawText("Chord Formula", 250, 190, 300, 20, juce::Justification::centredBottom);
    chordFormulaBox.setBounds(250, 210, 300, 20);
}

void MidiHarmonizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MidiHarmonizerAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox)
{
    //transpose mode
    audioProcessor.myMidiProcessor.setSemitones(transposeBox.getSelectedId() - 100);
    
    //chords mode
    audioProcessor.myMidiProcessor.setChordTypeID(chordsBox.getSelectedId());
    
    //chords in key mode
    audioProcessor.myMidiProcessor.setChordsFormulaID(chordFormulaBox.getSelectedId());
    audioProcessor.myMidiProcessor.populateKeyArray(keyBox.getSelectedId() - 12, keyMinorMajorBox.getSelectedId() - 1);
}

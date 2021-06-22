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
    setSize(mainWindowWidth, mainWindowHeight);
    setupTheme();
    setupFlexBox();
    
    //Transpose mode gui
    //==============================================================================
    setupTransposeButton();
    setupTransposeBox();
    addAndMakeVisible(transposeButton);
    addAndMakeVisible(transposeBox);
    
    //Chords mode gui
    //==============================================================================
    setupChordsButton();
    setupChordsBox();
    addAndMakeVisible(chordsButton);
    addAndMakeVisible(chordsBox);
    
    //Chords in Key mode gui
    //==============================================================================
    setupChordsInKeyButton();
    setupKeyBoxes();
    setupChordFormulaBox();
    addAndMakeVisible(chordsInKeyButton);
    addAndMakeVisible(keyBox);
    addAndMakeVisible(keyMinorMajorBox);
    addAndMakeVisible(chordFormulaBox);
}

MidiHarmonizerAudioProcessorEditor::~MidiHarmonizerAudioProcessorEditor()
{
}

//==============================================================================
void MidiHarmonizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    setupRectangles();
    g.setColour(leftBgColour);
    g.fillRect(leftPanel);
    g.setColour(rightBgColour);
    g.fillRect(rightPanel);
    leftFlexBox.performLayout(leftPanel.withSizeKeepingCentre(leftPanel.getWidth(),
                                                              leftPanel.getHeight()*4/5));
    rightFlexBox.performLayout(rightPanel.withSizeKeepingCentre(rightPanel.getWidth()-boxHorzPad,
                                                                rightPanel.getHeight()*4/5));
}

void MidiHarmonizerAudioProcessorEditor::resized()
{
    if (getWidth() < mainWindowWidth) {
        setSize(mainWindowWidth, getHeight());
    }
    if (getHeight() < mainWindowHeight) {
        setSize(getWidth(), mainWindowHeight);
    }
}

void MidiHarmonizerAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox)
{
    //transpose mode
    audioProcessor.myMidiProcessor.setSemitones(transposeBox.getSelectedId() - 100);
    
    //chords mode
    audioProcessor.myMidiProcessor.setChordTypeID(chordsBox.getSelectedId());
    
    //chords in key mode
    audioProcessor.myMidiProcessor.setChordsFormulaID(chordFormulaBox.getSelectedId());
    audioProcessor.myMidiProcessor.populateKeyArray(keyBox.getSelectedId() - 12,
                                                    keyMinorMajorBox.getSelectedId() - 1);
}

void MidiHarmonizerAudioProcessorEditor::setupTransposeButton()
{
    transposeButton.setButtonText("Transpose");
    transposeButton.setToggleState(1, juce::dontSendNotification);
    transposeButton.setRadioGroupId(100);
    transposeButton.onClick = [this]
    {
        transposeButton.setToggleState(1, juce::dontSendNotification);
        audioProcessor.myMidiProcessor.setModeID(1);
        transposeBox.setEnabled(1);
        chordsBox.setEnabled(0);
        keyBox.setEnabled(0);
        keyMinorMajorBox.setEnabled(0);
        chordFormulaBox.setEnabled(0);
    };
}

void MidiHarmonizerAudioProcessorEditor::setupChordsButton()
{
    chordsButton.setButtonText("Chords");
    chordsButton.setToggleState(0, juce::dontSendNotification);
    chordsButton.setRadioGroupId(100);
    chordsButton.onClick = [this]
    {
        chordsButton.setToggleState(1, juce::dontSendNotification);
        audioProcessor.myMidiProcessor.setModeID(2);
        transposeBox.setEnabled(0);
        chordsBox.setEnabled(1);
        keyBox.setEnabled(0);
        keyMinorMajorBox.setEnabled(0);
        chordFormulaBox.setEnabled(0);
    };
}

void MidiHarmonizerAudioProcessorEditor::setupChordsInKeyButton()
{
    chordsInKeyButton.setButtonText("Chords In Key");
    chordsInKeyButton.setToggleState(0, juce::dontSendNotification);
    chordsInKeyButton.setRadioGroupId(100);
    chordsInKeyButton.onClick = [this]
    {
        chordsInKeyButton.setToggleState(1, juce::dontSendNotification);
        audioProcessor.myMidiProcessor.setModeID(3);
        transposeBox.setEnabled(0);
        chordsBox.setEnabled(0);
        keyBox.setEnabled(1);
        keyMinorMajorBox.setEnabled(1);
        chordFormulaBox.setEnabled(1);
    };
}

void MidiHarmonizerAudioProcessorEditor::setupTransposeBox()
{
    transposeLabel.setText("Semitones / Interval", juce::dontSendNotification);
    transposeLabel.attachToComponent(&transposeBox, 0);
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
}

void MidiHarmonizerAudioProcessorEditor::setupChordsBox()
{
    chordsLabel.setText("Chord", juce::dontSendNotification);
    chordsLabel.attachToComponent(&chordsBox, 0);
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
    chordsBox.setEnabled(0);
    chordsBox.addListener(this);
}

void MidiHarmonizerAudioProcessorEditor::setupKeyBoxes()
{
    keyLabel.setText("Key", juce::dontSendNotification);
    keyLabel.attachToComponent(&keyBox, 0);
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
    keyBox.setEnabled(0);
    keyBox.addListener(this);
    
    keyMinorMajorBox.addItem("Major", 1);
    keyMinorMajorBox.addItem("Minor", 2);
    keyMinorMajorBox.setSelectedId(1);
    keyMinorMajorBox.addListener(this);
    keyMinorMajorBox.setEnabled(0);
}

void MidiHarmonizerAudioProcessorEditor::setupChordFormulaBox()
{
    chordFormulaLabel.setText("Chord Formula", juce::dontSendNotification);
    chordFormulaLabel.attachToComponent(&chordFormulaBox, 0);
    chordFormulaBox.addItem("1-5", 1);
    chordFormulaBox.addItem("1-3-5", 2);
    chordFormulaBox.addItem("1-3-5-7", 3);
    chordFormulaBox.addItem("1-4-5", 4);
    chordFormulaBox.addItem("1-4-7", 5);
    chordFormulaBox.setSelectedId(2);
    chordFormulaBox.setEnabled(0);
    chordFormulaBox.addListener(this);
}

void MidiHarmonizerAudioProcessorEditor::setupTheme()
{
    getLookAndFeel().setColour(juce::ComboBox::outlineColourId,
                               juce::Colours::transparentBlack);
    
    getLookAndFeel().setColour(juce::ComboBox::textColourId,
                               textColour);
    
    getLookAndFeel().setColour(juce::PopupMenu::textColourId,
                               textColour);
    
    getLookAndFeel().setColour(juce::TextButton::textColourOnId,
                               textColour);
    
    getLookAndFeel().setColour(juce::TextButton::textColourOnId,
                               textColour);
    
    getLookAndFeel().setColour(juce::TextButton::textColourOffId,
                               textColour);
    
    getLookAndFeel().setColour(juce::Label::textColourId,
                               textColour);
    
    getLookAndFeel().setColour(juce::ComboBox::backgroundColourId,
                               comboBoxColour);
    
    getLookAndFeel().setColour(juce::PopupMenu::backgroundColourId,
                               rightBgColour.withAlpha(0.8f));
    
    getLookAndFeel().setColour(juce::PopupMenu::highlightedBackgroundColourId,
                               comboBoxColour);
    
    getLookAndFeel().setColour(juce::TextButton::buttonColourId,
                               leftBgColour);
    
    getLookAndFeel().setColour(juce::TextButton::buttonOnColourId,
                               buttonOnColour);
}

void MidiHarmonizerAudioProcessorEditor::setupRectangles()
{
    leftPanel = getBounds().withRight(getWidth()/3);
    rightPanel = getBounds().withLeft(getWidth()/3);
}

void MidiHarmonizerAudioProcessorEditor::setupFlexBox()
{
    //left Panel
    leftItems.add(juce::FlexItem(buttonWidth,
                                 buttonHeight,
                                 transposeButton).withMargin(buttonMargin));
    leftItems.add(juce::FlexItem(buttonWidth,
                                 buttonHeight,
                                 chordsButton).withMargin(buttonMargin));
    leftItems.add(juce::FlexItem(buttonWidth,
                                 buttonHeight,
                                 chordsInKeyButton).withMargin(buttonMargin));
    leftFlexBox.flexDirection = juce::FlexBox::Direction::column;
    leftFlexBox.alignContent = juce::FlexBox::AlignContent::stretch;
    leftFlexBox.items = leftItems;
    
    
    //key box
    keyItems.add(juce::FlexItem(boxWidth/2, boxHeight, keyBox));
    keyItems.add(juce::FlexItem(boxWidth/2, boxHeight, keyMinorMajorBox));
    keyFlexBox.flexDirection = juce::FlexBox::Direction::column;
    keyFlexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    keyFlexBox.alignContent = juce::FlexBox::AlignContent::stretch;
    keyFlexBox.justifyContent = juce::FlexBox::JustifyContent::center;
    keyFlexBox.items = keyItems;
    
    //RightPanel
    rightItems.add(juce::FlexItem(boxWidth,
                                  boxHeight,
                                  transposeBox).withMargin(boxMargin));
    rightItems.add(juce::FlexItem(boxWidth,
                                  boxHeight,
                                  chordsBox).withMargin(boxMargin));
    rightItems.add(juce::FlexItem(boxWidth,
                                  boxHeight,
                                  keyFlexBox).withMargin(boxMargin));
    rightItems.add(juce::FlexItem(boxWidth,
                                  boxHeight,
                                  chordFormulaBox).withMargin(boxMargin));
    rightFlexBox.flexDirection = juce::FlexBox::Direction::column;
    rightFlexBox.alignContent = juce::FlexBox::AlignContent::stretch;
    rightFlexBox.items = rightItems;
    
}

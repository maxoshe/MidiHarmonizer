/*
  ==============================================================================

    MidiProcessor.h
    Created: 7 Jun 2021 1:01:12pm
    Author:  Moshe Stanylov

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MidiProcessor
{
private:
    //midi pitches in C major and C minor keys, used by populateKeyArray()
    const int cMajor[7] = {0, 2, 4, 5, 7, 9, 11};
    const int cMinor[7] = {0, 2, 3, 5, 7, 8, 10};
    
    int modeID = 1;
    int semitones;
    int chordTypeID;
    int chordFormulaID;
    int noteStatus[128] = {0};
    
    juce::MidiMessage messege;
    int sample;
    
    std::vector<int> pitchesInKey;
    juce::MidiBuffer processedMidi;
    
    //add a fixed interval to processedMidi, interval is the number of semitones from reference note
    void addFixedInterval(juce::MidiMessage messege, int sample, int interval);
    //add a step in the key of chice to processedMidi
    void addStepInKey(juce::MidiMessage messege, int sample, int step);
    //checks if a note is in key of choice
    bool inKey(int note);
    //update note status array based on messege
    void updateNoteStatusArray(juce::MidiMessage& messege);
    //check if the note should be on or off based on note status array and messege
    bool noteIsNotInDesiredStatus(juce::MidiMessage& messege);

    void transposeMode();
    void chordMode();
    void chordsInKeyMode();
    
public:
    int getModeID() {return modeID;}
    void setModeID(int choice);
    void setSemitones(int choice);
    void setChordTypeID(int choice);
    void setChordsFormulaID(int choice);
    //populates the pitchesInKey array,
    void populateKeyArray(int keyOffset, bool keyIsMinor);
    //process the midi buffer, used by the plugin processor
    void process(juce::MidiBuffer& midiMesseges);
};

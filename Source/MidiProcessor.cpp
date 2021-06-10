/*
  ==============================================================================

    MidiProcessor.cpp
    Created: 7 Jun 2021 1:01:12pm
    Author:  Moshe Stanylov

  ==============================================================================
*/

#include "MidiProcessor.h"

void MidiProcessor::process(juce::MidiBuffer& midiMesseges)
{
    processedMidi.clear();
    for (const auto metaData : midiMesseges)
    {
        auto messege = metaData.getMessage();
        auto sample = metaData.samplePosition;
        if (messege.isNoteOnOrOff())
        {
            switch (mode) {
                case 1:
                    addStepInKey(messege, sample, 1);
                    addStepInKey(messege, sample, 5);
                    break;
                case 2:
                    addStepInKey(messege, sample, 1);
                    addStepInKey(messege, sample, 3);
                    addStepInKey(messege, sample, 5);
                    break;
                case 3:
                    addStepInKey(messege, sample, 1);
                    addStepInKey(messege, sample, 3);
                    addStepInKey(messege, sample, 5);
                    addStepInKey(messege, sample, 7);
                    break;
                case 4:
                    addStepInKey(messege, sample, 1);
                    addStepInKey(messege, sample, 4);
                    addStepInKey(messege, sample, 5);
                    break;
                case 5:
                    addStepInKey(messege, sample, 1);
                    addStepInKey(messege, sample, 4);
                    addStepInKey(messege, sample, 7);
                    break;
                    
                default:
                    break;
            }
        }
        else
        {
            processedMidi.addEvent(messege, sample);
        }
        
    }
    midiMesseges.swapWith(processedMidi);
}

void MidiProcessor::addFixedInterval(juce::MidiMessage messege, int sample, int interval)
{
    messege.setNoteNumber(messege.getNoteNumber() + interval);
    processedMidi.addEvent(messege, sample);
}

void MidiProcessor::addStepInKey(juce::MidiMessage messege, int sample, int step)
{
    int midiInterval;
    int noteNum = messege.getNoteNumber();
    int noteBase = noteNum % 12;
    if (not inKey(noteBase))
    {
        noteBase++;
        noteNum++;
    }
    for (int i = 0; i < 8; i++)
    {
        if (pitchesInKey[i] == noteBase)
        {
            midiInterval = pitchesInKey[i+step-1] - noteBase;
        }
    }
    messege.setNoteNumber(noteNum + midiInterval);
    processedMidi.addEvent(messege, sample);
}

void MidiProcessor::populateKeyArray(int keyOffset, bool keyIsMinor)
{
    pitchesInKey.clear();
    if (keyIsMinor)
    {
        for (int pitch : cMinor)
        {
            pitchesInKey.push_back(pitch + keyOffset);
        }
    }
    else
    {
        for (int pitch : cMajor)
        {
            pitchesInKey.push_back(pitch + keyOffset);
        }
    }
    while (pitchesInKey.back() >= 12)
    {
        pitchesInKey.insert(pitchesInKey.begin(), pitchesInKey.back() - 12);
        pitchesInKey.pop_back();
    }
    for (int pitch : pitchesInKey)
    {
        pitchesInKey.push_back(pitch + 12);
    }
}

bool MidiProcessor::inKey(int note)
{
    bool inKey = false;
    for (int step = 0; step < 8; step++)
    {
        if (pitchesInKey[step] == note)
        {
            inKey = true;
        }
    }
    return inKey;
}

void MidiProcessor::setMode(int choice)
{
    mode = choice;
}

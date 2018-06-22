/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioSandBoxAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    AudioSandBoxAudioProcessorEditor (AudioSandBoxAudioProcessor&);
    ~AudioSandBoxAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider*) override;

private:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> slidePtr;
    Slider slide;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioSandBoxAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSandBoxAudioProcessorEditor)
};

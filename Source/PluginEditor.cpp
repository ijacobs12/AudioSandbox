/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioSandBoxAudioProcessorEditor::AudioSandBoxAudioProcessorEditor (AudioSandBoxAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(&slide);
    slide.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    slide.addListener(this);
    slide.setRange(1,50,1);
    slide.setValue(1);
}

AudioSandBoxAudioProcessorEditor::~AudioSandBoxAudioProcessorEditor()
{
}

void AudioSandBoxAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    processor.setDelayValue((int)slider->getValue()); //this will be VERY dumb once there's more than one slider.
};
//==============================================================================
void AudioSandBoxAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void AudioSandBoxAudioProcessorEditor::resized()
{
    slide.setBounds(getLocalBounds());
}

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
    slidePtr.reset(new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "slider Value", slide));
}

AudioSandBoxAudioProcessorEditor::~AudioSandBoxAudioProcessorEditor()
{
    slidePtr.reset();
}

void AudioSandBoxAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    
}


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

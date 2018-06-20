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
    slide.setRange(1,2000,1);
    slide.setValue(1);
}

AudioSandBoxAudioProcessorEditor::~AudioSandBoxAudioProcessorEditor()
{
}

void AudioSandBoxAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    processor.setDelayValue((int)slider->getValue()); //this will be VERY dumb once there's more than one slider. but will there be...?
};
//==============================================================================
void AudioSandBoxAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour(Colours::aqua);
    g.drawText("L/R channel sample difference", getBounds().removeFromBottom(getHeight()/4), Justification::centred);

}

void AudioSandBoxAudioProcessorEditor::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    slide.setBounds(bounds.removeFromTop(3*bounds.getHeight()/4));
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioSandBoxAudioProcessor::AudioSandBoxAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    index = 0;
    delaySamps = 1;
}

AudioSandBoxAudioProcessor::~AudioSandBoxAudioProcessor()
{
}

//==============================================================================
const String AudioSandBoxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioSandBoxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioSandBoxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioSandBoxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioSandBoxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioSandBoxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

double AudioSandBoxAudioProcessor::delayLine(double x) {
    double y = array[index];
    array[index++] = x;
    index %= delaySamps;
    return y;
}

int AudioSandBoxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioSandBoxAudioProcessor::setDelayValue(int num) {
    delaySamps = num;
}

void AudioSandBoxAudioProcessor::setCurrentProgram (int index)
{
}

const String AudioSandBoxAudioProcessor::getProgramName (int index)
{
    return {};
}

void AudioSandBoxAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AudioSandBoxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    sampRate = sampleRate;
}

void AudioSandBoxAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudioSandBoxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void AudioSandBoxAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); sample ++) {
            channelData[sample] = .5*(buffer.getSample(channel,sample)+delayLine(buffer.getSample(channel,sample))); //adding or subtracting seem to do different things!
        }
        
    }
}

//==============================================================================
bool AudioSandBoxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AudioSandBoxAudioProcessor::createEditor()
{
    return new AudioSandBoxAudioProcessorEditor (*this);
}

//==============================================================================
void AudioSandBoxAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AudioSandBoxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioSandBoxAudioProcessor();
}

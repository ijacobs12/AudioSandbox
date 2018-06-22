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
                       ),
tree(*this,nullptr)
#endif
{

    left_index = 0.;
    right_index = 0.;
    delaySampsL = 1.;
    delaySampsR = 1;
    finishedLeftLoop = false;
    finishedRightLoop = false;
    NormalisableRange<float> slideRange (1.,500.);
    tree.createAndAddParameter("slider Value", "slidVal", "slidVal", slideRange, 1., nullptr, nullptr);
    
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

float AudioSandBoxAudioProcessor::delayLineLeft(float input) {
    finishedLeftLoop = false;
    float diff = fmod(left_index, 1.);
    left_index -= diff;
    int prev = floorf(left_index);
    int next = ceilf(left_index);
    float y = leftArray[prev]+diff*(leftArray[next]-leftArray[prev]); //interpolate the fractional part!
    leftArray[(int)left_index++] = input;
    if(left_index != fmod(left_index,delaySampsL)){
        left_index = fmod(left_index,delaySampsL);
        finishedLeftLoop = true;
    }
    return y;
}

//there must be a more elegant way of doing this than splitting it up left right. hopefully I figure it out one day! 'till then....

float AudioSandBoxAudioProcessor::delayLineRight(float input) {
    finishedRightLoop = false;
    float diff = fmod(right_index, 1.);
    right_index -= diff;
    int prev = floorf(right_index);
    int next = ceilf(right_index);
    float y = rightArray[prev]+diff*(rightArray[next]-rightArray[prev]); //interpolate the fractional part!
    rightArray[(int)right_index++] = input;
    if(right_index != fmod(right_index,delaySampsR)){
        right_index = fmod(right_index,delaySampsR);
        finishedRightLoop = true;

    }
    return y;
}

int AudioSandBoxAudioProcessor::getCurrentProgram()
{
    return 0;
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
    float* channelDataLeft = buffer.getWritePointer (0);
    float* channelDataRight = buffer.getWritePointer (1);
    for (int sample = 0; sample < buffer.getNumSamples(); sample ++) {
        if(finishedRightLoop)delaySampsR = *tree.getRawParameterValue("slider Value");
        if(finishedLeftLoop)delaySampsL = *tree.getRawParameterValue("slider Value");
        channelDataLeft[sample] = .5*(buffer.getSample(0,sample)-delayLineLeft(buffer.getSample(0,sample))); //adding or subtracting seem to do different things!
        channelDataRight[sample] = .5*(buffer.getSample(1,sample)-delayLineRight(buffer.getSample(1,sample)));

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

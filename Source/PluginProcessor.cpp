/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Soft_ClipingAudioProcessor::Soft_ClipingAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
	:
#endif
parameters(*this,
	nullptr,
	juce::Identifier("Soft_cliping"),
	{ std::make_unique<juce::AudioParameterFloat>(
		"Gain_Parameter",
		"Gain Parameter",
		juce::Range{0.5f,2.0f},
		1.0f),
	std::make_unique<juce::AudioParameterFloat>(
		"Param_Parameter",
		"Param Parameter",
		juce::Range{0.f,10.f},
		1.0f),
	std::make_unique<juce::AudioParameterFloat>(
		"ChoiceHold_Parameter",
		"ChoiceHold Parameterr",
		juce::Range{0.f,8.f},
		0.0f)
	})
{
	GainParameter = parameters.getRawParameterValue("Gain_Parameter");
	ParamParameter = parameters.getRawParameterValue("Param_Parameter");
	ChoiceHoldParameter = parameters.getRawParameterValue("ChoiceHold_Parameter");
}

Soft_ClipingAudioProcessor::~Soft_ClipingAudioProcessor()
{
}

//==============================================================================
const juce::String Soft_ClipingAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Soft_ClipingAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Soft_ClipingAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Soft_ClipingAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Soft_ClipingAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Soft_ClipingAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Soft_ClipingAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Soft_ClipingAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Soft_ClipingAudioProcessor::getProgramName (int index)
{
    return {};
}

void Soft_ClipingAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Soft_ClipingAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Soft_ClipingAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Soft_ClipingAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void Soft_ClipingAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	float Gain = GainParameter->load();
	float Param = ParamParameter->load();

	int Choice = static_cast<int>(floor(ChoiceHoldParameter->load()));

	

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
		
		for (int i = 0; i < buffer.getNumSamples(); ++i)
		{
			switch (Choice)
			{
			case 0:
				channelData[i] = Cliping.ArrayaCliping(channelData[i], Gain);
				break;
			case 1:
				channelData[i] = Cliping.SigmoidCliping(channelData[i], Param, Gain);
				break;
			case 2:
				channelData[i] = Cliping.Sigmoid2Cliping(channelData[i], Gain);
				break;
			case 3:
				channelData[i] = Cliping.FuzzExponentialCliping(channelData[i], Param, Gain);
				break;
			case 4:
				channelData[i] = Cliping.FuzzExponential2Cliping(channelData[i], Gain);
				break;
			case 5:
				channelData[i] = Cliping.SquareSignCliping(channelData[i], Gain);
				break;
			case 6:
				channelData[i] = Cliping.AbsoluteSquareCliping(channelData[i], Param, Gain);
				break;

			default:
				break;
			}
			
		}  
    }
}

//==============================================================================
bool Soft_ClipingAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Soft_ClipingAudioProcessor::createEditor()
{
	return new Soft_ClipingAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void Soft_ClipingAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Soft_ClipingAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Soft_ClipingAudioProcessor();
}

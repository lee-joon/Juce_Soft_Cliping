/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Soft_ClipingAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Soft_ClipingAudioProcessorEditor (Soft_ClipingAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~Soft_ClipingAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Soft_ClipingAudioProcessor& audioProcessor;

	juce::Slider GainSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> GainAttachment;
	juce::Label GainLabel;

	juce::Slider ParamSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ParamAttachment;
	juce::Label ParamLabel;

	juce::Slider ChoiceHoldSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ChoiceHoldAttachment;
	juce::Label ChoiceHoldLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Soft_ClipingAudioProcessorEditor)
};

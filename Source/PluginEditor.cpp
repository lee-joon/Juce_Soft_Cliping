/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Soft_ClipingAudioProcessorEditor::Soft_ClipingAudioProcessorEditor (Soft_ClipingAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	addAndMakeVisible(GainSlider);
	GainSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	GainAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Gain_Parameter", GainSlider));

	addAndMakeVisible(GainLabel);
	GainLabel.setText("Gain Parameter",
		juce::dontSendNotification);

	//////////////////////////////////////////////////////////////////////
	addAndMakeVisible(ParamSlider);
	ParamSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	ParamAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Param_Parameter", ParamSlider));

	addAndMakeVisible(ParamLabel);
	ParamLabel.setText("Param Parameter",
		juce::dontSendNotification);

	//////////////////////////////////////////////////////////////////////
	addAndMakeVisible(ChoiceHoldSlider);
	ChoiceHoldSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	ChoiceHoldAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "ChoiceHold_Parameter", ChoiceHoldSlider));

	addAndMakeVisible(ChoiceHoldLabel);
	ChoiceHoldLabel.setText("ChoiceHold Parameter",
		juce::dontSendNotification);

	setSize(800, 400);
}

Soft_ClipingAudioProcessorEditor::~Soft_ClipingAudioProcessorEditor()
{
}

//==============================================================================
void Soft_ClipingAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void Soft_ClipingAudioProcessorEditor::resized()
{
	GainSlider.setBounds({ 15, 35, 300, 300 });
	GainLabel.setBounds({ GainSlider.getX() + 30,
									GainSlider.getY() - 30,
									200, 50 });


	ParamSlider.setBounds({ 215, 35, 300, 300 });
	ParamLabel.setBounds({ ParamSlider.getX() + 30,
									ParamSlider.getY() - 30,
									200, 50 });

	ChoiceHoldSlider.setBounds({ 415, 35, 300, 300 });
	ChoiceHoldLabel.setBounds({ ChoiceHoldSlider.getX() + 30,
									ChoiceHoldSlider.getY() - 30,
									200, 50 });



}

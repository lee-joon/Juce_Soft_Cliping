/*
  ==============================================================================

    Soft_Cliping.h
    Created: 1 Jul 2023 12:26:29am
    Author:  JUNLEE

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include <juce_core/juce_core.h>
#include <cmath>


class SoftClipimg {


public:
	float SampleGain(float input, float gain){
	
		return  juce::jlimit(-1.0f, 1.0f, input * gain);//clamp
	}

	float SampleDeGain(float input, float gain) {

		return input / gain;
	}


	float sgn(float input) {


		return (input >= 0) ? 1.0f : -1.0f;
	}

   //1
	float ArrayaCliping(float input, float gain = 1.0f){


		float inputsample = SampleGain(input, gain);


		float outSample = (3 * inputsample / 2) * (1 - pow(inputsample, 2) / 3);


		return SampleDeGain(outSample, gain);
		
    }


	//2
	float SigmoidCliping(float input, float Param, float gain = 1.0f) {


		//param --> 2.5~~~~~~~

		float inputsample = SampleGain(input, gain);


		float outSample = 2 * (1 / (1 + exp(-Param * inputsample))) - 1;


		return SampleDeGain(outSample, gain);

	}
	//3
	float Sigmoid2Cliping(float input,  float gain = 1.0f) {



		float inputsample = SampleGain(input, gain);

		float numerator = (exp(input) - 1) * (exp(1) + 1);
		float denominator = (exp(input) + 1) * (exp(1) - 1);

		float outSample = numerator / denominator;


		return SampleDeGain(outSample, gain);

	}
	//4
	float FuzzExponentialCliping(float input, float Param, float gain = 1.0f) {



		float inputsample = SampleGain(input, gain);


		float outSample = sgn(inputsample) * ((1 - exp(-fabs(Param * inputsample))) / (1 - exp(-Param)));


		return SampleDeGain(outSample, gain);

	}

	//5
	float FuzzExponential2Cliping(float input, float gain = 1.0f) {



		float inputsample = SampleGain(input, gain);


		float outSample = sgn(-inputsample) * ((1 - exp(fabs(inputsample))) / (exp(1) - 1));


		return SampleDeGain(outSample, gain);

	}

	//6
	float SquareSignCliping(float input, float gain = 1.0f) {



		float inputsample = SampleGain(input, gain);


		float outSample = inputsample * inputsample * ((inputsample >= 0) ? 1.0f : -1.0f);


		return SampleDeGain(outSample, gain);

	}
	//7
	float AbsoluteSquareCliping(float input, float Param, float gain = 1.0f) {



		float inputsample = SampleGain(input, gain);


		float outSample =  pow(fabs(inputsample), Param / 2.0f) * ((inputsample >= 0) ? 1.0f : -1.0f);


		return SampleDeGain(outSample, gain);

	}



};
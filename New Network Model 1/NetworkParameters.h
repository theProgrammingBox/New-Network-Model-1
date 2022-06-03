#pragma once
#include "Header.h"

class NetworkParameters
{
public:
	unsigned int numNodes;
	unsigned int numInputs;
	unsigned int numOutputs;

	float* initialState = nullptr;
	float* inputToMultWeights = nullptr;
	float* stateToMultWeights = nullptr;
	float* inputToAddWeights = nullptr;
	float* stateToAddWeights = nullptr;
	float* outputWeights = nullptr;
	float* multBiases = nullptr;
	float* addBiases = nullptr;
	float* outputBiases = nullptr;

	NetworkParameters(unsigned int numNodes, unsigned int numInputs, unsigned int numOutputs);
	~NetworkParameters();

	void Initialize();
	void Import();

	void Export();
};
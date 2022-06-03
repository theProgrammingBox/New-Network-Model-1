#pragma once
#include "NetworkParameters.h"

class Network
{
public:
	bool shared;
	NetworkParameters* networkParameters = nullptr;

	Network(unsigned int numNodes, unsigned int numInputs, unsigned int numOutputs);
	Network(NetworkParameters* networkParameters);
	~Network();

	void Forwardpropagate(float* input, float* output);
};

Network::Network(unsigned int numNodes, unsigned int numInputs, unsigned int numOutputs)
{
	networkParameters = new NetworkParameters(numNodes, numInputs, numOutputs);
	assert(networkParameters != NULL);
	//networkParameters->Import();
	networkParameters->Initialize();
	shared = false;
}

Network::Network(NetworkParameters* networkParameters)
{
	this->networkParameters = networkParameters;
	shared = true;
}

Network::~Network()
{
	if (!shared)
	{
		delete networkParameters;
	}
}

void Network::Forwardpropagate(float* input, float* output)
{
	//
}
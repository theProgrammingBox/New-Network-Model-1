#pragma once
#include "NetworkParameters.h"

class Network
{
public:
	NetworkParameters* networkParameters;

	Network(NetworkParameters* networkParameters);
	~Network();
};
#include "NetworkParameters.h"

int main()
{
	NetworkParameters networkParameters(3, 1, 1, 1);
	//networkParameters.Initialize();
	networkParameters.Import();
	networkParameters.Export();

	return 0;
}
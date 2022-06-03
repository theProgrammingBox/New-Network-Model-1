#include "NetworkParameters.h"

int main()
{
	NetworkParameters networkParameters(2, 2, 2);
	networkParameters.Import();
	networkParameters.Export();

	return 0;
}
//#include "NetworkParameters.h"	
//
//NetworkParameters::NetworkParameters(unsigned int numNodes, unsigned int numInputs, unsigned int numOutputs)
//{
//	this->numNodes = numNodes;
//	this->numInputs = numInputs;
//	this->numOutputs = numOutputs;
//
//	initialState = (float*)malloc(numNodes * sizeof(float));
//	assert(initialState != NULL);
//	inputToMultWeights = (float*)malloc(numNodes * numInputs * sizeof(float));
//	assert(inputToMultWeights != NULL);
//	stateToMultWeights = (float*)malloc(numNodes * numNodes * sizeof(float));
//	assert(stateToMultWeights != NULL);
//	inputToAddWeights = (float*)malloc(numNodes * numInputs * sizeof(float));
//	assert(inputToAddWeights != NULL);
//	stateToAddWeights = (float*)malloc(numNodes * numNodes * sizeof(float));
//	assert(stateToAddWeights != NULL);
//	outputWeights = (float*)malloc(numNodes * numOutputs * sizeof(float));
//	assert(outputWeights != NULL);
//	multBiases = (float*)malloc(numNodes * sizeof(float));
//	assert(multBiases != NULL);
//	addBiases = (float*)malloc(numNodes * sizeof(float));
//	assert(addBiases != NULL);
//	outputBiases = (float*)malloc(numOutputs * sizeof(float));
//	assert(outputBiases != NULL);
//}
//
//NetworkParameters::~NetworkParameters()
//{
//	delete[] initialState;
//	delete[] inputToMultWeights;
//	delete[] stateToMultWeights;
//	delete[] inputToAddWeights;
//	delete[] stateToAddWeights;
//	delete[] outputWeights;
//	delete[] multBiases;
//	delete[] addBiases;
//	delete[] outputBiases;
//}
//
//void NetworkParameters::Initialize()
//{
//	for (int i = 0; i < numNodes; i++)
//	{
//		initialState[i] = 0.0f;
//	}
//
//	int row;
//
//	for (int i = 0; i < numNodes; i++)
//	{
//		row = i * numInputs;
//
//		for (int j = 0; j < numInputs; j++)
//		{
//			inputToMultWeights[row + j] = 0.0f;
//			inputToAddWeights[row + j] = 0.0f;
//		}
//	}
//
//	for (int i = 0; i < numNodes; i++)
//	{
//		row = i * numNodes;
//
//		for (int j = 0; j < numNodes; j++)
//		{
//			stateToMultWeights[row + j] = (i == j ? 1.0f : 0.0f);
//			stateToAddWeights[row + j] = (i == j ? 1.0f : 0.0f);
//		}
//	}
//
//	for (int i = 0; i < numOutputs; i++)
//	{
//		row = i * numOutputs;
//
//		for (int j = 0; j < numNodes; j++)
//		{
//			outputWeights[row + j] = 0.0f;
//		}
//	}
//
//	for (int i = 0; i < numNodes; i++)
//	{
//		multBiases[i] = 0.0f;
//		addBiases[i] = 0.0f;
//	}
//
//	for (int i = 0; i < numOutputs; i++)
//	{
//		outputBiases[i] = 0.0f;
//	}
//}
//
//bool comparitor(string a, string b)
//{
//	int aMonth, aDay, aYear, aHour, aMinute, aSecond;
//	int bMonth, bDay, bYear, bHour, bMinute, bSecond;
//
//	aMonth = stoi(a.substr(0, 2));
//	aDay = stoi(a.substr(3, 2));
//	aYear = stoi(a.substr(6, 4));
//	aHour = stoi(a.substr(11, 2));
//	aMinute = stoi(a.substr(14, 2));
//	aSecond = stoi(a.substr(17, 2));
//
//	bMonth = stoi(b.substr(0, 2));
//	bDay = stoi(b.substr(3, 2));
//	bYear = stoi(b.substr(6, 4));
//	bHour = stoi(b.substr(11, 2));
//	bMinute = stoi(b.substr(14, 2));
//	bSecond = stoi(b.substr(17, 2));
//
//	unsigned long long aTime =
//		aYear * 1000000000000 +
//		aMonth * 100000000 +
//		aDay * 1000000 +
//		aHour * 10000 +
//		aMinute * 100 +
//		aSecond;
//
//	unsigned long long bTime =
//		bYear * 1000000000000 +
//		bMonth * 100000000 +
//		bDay * 1000000 +
//		bHour * 10000 +
//		bMinute * 100 +
//		bSecond;
//
//	return aTime > bTime;
//}
//
//void NetworkParameters::Import()
//{
//	cout << "IMPORT OPTIONS" << endl;
//	cout << "Option" << setw(6) << 0 << ": Initialize New Network\n";
//	vector<string> files;
//	if (auto dir = opendir("./Program Logs/"))
//	{
//		while (auto f = readdir(dir)) {
//			if (f->d_name && f->d_name[0] != '.')
//			{
//				files.push_back(f->d_name);
//			}
//		}
//		closedir(dir);
//
//		sort(files.begin(), files.end(), comparitor);
//
//		for (int i = 0; i < files.size(); i++)
//		{
//			cout << "Option" << setw(6) << i + 1 << ": " << files[i] << endl;
//		}
//	}
//
//	int choice;
//	do
//	{
//		cout << "Select an option (Enter 0 for default): ";
//	} while (ErrorCheckIntInput(choice, 0, files.size()));
//
//	if (choice == 0)
//	{
//		cout << "Initializing New Network" << endl;
//		Initialize();
//	}
//	else
//	{
//		cout << "Importing Network from file: " << files[choice - 1] << endl;
//		string path = "./Program Logs/" + files[choice - 1];
//		ifstream file;
//		file.open(path);
//		string label;
//		unsigned int value;
//
//		file >> label;
//		if (label != "numNodes:")
//		{
//			cout << "Error: Expected numNodes: but found " << label << endl;
//			assert(false);
//		}
//		file >> value;
//		if (value != numNodes)
//		{
//			cout << "Error: Expected numNodes: " << numNodes << " but found " << value << endl;
//			assert(false);
//		}
//		cout << label << " " << value << endl;
//
//		file >> label;
//		if (label != "numInputs:")
//		{
//			cout << "Error: Expected numInputs: but found " << label << endl;
//			assert(false);
//		}
//		file >> value;
//		if (value != numInputs)
//		{
//			cout << "Error: Expected numInputs: " << numInputs << " but found " << value << endl;
//			assert(false);
//		}
//		cout << label << " " << value << endl;
//
//		file >> label;
//		if (label != "numOutputs:")
//		{
//			cout << "Error: Expected numOutputs: but found " << label << endl;
//			assert(false);
//		}
//		file >> value;
//		if (value != numOutputs)
//		{
//			cout << "Error: Expected numOutputs: " << numOutputs << " but found " << value << endl;
//			assert(false);
//		}
//		cout << label << " " << value << endl;
//
//		file >> label;
//		if (label != "initialState:")
//		{
//			cout << "Error: Expected numInputs: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			file >> value;
//			initialState[i] = value;
//			cout << value << " ";
//		}
//		cout << "\n\n";
//
//		file >> label;
//		if (label != "inputToMultWeights:")
//		{
//			cout << "Error: Expected inputToMultWeights: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			for (int j = 0; j < numInputs; j++)
//			{
//				file >> value;
//				inputToMultWeights[i * numInputs + j] = value;
//				cout << value << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//
//		file >> label;
//		if (label != "stateToMultWeights:")
//		{
//			cout << "Error: Expected stateToMultWeights: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			for (int j = 0; j < numNodes; j++)
//			{
//				file >> value;
//				stateToMultWeights[i * numNodes + j] = value;
//				cout << value << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//
//		file >> label;
//		if (label != "inputToAddWeights:")
//		{
//			cout << "Error: Expected inputToAddWeights: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			for (int j = 0; j < numInputs; j++)
//			{
//				file >> value;
//				inputToAddWeights[i * numInputs + j] = value;
//				cout << value << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//
//		file >> label;
//		if (label != "stateToAddWeights:")
//		{
//			cout << "Error: Expected stateToAddWeights: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			for (int j = 0; j < numNodes; j++)
//			{
//				file >> value;
//				stateToAddWeights[i * numNodes + j] = value;
//				cout << value << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//
//		file >> label;
//		if (label != "outputWeights:")
//		{
//			cout << "Error: Expected outputWeights: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			for (int j = 0; j < numOutputs; j++)
//			{
//				file >> value;
//				outputWeights[i * numOutputs + j] = value;
//				cout << value << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//
//		file >> label;
//		if (label != "multBiases:")
//		{
//			cout << "Error: Expected multBiases: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			file >> value;
//			multBiases[i] = value;
//			cout << value << " ";
//		}
//		cout << "\n\n";
//
//		file >> label;
//		if (label != "addBiases:")
//		{
//			cout << "Error: Expected addBiases: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numNodes; i++)
//		{
//			file >> value;
//			addBiases[i] = value;
//			cout << value << " ";
//		}
//		cout << "\n\n";
//
//		file >> label;
//		if (label != "outputBiases:")
//		{
//			cout << "Error: Expected outputBiases: but found " << label << endl;
//			assert(false);
//		}
//		cout << label << endl;
//		for (int i = 0; i < numOutputs; i++)
//		{
//			file >> value;
//			outputBiases[i] = value;
//			cout << value << " ";
//		}
//		cout << "\n\n";
//
//		file.close();
//	}
//}
//
//void NetworkParameters::Export()
//{
//	ofstream file;
//	struct tm newtime;
//	time_t now = time(0);
//	localtime_s(&newtime, &now);
//	char buffer[80];
//	strftime(buffer, 80, "%m-%d-%Y %H-%M-%S", &newtime);
//	string path = ".\\Program Logs\\" + string(buffer) + ".txt";
//	file.open(path);
//
//	file << "numNodes: " << numNodes << endl;
//	file << "numInputs: " << numInputs << endl;
//	file << "numOutputs: " << numOutputs << endl;
//
//	file << "initialState: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		file << initialState[i] << " ";
//	}
//	file << "\n\n";
//
//	file << "inputToMultWeights: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		for (int j = 0; j < numInputs; j++)
//		{
//			file << inputToMultWeights[i * numInputs + j] << " ";
//		}
//		file << endl;
//	}
//	file << endl;
//
//	file << "stateToMultWeights: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		for (int j = 0; j < numNodes; j++)
//		{
//			file << stateToMultWeights[i * numNodes + j] << " ";
//		}
//		file << endl;
//	}
//	file << endl;
//
//	file << "inputToAddWeights: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		for (int j = 0; j < numInputs; j++)
//		{
//			file << inputToAddWeights[i * numInputs + j] << " ";
//		}
//		file << endl;
//	}
//	file << endl;
//
//	file << "stateToAddWeights: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		for (int j = 0; j < numNodes; j++)
//		{
//			file << stateToAddWeights[i * numNodes + j] << " ";
//		}
//		file << endl;
//	}
//	file << endl;
//
//	file << "outputWeights: " << endl;
//	for (int i = 0; i < numOutputs; i++)
//	{
//		for (int j = 0; j < numNodes; j++)
//		{
//			file << outputWeights[i * numNodes + j] << " ";
//		}
//		file << endl;
//	}
//	file << endl;
//
//	file << "multBiases: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		file << multBiases[i] << " ";
//	}
//	file << "\n\n";
//
//	file << "addBiases: " << endl;
//	for (int i = 0; i < numNodes; i++)
//	{
//		file << addBiases[i] << " ";
//	}
//	file << "\n\n";
//
//	file << "outputBiases: " << endl;
//	for (int i = 0; i < numOutputs; i++)
//	{
//		file << outputBiases[i] << " ";
//	}
//	file << "\n\n";
//
//	file.close();
//}

//const uint64_t TOTAL_NODES_1D = 3;
//const uint64_t CONV_RADIUS = 1;
//const uint64_t TOTAL_WEIGHTS_1D = 2 * CONV_RADIUS + 1;
//assert(TOTAL_NODES_1D >= TOTAL_WEIGHTS_1D);
///*having TOTAL_WEIGHTS_1D > TOTAL_NODES_1D will result in
//convolution to overlap resulting in redundant computation.
//However, not checking for this may result in different
//good and bad "features"*/
//
//const uint64_t TOTAL_NODES_2D = TOTAL_NODES_1D * TOTAL_NODES_1D;
//const uint64_t TOTAL_NODES_3D = TOTAL_NODES_2D * TOTAL_NODES_1D;
//const uint64_t TOTAL_NODES_4D = TOTAL_NODES_3D * TOTAL_NODES_1D;
//const uint64_t TOTAL_NODES_5D = TOTAL_NODES_4D * TOTAL_WEIGHTS_1D;
//const uint64_t TOTAL_NODES_6D = TOTAL_NODES_5D * TOTAL_WEIGHTS_1D;
//const uint64_t TOTAL_NODES_7D = TOTAL_NODES_6D * TOTAL_WEIGHTS_1D;
//const uint64_t TOTAL_NODES_8D = TOTAL_NODES_7D * TOTAL_WEIGHTS_1D;
//assert(TOTAL_NODES_8D <= UINT32_MAX);
///*don't want to overflow the uint32_t index cuz it will cause
//weird bugs when computing the future state*/
//
//float* state = nullptr;
//float* futureState = nullptr;
//float* bias = nullptr;
//float* weights = nullptr;
//
//uint64_t i, j, k, l, ci, cj, ck, cl;
//int64_t y, z, w, wx, wy, wz, cx, cy, cz, cw;
//Random random;
//
//state = new float[TOTAL_NODES_4D];
//futureState = new float[TOTAL_NODES_4D];
//bias = new float[TOTAL_NODES_4D];
//weights = new float[TOTAL_NODES_8D];
//assert(state != nullptr);
//assert(futureState != nullptr);
//assert(bias != nullptr);
//assert(weights != nullptr);
///*allocate memory for the state, future state, bias, and weights*/
//
//for (i = 0; i < TOTAL_NODES_1D; i++)
//{
//	for (j = 0; j < TOTAL_NODES_1D; j++)
//	{
//		y = i + j * TOTAL_NODES_1D;
//		for (k = 0; k < TOTAL_NODES_1D; k++)
//		{
//			z = y + k * TOTAL_NODES_2D;
//			for (l = 0; l < TOTAL_NODES_1D; l++)
//			{
//				w = z + l * TOTAL_NODES_3D;
//				state[w] = random.NormalRandom(0, 0.5);
//				bias[w] = random.NormalRandom(0, 0.01);
//				for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
//				{
//					wx = w + ci * TOTAL_NODES_4D;
//					for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
//					{
//						wy = wx + cj * TOTAL_NODES_5D;
//						for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
//						{
//							wz = wy + ck * TOTAL_NODES_6D;
//							for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
//							{
//								weights[wz + cl * TOTAL_NODES_7D] =
//									float(
//										ci == CONV_RADIUS &&
//										cj == CONV_RADIUS &&
//										ck == CONV_RADIUS &&
//										cl == CONV_RADIUS
//										)
//									+ random.NormalRandom(0, 0.01);
//								/*identity matrix with a small amount of noise*/
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//for (i = 0; i < TOTAL_NODES_1D; i++)
//{
//	for (j = 0; j < TOTAL_NODES_1D; j++)
//	{
//		y = i + j * TOTAL_NODES_1D;
//		for (k = 0; k < TOTAL_NODES_1D; k++)
//		{
//			z = y + k * TOTAL_NODES_2D;
//			for (l = 0; l < TOTAL_NODES_1D; l++)
//			{
//				w = z + l * TOTAL_NODES_3D;
//				futureState[w] = bias[w];
//				for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
//				{
//					wx = w + ci * TOTAL_NODES_4D;
//					cx = i + ci - CONV_RADIUS;
//					cx = cx < 0 ? cx + TOTAL_NODES_1D :
//						cx >= TOTAL_NODES_1D ? cx - TOTAL_NODES_1D : cx;
//					/*wrap around the edges of that dimention if at edge*/
//					for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
//					{
//						wy = wx + cj * TOTAL_NODES_5D;
//						cy = cx + (j + cj - CONV_RADIUS) * TOTAL_NODES_1D;
//						cy = cy < 0 ? cy + TOTAL_NODES_2D :
//							cy >= TOTAL_NODES_2D ? cy - TOTAL_NODES_2D : cy;
//						for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
//						{
//							wz = wy + ck * TOTAL_NODES_6D;
//							cz = cy + (k + ck - CONV_RADIUS) * TOTAL_NODES_2D;
//							cz = cz < 0 ? cz + TOTAL_NODES_3D :
//								cz >= TOTAL_NODES_3D ? cz - TOTAL_NODES_3D : cz;
//							for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
//							{
//								cw = cz + (l + cl - CONV_RADIUS) * TOTAL_NODES_3D;
//								cw = cw < 0 ? cw + TOTAL_NODES_4D :
//									cw >= TOTAL_NODES_4D ? cw - TOTAL_NODES_4D : cw;
//								futureState[w] += state[cw] * weights[wz + cl * TOTAL_NODES_7D];
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}
//
//cout << "state matrix" << endl;
//for (i = 0; i < TOTAL_NODES_1D; i++)
//{
//	for (j = 0; j < TOTAL_NODES_1D; j++)
//	{
//		y = i + j * TOTAL_NODES_1D;
//		for (k = 0; k < TOTAL_NODES_1D; k++)
//		{
//			z = y + k * TOTAL_NODES_2D;
//			for (l = 0; l < TOTAL_NODES_1D; l++)
//			{
//				cout << state[z + l * TOTAL_NODES_3D] << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//cout << endl;
//
//cout << "future state matrix" << endl;
//for (i = 0; i < TOTAL_NODES_1D; i++)
//{
//	for (j = 0; j < TOTAL_NODES_1D; j++)
//	{
//		y = i + j * TOTAL_NODES_1D;
//		for (k = 0; k < TOTAL_NODES_1D; k++)
//		{
//			z = y + k * TOTAL_NODES_2D;
//			for (l = 0; l < TOTAL_NODES_1D; l++)
//			{
//				cout << futureState[z + l * TOTAL_NODES_3D] << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//cout << endl;
//
//cout << "bias matrix" << endl;
//for (i = 0; i < TOTAL_NODES_1D; i++)
//{
//	for (j = 0; j < TOTAL_NODES_1D; j++)
//	{
//		y = i + j * TOTAL_NODES_1D;
//		for (k = 0; k < TOTAL_NODES_1D; k++)
//		{
//			z = y + k * TOTAL_NODES_2D;
//			for (l = 0; l < TOTAL_NODES_1D; l++)
//			{
//				cout << bias[z + l * TOTAL_NODES_3D] << " ";
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//cout << endl;
//
//cout << "weights matrix" << endl;
//for (i = 0; i < TOTAL_NODES_1D; i++)
//{
//	for (j = 0; j < TOTAL_NODES_1D; j++)
//	{
//		y = i + j * TOTAL_NODES_1D;
//		for (k = 0; k < TOTAL_NODES_1D; k++)
//		{
//			z = y + k * TOTAL_NODES_2D;
//			for (l = 0; l < TOTAL_NODES_1D; l++)
//			{
//				w = z + l * TOTAL_NODES_3D;
//				for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
//				{
//					wx = w + ci * TOTAL_NODES_4D;
//					for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
//					{
//						wy = wx + cj * TOTAL_NODES_5D;
//						for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
//						{
//							wz = wy + ck * TOTAL_NODES_6D;
//							for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
//							{
//								cout << weights[wz + cl * TOTAL_NODES_7D] << " ";
//							}
//							cout << endl;
//						}
//						cout << endl;
//					}
//					cout << endl;
//				}
//				cout << endl;
//			}
//			cout << endl;
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//cout << endl;
//
//delete[] state;
//delete[] futureState;
//delete[] bias;
//delete[] weights;
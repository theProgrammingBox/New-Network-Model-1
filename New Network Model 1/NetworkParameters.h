#pragma once
#include "Header.h"

class NetworkParameters
{
public:
	uint64_t TOTAL_NODES_1D;
	uint64_t CONV_RADIUS;
	uint64_t TOTAL_INPUTS;
	uint64_t TOTAL_OUTPUTS;

	uint64_t TOTAL_WEIGHTS_1D;
	uint64_t TOTAL_NODES_2D;
	uint64_t TOTAL_NODES_3D;
	uint64_t TOTAL_NODES_4D;
	uint64_t TOTAL_NODES_5D;
	uint64_t TOTAL_NODES_6D;
	uint64_t TOTAL_NODES_7D;
	uint64_t TOTAL_NODES_8D;

	float* initalState = nullptr;
	float* stateBias1 = nullptr;
	float* inputWeights1 = nullptr;
	float* stateWeights1 = nullptr;
	float* stateBias2 = nullptr;
	float* inputWeights2 = nullptr;
	float* stateWeights2 = nullptr;
	float* outputWeights = nullptr;
	float* outputBias = nullptr;

	NetworkParameters(uint64_t totalNodes1D, uint64_t convRadius, unsigned int numInputs, unsigned int numOutputs);
	~NetworkParameters();

	void Initialize();
	void Import();

	void Export();
};

NetworkParameters::NetworkParameters(uint64_t totalNodes1D, uint64_t convRadius, unsigned int numInputs, unsigned int numOutputs)
{
	TOTAL_NODES_1D = totalNodes1D;
	CONV_RADIUS = convRadius;
	TOTAL_INPUTS = numInputs;
	TOTAL_OUTPUTS = numOutputs;
	TOTAL_WEIGHTS_1D = 2 * CONV_RADIUS + 1;
	assert(TOTAL_NODES_1D >= TOTAL_WEIGHTS_1D);

	TOTAL_NODES_2D = TOTAL_NODES_1D * TOTAL_NODES_1D;
	TOTAL_NODES_3D = TOTAL_NODES_2D * TOTAL_NODES_1D;
	TOTAL_NODES_4D = TOTAL_NODES_3D * TOTAL_NODES_1D;
	TOTAL_NODES_5D = TOTAL_NODES_4D * TOTAL_WEIGHTS_1D;
	TOTAL_NODES_6D = TOTAL_NODES_5D * TOTAL_WEIGHTS_1D;
	TOTAL_NODES_7D = TOTAL_NODES_6D * TOTAL_WEIGHTS_1D;
	TOTAL_NODES_8D = TOTAL_NODES_7D * TOTAL_WEIGHTS_1D;
	assert(TOTAL_NODES_8D <= UINT32_MAX);

	initalState = new float[TOTAL_NODES_4D];
	stateBias1 = new float[TOTAL_NODES_4D];
	inputWeights1 = new float[TOTAL_INPUTS * TOTAL_NODES_4D];
	stateWeights1 = new float[TOTAL_NODES_8D];
	stateBias2 = new float[TOTAL_NODES_4D];
	inputWeights2 = new float[TOTAL_INPUTS * TOTAL_NODES_4D];
	stateWeights2 = new float[TOTAL_NODES_8D];
	outputWeights = new float[TOTAL_NODES_4D * TOTAL_OUTPUTS];
	outputBias = new float[TOTAL_OUTPUTS];

	assert(initalState != nullptr);
	assert(stateBias1 != nullptr);
	assert(inputWeights1 != nullptr);
	assert(stateWeights1 != nullptr);
	assert(stateBias2 != nullptr);
	assert(inputWeights2 != nullptr);
	assert(stateWeights2 != nullptr);
	assert(outputWeights != nullptr);
	assert(outputBias != nullptr);
}

NetworkParameters::~NetworkParameters()
{
	if (initalState != nullptr)
		delete[] initalState;
	if (stateBias1 != nullptr)
		delete[] stateBias1;
	if (inputWeights1 != nullptr)
		delete[] inputWeights1;
	if (stateWeights1 != nullptr)
		delete[] stateWeights1;
	if (stateBias2 != nullptr)
		delete[] stateBias2;
	if (inputWeights2 != nullptr)
		delete[] inputWeights2;
	if (stateWeights2 != nullptr)
		delete[] stateWeights2;
	if (outputWeights != nullptr)
		delete[] outputWeights;
	if (outputBias != nullptr)
		delete[] outputBias;
}

void NetworkParameters::Initialize()
{
	uint64_t i, j, k, l, ci, cj, ck, cl;
	int64_t y, z, w, wx, wy, wz;
	Random random;

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					initalState[w] = random.NormalRandom(0, 0.5);
					stateBias1[w] = random.NormalRandom(0, 0.001);
					stateBias2[w] = random.NormalRandom(0, 0.001);

					for (ci = 0; ci < TOTAL_INPUTS; ci++)
					{
						inputWeights1[w + ci * TOTAL_NODES_4D] = random.NormalRandom(0, 0.001);
						inputWeights2[w + ci * TOTAL_NODES_4D] = random.NormalRandom(0, 0.001);
					}

					for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
					{
						wx = w + ci * TOTAL_NODES_4D;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							wy = wx + cj * TOTAL_NODES_5D;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								wz = wy + ck * TOTAL_NODES_6D;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									stateWeights1[wz + cl * TOTAL_NODES_7D] =
										float(
											ci == CONV_RADIUS &&
											cj == CONV_RADIUS &&
											ck == CONV_RADIUS &&
											cl == CONV_RADIUS
											)
										+ random.NormalRandom(0, 0.001);
									stateWeights2[wz + cl * TOTAL_NODES_7D] =
										float(
											ci == CONV_RADIUS &&
											cj == CONV_RADIUS &&
											ck == CONV_RADIUS &&
											cl == CONV_RADIUS
											)
										+ random.NormalRandom(0, 0.001);
								}
							}
						}
					}

					for (ci = 0; ci < TOTAL_OUTPUTS; ci++)
					{
						outputWeights[w + ci * TOTAL_NODES_4D] = random.NormalRandom(0, 0.001);
					}
				}
			}
		}
	}

	for (i = 0; i < TOTAL_OUTPUTS; i++)
	{
		outputBias[i] = random.NormalRandom(0, 0.001);
	}
}

void NetworkParameters::Export()
{
	uint64_t i, j, k, l, ci, cj, ck, cl;
	int64_t y, z, w, wx, wy, wz;

	ofstream file;
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	char buffer[80];
	strftime(buffer, 80, "%m-%d-%Y %H-%M-%S", &newtime);
	string path = ".\\Program Logs\\" + string(buffer) + ".txt";
	file.open(path);

	file << "TOTAL_NODES_1D: " << TOTAL_NODES_1D << "\n\n";
	file << "CONV_RADIUS: " << CONV_RADIUS << "\n\n";
	file << "TOTAL_INPUTS: " << TOTAL_INPUTS << "\n\n";
	file << "TOTAL_OUTPUTS: " << TOTAL_OUTPUTS << "\n\n";

	file << "initalState:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					file << initalState[z + l * TOTAL_NODES_3D] << " ";
				}
				file << std::endl;
			}
			file << std::endl;
		}
		file << std::endl;
	}

	file << "stateBias1:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					file << stateBias1[z + l * TOTAL_NODES_3D] << " ";
				}
				file << std::endl;
			}
			file << std::endl;
		}
		file << std::endl;
	}

	file << "stateBias2:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					file << stateBias2[z + l * TOTAL_NODES_3D] << " ";
				}
				file << std::endl;
			}
			file << std::endl;
		}
		file << std::endl;
	}

	file << "inputWeights1:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					for (ci = 0; ci < TOTAL_INPUTS; ci++)
					{
						file << inputWeights1[w + ci * TOTAL_NODES_4D] << " ";
					}
					file << std::endl;
				}
				file << std::endl;
			}
			file << std::endl;
		}
		file << std::endl;
	}

	file << "inputWeights2:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					for (ci = 0; ci < TOTAL_INPUTS; ci++)
					{
						file << inputWeights2[w + ci * TOTAL_NODES_4D] << " ";
					}
					file << std::endl;
				}
				file << std::endl;
			}
			file << std::endl;
		}
		file << std::endl;
	}

	file << "stateWeights1:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
					{
						wx = w + ci * TOTAL_NODES_4D;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							wy = wx + cj * TOTAL_NODES_5D;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								wz = wy + ck * TOTAL_NODES_6D;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									file << stateWeights1[wz + cl * TOTAL_NODES_7D] << " ";
								}
								file << endl;
							}
							file << endl;
						}
						file << endl;
					}
					file << endl;
				}
				file << endl;
			}
			file << endl;
		}
		file << endl;
	}

	file << "stateWeights2:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
					{
						wx = w + ci * TOTAL_NODES_4D;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							wy = wx + cj * TOTAL_NODES_5D;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								wz = wy + ck * TOTAL_NODES_6D;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									file << stateWeights2[wz + cl * TOTAL_NODES_7D] << " ";
								}
								file << endl;
							}
							file << endl;
						}
						file << endl;
					}
					file << endl;
				}
				file << endl;
			}
			file << endl;
		}
		file << endl;
	}

	file << "outputWeights:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					for (ci = 0; ci < TOTAL_OUTPUTS; ci++)
					{
						file << outputWeights[w + ci * TOTAL_NODES_4D] << " ";
					}
					file << endl;
				}
				file << std::endl;
			}
			file << std::endl;
		}
		file << std::endl;
	}

	file << "outputBias:" << endl;
	for (i = 0; i < TOTAL_OUTPUTS; i++)
	{
		file << outputBias[i] << " ";
	}

	file.close();
}

bool comparitor(string a, string b)
{
	uint64_t aTime, bTime;

	aTime = stoi(
		a.substr(6, 4) +
		a.substr(0, 2) +
		a.substr(3, 2) +
		a.substr(11, 2) +
		a.substr(14, 2) +
		a.substr(17, 2)
	);

	bTime = stoi(
		b.substr(6, 4) +
		b.substr(0, 2) +
		b.substr(3, 2) +
		b.substr(11, 2) +
		b.substr(14, 2) +
		b.substr(17, 2)
	);

	return aTime > bTime;
}

void NetworkParameters::Import()
{
	cout << "IMPORT OPTIONS" << endl;
	cout << "Option" << setw(6) << 0 << ": Initialize New Network\n";
	vector<string> files;
	if (auto dir = opendir("./Program Logs/"))
	{
		while (auto f = readdir(dir)) {
			if (f->d_name && f->d_name[0] != '.')
			{
				files.push_back(f->d_name);
			}
		}
		closedir(dir);

		sort(files.begin(), files.end(), comparitor);

		for (int i = 0; i < files.size(); i++)
		{
			cout << "Option" << setw(6) << i + 1 << ": " << files[i] << endl;
		}
	}

	int choice;
	do
	{
		cout << "Select an option (Enter 0 for default): ";
	} while (ErrorCheckIntInput(choice, 0, files.size()));

	if (choice == 0)
	{
		cout << "Initializing New Network" << endl;
		Initialize();
	}
	else
	{
		uint64_t i, j, k, l, ci, cj, ck, cl;
		int64_t y, z, w, wx, wy, wz;

		cout << "Importing Network from file: " << files[choice - 1] << endl;
		string path = "./Program Logs/" + files[choice - 1];
		ifstream file;
		file.open(path);
		string label;
		unsigned int value;

		file >> label >> value;
		assert(label == "TOTAL_NODES_1D:");
		assert(value == TOTAL_NODES_1D);

		file >> label >> value;
		assert(label == "CONV_RADIUS:");
		assert(value == CONV_RADIUS);

		file >> label >> value;
		assert(label == "TOTAL_INPUTS:");
		assert(value == TOTAL_INPUTS);

		file >> label >> value;
		assert(label == "TOTAL_OUTPUTS:");
		assert(value == TOTAL_OUTPUTS);

		file >> label;
		assert(label == "initalState:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						file >> initalState[z + l * TOTAL_NODES_3D];
					}
				}
			}
		}

		file >> label;
		assert(label == "stateBias1:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						file >> stateBias1[z + l * TOTAL_NODES_3D];
					}
				}
			}
		}

		file >> label;
		assert(label == "stateBias2:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						file >> stateBias2[z + l * TOTAL_NODES_3D];
					}
				}
			}
		}

		file >> label;
		assert(label == "inputWeights1:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						w = z + l * TOTAL_NODES_3D;
						for (ci = 0; ci < TOTAL_INPUTS; ci++)
						{
							file >> inputWeights1[w + ci * TOTAL_NODES_4D];
						}
					}
				}
			}
		}

		file >> label;
		assert(label == "inputWeights2:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						w = z + l * TOTAL_NODES_3D;
						for (ci = 0; ci < TOTAL_INPUTS; ci++)
						{
							file >> inputWeights2[w + ci * TOTAL_NODES_4D];
						}
					}
				}
			}
		}

		file >> label;
		assert(label == "stateWeights1:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						w = z + l * TOTAL_NODES_3D;
						for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
						{
							wx = w + ci * TOTAL_NODES_4D;
							for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
							{
								wy = wx + cj * TOTAL_NODES_5D;
								for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
								{
									wz = wy + ck * TOTAL_NODES_6D;
									for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
									{
										file >> stateWeights1[wz + cl * TOTAL_NODES_7D];
									}
								}
							}
						}
					}
				}
			}
		}

		file >> label;
		assert(label == "stateWeights2:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						w = z + l * TOTAL_NODES_3D;
						for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
						{
							wx = w + ci * TOTAL_NODES_4D;
							for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
							{
								wy = wx + cj * TOTAL_NODES_5D;
								for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
								{
									wz = wy + ck * TOTAL_NODES_6D;
									for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
									{
										file >> stateWeights2[wz + cl * TOTAL_NODES_7D];
									}
								}
							}
						}
					}
				}
			}
		}

		file >> label;
		assert(label == "outputWeights:");
		for (i = 0; i < TOTAL_NODES_1D; i++)
		{
			for (j = 0; j < TOTAL_NODES_1D; j++)
			{
				y = i + j * TOTAL_NODES_1D;
				for (k = 0; k < TOTAL_NODES_1D; k++)
				{
					z = y + k * TOTAL_NODES_2D;
					for (l = 0; l < TOTAL_NODES_1D; l++)
					{
						w = z + l * TOTAL_NODES_3D;
						for (ci = 0; ci < TOTAL_OUTPUTS; ci++)
						{
							file >> outputWeights[w + ci * TOTAL_NODES_4D];
						}
					}
				}
			}
		}

		file >> label;
		assert(label == "outputBias:");
		for (i = 0; i < TOTAL_OUTPUTS; i++)
		{
			file >> outputBias[i];
		}
	}
}
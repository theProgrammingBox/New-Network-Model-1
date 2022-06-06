#include "Header.h"

int main()
{
	const int64_t TOTAL_NODES_1D = 3;
	const int64_t CONV_RADIUS = 1;
	const int64_t TOTAL_NODES_2D = TOTAL_NODES_1D * TOTAL_NODES_1D;
	const int64_t TOTAL_NODES_3D = TOTAL_NODES_2D * TOTAL_NODES_1D;
	const int64_t TOTAL_NODES_4D = TOTAL_NODES_3D * TOTAL_NODES_1D;
	const int64_t TOTAL_WEIGHTS_1D = 2 * CONV_RADIUS + 1;
	const int64_t TOTAL_WEIGHTS_2D = TOTAL_WEIGHTS_1D * TOTAL_WEIGHTS_1D;
	const int64_t TOTAL_WEIGHTS_3D = TOTAL_WEIGHTS_2D * TOTAL_WEIGHTS_1D;
	const int64_t TOTAL_WEIGHTS_4D = TOTAL_WEIGHTS_3D * TOTAL_WEIGHTS_1D;

	/*double**** state = nullptr;
	double**** bias = nullptr;
	double******** weights = nullptr;
	double**** futureState = nullptr;

	int64_t i, j, k, l;
	int64_t wi, wj, wk, wl;
	Random random;

	state = new double*** [TOTAL_NODES_1D];
	bias = new double*** [TOTAL_NODES_1D];
	futureState = new double*** [TOTAL_NODES_1D];
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		state[i] = new double** [TOTAL_NODES_1D];
		bias[i] = new double** [TOTAL_NODES_1D];
		futureState[i] = new double** [TOTAL_NODES_1D];
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			state[i][j] = new double* [TOTAL_NODES_1D];
			bias[i][j] = new double* [TOTAL_NODES_1D];
			futureState[i][j] = new double* [TOTAL_NODES_1D];
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				state[i][j][k] = new double[TOTAL_NODES_1D];
				bias[i][j][k] = new double[TOTAL_NODES_1D];
				futureState[i][j][k] = new double[TOTAL_NODES_1D];
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					state[i][j][k][l] = random.DoubleRandom();
					bias[i][j][k][l] = 0;
				}
			}
		}
	}

	weights = new double******* [TOTAL_NODES_1D];
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		weights[i] = new double****** [TOTAL_NODES_1D];
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			weights[i][j] = new double***** [TOTAL_NODES_1D];
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				weights[i][j][k] = new double**** [TOTAL_NODES_1D];
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					weights[i][j][k][l] = new double*** [TOTAL_WEIGHTS_1D];
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						weights[i][j][k][l][wi] = new double** [TOTAL_WEIGHTS_1D];
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							weights[i][j][k][l][wi][wj] = new double* [TOTAL_WEIGHTS_1D];
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								weights[i][j][k][l][wi][wj][wk] = new double[TOTAL_WEIGHTS_1D];
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									weights[i][j][k][l][wi][wj][wk][wl] = wi == CONV_RADIUS && wj == CONV_RADIUS && wk == CONV_RADIUS && wl == CONV_RADIUS;
								}
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					futureState[i][j][k][l] = bias[i][j][k][l];
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									int64_t indexi = i + (wi - CONV_RADIUS);
									indexi = indexi < 0 ? indexi + TOTAL_NODES_1D : indexi >= TOTAL_NODES_1D ? indexi - TOTAL_NODES_1D : indexi;
									int64_t indexj = j + (wj - CONV_RADIUS);
									indexj = indexj < 0 ? indexj + TOTAL_NODES_1D : indexj >= TOTAL_NODES_1D ? indexj - TOTAL_NODES_1D : indexj;
									int64_t indexk = k + (wk - CONV_RADIUS);
									indexk = indexk < 0 ? indexk + TOTAL_NODES_1D : indexk >= TOTAL_NODES_1D ? indexk - TOTAL_NODES_1D : indexk;
									int64_t indexl = l + (wl - CONV_RADIUS);
									indexl = indexl < 0 ? indexl + TOTAL_NODES_1D : indexl >= TOTAL_NODES_1D ? indexl - TOTAL_NODES_1D : indexl;
									futureState[i][j][k][l] += state[indexi][indexj][indexk][indexl] * weights[i][j][k][l][wi][wj][wk][wl];
									if (i == 0 && j == 0 && k == 0 && l == 0)
									{
										cout << "state[" << indexi << "][" << indexj << "][" << indexk << "][" << indexl << "] = " << state[indexi][indexj][indexk][indexl] << endl;
										cout << "weights[" << i << "][" << j << "][" << k << "][" << l << "][" << wi << "][" << wj << "][" << wk << "][" << wl << "] = " << weights[i][j][k][l][wi][wj][wk][wl] << endl;
									}
								}
							}
						}
					}
					if (i == 0 && j == 0 && k == 0 && l == 0)
					{
						cout << "futureState[" << i << "][" << j << "][" << k << "][" << l << "] = " << futureState[i][j][k][l] << endl;
					}
				}
			}
		}
	}

	cout << "state matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << state[i][j][k][l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "future state matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << futureState[i][j][k][l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "bias matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << bias[i][j][k][l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "weights matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									cout << weights[i][j][k][l][wi][wj][wk][wl] << " ";
								}
								cout << endl;
							}
							cout << endl;
						}
						cout << endl;
					}
					cout << endl;
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				delete[] state[i][j][k];
				delete[] bias[i][j][k];
			}
			delete[] state[i][j];
			delete[] bias[i][j];
		}
		delete[] state[i];
		delete[] bias[i];
	}
	delete[] state;
	delete[] bias;

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								delete[] weights[i][j][k][l][wi][wj][wk];
							}
							delete[] weights[i][j][k][l][wi][wj];
						}
						delete[] weights[i][j][k][l][wi];
					}
					delete[] weights[i][j][k][l];
				}
				delete[] weights[i][j][k];
			}
			delete[] weights[i][j];
		}
		delete[] weights[i];
	}
	delete[] weights;*/

	/*float* state = nullptr;
	float* futureState = nullptr;
	float* bias = nullptr;
	float* weights = nullptr;

	uint32_t i, j, k, l, wi, wj, wk, wl;
	Random random;

	state = new float[TOTAL_NODES_4D];
	futureState = new float[TOTAL_NODES_4D];
	bias = new float[TOTAL_NODES_4D];
	weights = new float[TOTAL_NODES_4D * TOTAL_WEIGHTS_4D];

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					state[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] = random.DoubleRandom();
					futureState[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] = 0;
					bias[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] = 0;
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									weights[(i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l) * TOTAL_WEIGHTS_4D + wi * TOTAL_WEIGHTS_3D + wj * TOTAL_WEIGHTS_2D + wk * TOTAL_WEIGHTS_1D + wl] = wi == CONV_RADIUS && wj == CONV_RADIUS && wk == CONV_RADIUS && wl == CONV_RADIUS;
								}
							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					futureState[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] = bias[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l];
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									int64_t indexi = i + (wi - CONV_RADIUS);
									indexi = indexi < 0 ? indexi + TOTAL_NODES_1D : indexi >= TOTAL_NODES_1D ? indexi - TOTAL_NODES_1D : indexi;
									int64_t indexj = j + (wj - CONV_RADIUS);
									indexj = indexj < 0 ? indexj + TOTAL_NODES_1D : indexj >= TOTAL_NODES_1D ? indexj - TOTAL_NODES_1D : indexj;
									int64_t indexk = k + (wk - CONV_RADIUS);
									indexk = indexk < 0 ? indexk + TOTAL_NODES_1D : indexk >= TOTAL_NODES_1D ? indexk - TOTAL_NODES_1D : indexk;
									int64_t indexl = l + (wl - CONV_RADIUS);
									indexl = indexl < 0 ? indexl + TOTAL_NODES_1D : indexl >= TOTAL_NODES_1D ? indexl - TOTAL_NODES_1D : indexl;
									futureState[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] += state[indexi * TOTAL_NODES_3D + indexj * TOTAL_NODES_2D + indexk * TOTAL_NODES_1D + indexl] * weights[(i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l) * TOTAL_WEIGHTS_4D + wi * TOTAL_WEIGHTS_3D + wj * TOTAL_WEIGHTS_2D + wk * TOTAL_WEIGHTS_1D + wl];
									if (i == 0 && j == 0 && k == 0 && l == 0)
									{
										cout << "state[" << indexi << "][" << indexj << "][" << indexk << "][" << indexl << "] = " << state[indexi * TOTAL_NODES_3D + indexj * TOTAL_NODES_2D + indexk * TOTAL_NODES_1D + indexl] << endl;
										cout << "weights[" << i << "][" << j << "][" << k << "][" << l << "][" << wi << "][" << wj << "][" << wk << "][" << wl << "] = " << weights[(i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l) * TOTAL_WEIGHTS_4D + wi * TOTAL_WEIGHTS_3D + wj * TOTAL_WEIGHTS_2D + wk * TOTAL_WEIGHTS_1D + wl] << endl;
									}
								}
							}
						}
					}
					if (i == 0 && j == 0 && k == 0 && l == 0)
					{
						cout << "futureState[" << i << "][" << j << "][" << k << "][" << l << "] = " << futureState[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] << endl;
					}
				}
			}
		}
	}

	cout << "state matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << state[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "future state matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << futureState[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "bias matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << bias[i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "weights matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									cout << weights[(i * TOTAL_NODES_3D + j * TOTAL_NODES_2D + k * TOTAL_NODES_1D + l) * TOTAL_WEIGHTS_4D + wi * TOTAL_WEIGHTS_3D + wj * TOTAL_WEIGHTS_2D + wk * TOTAL_WEIGHTS_1D + wl] << " ";
								}
								cout << endl;
							}
							cout << endl;
						}
						cout << endl;
					}
					cout << endl;
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;*/

	return 0;
}
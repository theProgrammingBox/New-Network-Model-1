#include "Header.h"

int main()
{
	const int32_t TOTAL_NODES_1D = 4;
	const int32_t CONV_RADIUS = 1;

	const int32_t TOTAL_NODES_2D = TOTAL_NODES_1D * TOTAL_NODES_1D;
	const int32_t TOTAL_NODES_3D = TOTAL_NODES_2D * TOTAL_NODES_1D;
	const int32_t TOTAL_NODES_4D = TOTAL_NODES_2D * TOTAL_NODES_2D;
	const int32_t TOTAL_WEIGHTS_1D = CONV_RADIUS * 2 + 1;
	const int32_t TOTAL_WEIGHTS_2D = TOTAL_WEIGHTS_1D * TOTAL_WEIGHTS_1D;
	const int32_t TOTAL_WEIGHTS_3D = TOTAL_WEIGHTS_2D * TOTAL_WEIGHTS_1D;
	const int32_t TOTAL_WEIGHTS_4D = TOTAL_WEIGHTS_2D * TOTAL_WEIGHTS_2D;
	Random random;

	int32_t i, j, k, l;
	int32_t wi, wj, wk, wl;
	int32_t indexI, indexJ, indexK, indexL;
	int32_t wIndexI, wIndexJ, wIndexK, wIndexL;
	int32_t cIndexI, cIndexJ, cIndexK, cIndexL;

	float* matrix = nullptr;
	float* bias = nullptr;
	float* weights = nullptr;
	float* matrix2 = nullptr;

	matrix = new float[TOTAL_NODES_4D];
	bias = new float[TOTAL_NODES_4D];
	weights = new float[TOTAL_NODES_4D * TOTAL_WEIGHTS_4D];
	matrix2 = new float[TOTAL_NODES_4D];

	for (i = 0; i < TOTAL_NODES_4D; i++)
	{
		matrix[i] = random.DoubleRandom();
		bias[i] = 0;
		uint32_t counter = 0;
		for (j = 0; j < TOTAL_WEIGHTS_4D; j++)
		{
			weights[i * TOTAL_WEIGHTS_4D + j] = counter++ == TOTAL_WEIGHTS_4D / 2;
		}
	}

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		indexI = i * TOTAL_NODES_3D;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			indexJ = indexI + j * TOTAL_NODES_2D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				indexK = indexJ + k * TOTAL_NODES_1D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					indexL = indexK + l;
					matrix2[indexL] = bias[indexL];
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						wIndexI = indexL * TOTAL_WEIGHTS_4D + wi * TOTAL_WEIGHTS_3D;
						cIndexI = indexL + (wi - CONV_RADIUS) * TOTAL_NODES_3D;
						cIndexI = cIndexI < 0 ? cIndexI + TOTAL_NODES_4D : cIndexI >= TOTAL_NODES_4D ? cIndexI - TOTAL_NODES_4D : cIndexI;
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							wIndexJ = wIndexI + wj * TOTAL_WEIGHTS_2D;
							cIndexJ = cIndexI + (wj - CONV_RADIUS) * TOTAL_NODES_2D;
							cIndexJ = cIndexJ < 0 ? cIndexJ + TOTAL_NODES_4D : cIndexJ >= TOTAL_NODES_4D ? cIndexJ - TOTAL_NODES_4D : cIndexJ;
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								wIndexK = wIndexJ + wk * TOTAL_WEIGHTS_1D;
								cIndexK = cIndexJ + (wk - CONV_RADIUS) * TOTAL_NODES_1D;
								cIndexK = cIndexK < 0 ? cIndexK + TOTAL_NODES_4D : cIndexK >= TOTAL_NODES_4D ? cIndexK - TOTAL_NODES_4D : cIndexK;
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									wIndexL = wIndexK + wl;
									cIndexL = cIndexK + (wl - CONV_RADIUS);
									cIndexL = cIndexL < 0 ? cIndexL + TOTAL_NODES_4D : cIndexL >= TOTAL_NODES_4D ? cIndexL - TOTAL_NODES_4D : cIndexL;
									matrix2[indexL] += matrix[cIndexL] * weights[wIndexL];
									if (i == 0 && j == 1 && k == 0 && l == 1)
									{
										cout << "matrix[" << cIndexL << "] = " << matrix[cIndexL] << " * weights[" << wIndexL << "] = " << weights[wIndexL] << " = " << matrix[cIndexL] * weights[wIndexL] << endl;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << "Matrix:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		indexI = i * TOTAL_NODES_3D;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			indexJ = indexI + j * TOTAL_NODES_2D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				indexK = indexJ + k * TOTAL_NODES_1D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					indexL = indexK + l;
					cout << matrix[indexL] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "Matrix2:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		indexI = i * TOTAL_NODES_3D;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			indexJ = indexI + j * TOTAL_NODES_2D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				indexK = indexJ + k * TOTAL_NODES_1D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					indexL = indexK + l;
					cout << matrix2[indexL] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "Bias:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		indexI = i * TOTAL_NODES_3D;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			indexJ = indexI + j * TOTAL_NODES_2D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				indexK = indexJ + k * TOTAL_NODES_1D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					indexL = indexK + l;
					cout << bias[indexL] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	/*cout << "Weights:" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		indexI = i * TOTAL_NODES_3D;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			indexJ = indexI + j * TOTAL_NODES_2D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				indexK = indexJ + k * TOTAL_NODES_1D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					indexL = indexK + l;
					for (wi = 0; wi < TOTAL_WEIGHTS_1D; wi++)
					{
						wIndexI = indexL * TOTAL_WEIGHTS_4D + wi * TOTAL_WEIGHTS_3D;
						for (wj = 0; wj < TOTAL_WEIGHTS_1D; wj++)
						{
							wIndexJ = wIndexI + wj * TOTAL_WEIGHTS_2D;
							for (wk = 0; wk < TOTAL_WEIGHTS_1D; wk++)
							{
								wIndexK = wIndexJ + wk * TOTAL_WEIGHTS_1D;
								for (wl = 0; wl < TOTAL_WEIGHTS_1D; wl++)
								{
									wIndexL = wIndexK + wl;
									cout << weights[wIndexL] << " ";
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

	delete[] matrix;
	delete[] bias;
	delete[] weights;
	delete[] matrix2;

	return 0;
}
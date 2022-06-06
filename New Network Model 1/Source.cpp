#include "Header.h"

int main()
{
	const int64_t TOTAL_NODES_1D = 3;
	const int64_t CONV_RADIUS = 1;

	const int64_t TOTAL_NODES_2D = TOTAL_NODES_1D * TOTAL_NODES_1D;
	const int64_t TOTAL_NODES_3D = TOTAL_NODES_2D * TOTAL_NODES_1D;
	const int64_t TOTAL_NODES_4D = TOTAL_NODES_3D * TOTAL_NODES_1D;
	const int64_t TOTAL_WEIGHTS_1D = 2 * CONV_RADIUS + 1;
	const int64_t TOTAL_NODES_5D = TOTAL_NODES_4D * TOTAL_WEIGHTS_1D;
	const int64_t TOTAL_NODES_6D = TOTAL_NODES_5D * TOTAL_WEIGHTS_1D;
	const int64_t TOTAL_NODES_7D = TOTAL_NODES_6D * TOTAL_WEIGHTS_1D;
	const int64_t TOTAL_NODES_8D = TOTAL_NODES_7D * TOTAL_WEIGHTS_1D;

	float* state = nullptr;
	float* futureState = nullptr;
	float* bias = nullptr;
	float* weights = nullptr;

	uint32_t i, j, k, l, ci, cj, ck, cl;
	int64_t x, y, z, w, cx, cy, cz, cw;
	int64_t indexi, indexj, indexk, indexl;
	Random random;

	state = new float[TOTAL_NODES_4D];
	futureState = new float[TOTAL_NODES_4D];
	bias = new float[TOTAL_NODES_4D];
	weights = new float[TOTAL_NODES_8D];

	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		x = i;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = x + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;

					state[w] = random.DoubleRandom();
					bias[w] = 0;
					for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
					{
						cx = w + ci * TOTAL_NODES_4D;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							cy = cx + cj * TOTAL_NODES_5D;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								cz = cy + ck * TOTAL_NODES_6D;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									cw = cz + cl * TOTAL_NODES_7D;
									weights[cw] = ci == CONV_RADIUS && cj == CONV_RADIUS && ck == CONV_RADIUS && cl == CONV_RADIUS;
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
		x = i;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = x + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					futureState[w] = bias[w];
					for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
					{
						cx = w + ci * TOTAL_NODES_4D;
						indexi = i + ci - CONV_RADIUS;
						indexi = indecx < 0 ? indecx + TOTAL_NODES_1D : indecx >= TOTAL_NODES_1D ? indecx - TOTAL_NODES_1D : indecx;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							cy = cx + cj * TOTAL_NODES_5D;
							indexj = j + cj - CONV_RADIUS;
							indexj = indexj < 0 ? indexj + TOTAL_NODES_1D : indexj >= TOTAL_NODES_1D ? indexj - TOTAL_NODES_1D : indexj;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								cz = cy + ck * TOTAL_NODES_6D;
								indexk = k + ck - CONV_RADIUS;
								indexk = indexk < 0 ? indexk + TOTAL_NODES_1D : indexk >= TOTAL_NODES_1D ? indexk - TOTAL_NODES_1D : indexk;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									cw = cz + cl * TOTAL_NODES_7D;
									indexl = l + cl - CONV_RADIUS;
									indexl = indexl < 0 ? indexl + TOTAL_NODES_1D : indexl >= TOTAL_NODES_1D ? indexl - TOTAL_NODES_1D : indexl;
									futureState[w] += state[indecx + indexj * TOTAL_NODES_1D + indexk * TOTAL_NODES_2D + indexl * TOTAL_NODES_3D] * weights[cw];
									if (i == 0 && j == 0 && k == 0 && l == 0)
									{
										cout << "state[" << indexi << "][" << indexj << "][" << indexk << "][" << indexl << "] = " << state[indexi + indexj * TOTAL_NODES_1D + indexk * TOTAL_NODES_2D + indexl * TOTAL_NODES_3D] << endl;
										cout << "weights[" << i << "][" << j << "][" << k << "][" << l << "][" << ci << "][" << cj << "][" << ck << "][" << cl << "] = " << weights[cw] << endl;
									}
								}
							}
						}
					}
					if (i == 0 && j == 0 && k == 0 && l == 0)
					{
						cout << "futureState[" << i << "][" << j << "][" << k << "][" << l << "] = " << futureState[w] << endl;
					}
				}
			}
		}
	}

	cout << "state matrix" << endl;
	for (i = 0; i < TOTAL_NODES_1D; i++)
	{
		x = i;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = x + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					cout << state[w] << " ";
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
		x = i;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = x + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					cout << futureState[w] << " ";
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
		x = i;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = x + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					cout << bias[w] << " ";
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
		x = i;
		for (j = 0; j < TOTAL_NODES_1D; j++)
		{
			y = x + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					w = z + l * TOTAL_NODES_3D;
					for (ci = 0; ci < TOTAL_WEIGHTS_1D; ci++)
					{
						cx = w + ci * TOTAL_NODES_4D;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							cy = cx + cj * TOTAL_NODES_5D;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								cz = cy + ck * TOTAL_NODES_6D;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									cw = cz + cl * TOTAL_NODES_7D;
									cout << weights[cw] << " ";
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

	return 0;
}
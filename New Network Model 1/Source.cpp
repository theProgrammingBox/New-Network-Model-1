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

	uint64_t i, j, k, l, ci, cj, ck, cl;
	int64_t y, z, w, cx, cy, cz, px, py, pz, pw;
	Random random;

	state = new float[TOTAL_NODES_4D];
	futureState = new float[TOTAL_NODES_4D];
	bias = new float[TOTAL_NODES_4D];
	weights = new float[TOTAL_NODES_8D];

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
									weights[cz + cl * TOTAL_NODES_7D] = ci == CONV_RADIUS && cj == CONV_RADIUS && ck == CONV_RADIUS && cl == CONV_RADIUS;
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
			y = i + j * TOTAL_NODES_1D;
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
						px = i + ci - CONV_RADIUS;
						px = px < 0 ? px + TOTAL_NODES_1D : px >= TOTAL_NODES_1D ? px - TOTAL_NODES_1D : px;
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							cy = cx + cj * TOTAL_NODES_5D;
							py = px + (j + cj - CONV_RADIUS) * TOTAL_NODES_1D;
							py = py < 0 ? py + TOTAL_NODES_2D : py >= TOTAL_NODES_2D ? py - TOTAL_NODES_2D : py;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								cz = cy + ck * TOTAL_NODES_6D;
								pz = py + (k + ck - CONV_RADIUS) * TOTAL_NODES_2D;
								pz = pz < 0 ? pz + TOTAL_NODES_3D : pz >= TOTAL_NODES_3D ? pz - TOTAL_NODES_3D : pz;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									pw = pz + (l + cl - CONV_RADIUS) * TOTAL_NODES_3D;
									pw = pw < 0 ? pw + TOTAL_NODES_4D : pw >= TOTAL_NODES_4D ? pw - TOTAL_NODES_4D : pw;

									futureState[w] += state[pw] * weights[cz + cl * TOTAL_NODES_7D];
								}
							}
						}
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
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << state[z + l * TOTAL_NODES_3D] << " ";
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
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << futureState[z + l * TOTAL_NODES_3D] << " ";
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
			y = i + j * TOTAL_NODES_1D;
			for (k = 0; k < TOTAL_NODES_1D; k++)
			{
				z = y + k * TOTAL_NODES_2D;
				for (l = 0; l < TOTAL_NODES_1D; l++)
				{
					cout << bias[z + l * TOTAL_NODES_3D] << " ";
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
			y = i + j * TOTAL_NODES_1D;
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
									cout << weights[cz + cl * TOTAL_NODES_7D] << " ";
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

	delete[] state;
	delete[] futureState;
	delete[] bias;
	delete[] weights;

	return 0;
}
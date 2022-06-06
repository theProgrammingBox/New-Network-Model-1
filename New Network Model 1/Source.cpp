#include "Header.h"

int main()
{
	const uint64_t TOTAL_NODES_1D = 3;
	const uint64_t CONV_RADIUS = 1;
	const uint64_t TOTAL_WEIGHTS_1D = 2 * CONV_RADIUS + 1;
	assert(TOTAL_NODES_1D >= TOTAL_WEIGHTS_1D);
	/*having TOTAL_WEIGHTS_1D > TOTAL_NODES_1D will result in
	convolution to overlap resulting in redundant computation.
	However, not checking for this may result in different
	good and bad "features"*/

	const uint64_t TOTAL_NODES_2D = TOTAL_NODES_1D * TOTAL_NODES_1D;
	const uint64_t TOTAL_NODES_3D = TOTAL_NODES_2D * TOTAL_NODES_1D;
	const uint64_t TOTAL_NODES_4D = TOTAL_NODES_3D * TOTAL_NODES_1D;
	const uint64_t TOTAL_NODES_5D = TOTAL_NODES_4D * TOTAL_WEIGHTS_1D;
	const uint64_t TOTAL_NODES_6D = TOTAL_NODES_5D * TOTAL_WEIGHTS_1D;
	const uint64_t TOTAL_NODES_7D = TOTAL_NODES_6D * TOTAL_WEIGHTS_1D;
	const uint64_t TOTAL_NODES_8D = TOTAL_NODES_7D * TOTAL_WEIGHTS_1D;
	assert(TOTAL_NODES_8D <= UINT32_MAX);
	/*don't want to overflow the uint32_t index cuz it will cause
	weird bugs when computing the future state*/

	float* state = nullptr;
	float* futureState = nullptr;
	float* bias = nullptr;
	float* weights = nullptr;

	uint64_t i, j, k, l, ci, cj, ck, cl;
	int64_t y, z, w, wx, wy, wz, cx, cy, cz, cw;
	Random random;

	state = new float[TOTAL_NODES_4D];
	futureState = new float[TOTAL_NODES_4D];
	bias = new float[TOTAL_NODES_4D];
	weights = new float[TOTAL_NODES_8D];
	assert(state != nullptr);
	assert(futureState != nullptr);
	assert(bias != nullptr);
	assert(weights != nullptr);
	/*allocate memory for the state, future state, bias, and weights*/

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
					state[w] = random.NormalRandom(0, 0.5);
					bias[w] = random.NormalRandom(0, 0.01);
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
									weights[wz + cl * TOTAL_NODES_7D] =
										float(
											ci == CONV_RADIUS &&
											cj == CONV_RADIUS &&
											ck == CONV_RADIUS &&
											cl == CONV_RADIUS
											)
										+ random.NormalRandom(0, 0.01);
									/*identity matrix with a small amount of noise*/
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
						wx = w + ci * TOTAL_NODES_4D;
						cx = i + ci - CONV_RADIUS;
						cx = cx < 0 ? cx + TOTAL_NODES_1D :
							cx >= TOTAL_NODES_1D ? cx - TOTAL_NODES_1D : cx;
						/*wrap around the edges of that dimention if at edge*/
						for (cj = 0; cj < TOTAL_WEIGHTS_1D; cj++)
						{
							wy = wx + cj * TOTAL_NODES_5D;
							cy = cx + (j + cj - CONV_RADIUS) * TOTAL_NODES_1D;
							cy = cy < 0 ? cy + TOTAL_NODES_2D :
								cy >= TOTAL_NODES_2D ? cy - TOTAL_NODES_2D : cy;
							for (ck = 0; ck < TOTAL_WEIGHTS_1D; ck++)
							{
								wz = wy + ck * TOTAL_NODES_6D;
								cz = cy + (k + ck - CONV_RADIUS) * TOTAL_NODES_2D;
								cz = cz < 0 ? cz + TOTAL_NODES_3D :
									cz >= TOTAL_NODES_3D ? cz - TOTAL_NODES_3D : cz;
								for (cl = 0; cl < TOTAL_WEIGHTS_1D; cl++)
								{
									cw = cz + (l + cl - CONV_RADIUS) * TOTAL_NODES_3D;
									cw = cw < 0 ? cw + TOTAL_NODES_4D :
										cw >= TOTAL_NODES_4D ? cw - TOTAL_NODES_4D : cw;
									futureState[w] += state[cw] * weights[wz + cl * TOTAL_NODES_7D];
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

	/*cout << "weights matrix" << endl;
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
									cout << weights[wz + cl * TOTAL_NODES_7D] << " ";
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

	delete[] state;
	delete[] futureState;
	delete[] bias;
	delete[] weights;

	return 0;
}
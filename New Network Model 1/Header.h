#pragma once
#include <iostream>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include "dirent.h"
#include <algorithm>
#include "Randoms.h"

using namespace std;

class NetworkParameters;
class Network;

bool ErrorCheckIntInput(int& input, int min, int max);
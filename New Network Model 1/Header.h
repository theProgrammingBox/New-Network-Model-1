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

using namespace std;

class NetworkParameters;

bool ErrorCheckIntInput(int& input, int min, int max);
#include "Header.h"

bool ErrorCheckIntInput(int& input, int min, int max)
{
	if (!(cin >> input))
	{
		cout << "\n**** Please input a number between " << min << " and " << max << " ****\n\n";
		cin.clear();
		cin.ignore(1000, '\n');
		return true;
	}
	else if (input < min || input > max)
	{
		cout << "\n**** The number " << setw(5) << input << " is an invalid entry  ****\n";
		cout << "**** Please input a number between " << min << " and " << max << " ****\n\n";
		cin.ignore(1000, '\n');
		return true;
	}
	else
	{
		cout << endl;
		cin.ignore(1000, '\n');
		return false;
	}
}
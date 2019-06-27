/*

AC circuit project
By Tom Moran
12/5/19

This program takes a circuit class and can fill it with components
Components are inherited from an abstract base class for component
There are: reisstors, inductors, capacitors
As well as a component for a user-specified component with a defined inductance
And a nested circuit component, that takes a circuit as it's argument

This file contians only the main function, that defines how the user interacts with the programs

There are two types of input: from a txt file or from the display
It can then be printed to a txt file or the display


*/

#include "AC_Circuit_Classes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <algorithm>

//define the value of PI
#define Pi 3.1415926535897;

using namespace std;

int main()
{
	ExplanationOfProgram();

	try
	{
		circuit Circuit;
		DecideAndRunInput(Circuit);

		DecideAndRunOutput(Circuit);

	}
	catch (double errorFlag)
	{
		if (errorFlag == BadFunction)
			cout << "An invalid function was called up" << endl;

		exit(errorFlag);
	}

	return 0;
		
}

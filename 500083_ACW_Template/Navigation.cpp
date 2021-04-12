#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include "ACW_Wrapper.h"

using namespace std;

Navigation::Navigation() : _outFile("Output.txt")
{
}

Navigation::~Navigation()
{
}

bool Navigation::ProcessCommand(const string& commandString)
{
	istringstream inString(commandString);
	string command;
	inString >> command;

	// Add your code here

	return false;
}

bool Navigation::BuildNetwork(const string &fileNamePlaces, const string &fileNameLinks)
{
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);
	if (finPlaces.fail() || finLinks.fail()) return false;

	// ****** Add your code here *******

	// example code of using the LLtoUTM function from ACW_Wrapper to convert 
	// latitude and longitude values into x and y global coordinates:
	double latitude = 53.770, longitude = -0.368, x, y;
	LLtoUTM(latitude, longitude, x, y);
	

	return true;
}

// Add your code here

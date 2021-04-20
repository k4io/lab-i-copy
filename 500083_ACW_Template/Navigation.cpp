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
	m_node = NULL;
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);
	if (finPlaces.fail() || finLinks.fail()) return false;
	
	vector<Node*> m_place;
	if (finPlaces.is_open())
	{
		while (!finPlaces.eof())
		{
			//get the place name and refrence number lat and long and adds it to a vector for node pointers
			char line[255];
			string placename;
			int refernce;
			finPlaces.getline(line, 255, ',');
			placename = string(line);
			finPlaces.getline(line, 255, ',');
			//converts string to a int.
			istringstream inRefernce(line);
			inRefernce >> refernce;
			double latitude;
			double longitude;
			double x;
			double y;
			finPlaces.getline(line, 255, ',');
			istringstream inLat(line);
			inLat >> latitude;
			finPlaces.getline(line, 255);
			istringstream inLong(line);
			inLong >> longitude;


			//converts them and makes x and y global
			LLtoUTM(latitude, longitude, x, y);
			//creates a new object and adds it the the vector.
			m_node = new Node(placename, refernce, x, y);
			m_place.push_back(m_node);

			if (finPlaces.eof())
			{
				finPlaces.close();
				return true;
			}
		}
	}








	return true;
}

// Add your code here

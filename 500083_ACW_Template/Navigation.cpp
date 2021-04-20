#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <sstream>

#include "ACW_Wrapper.h"

using namespace std;

Navigation::Navigation() : _outFile("Output.txt")
{
	LOG_ENTRY_EXIT;
}

Navigation::~Navigation()
{
}

TransportMode Navigation::determineTransportMode(string mode) 
{
	LOG_ENTRY_EXIT;
	if (mode.find("Foot") != string::npos) { return TransportMode::Foot; }
	else if (mode.find("Bike") != string::npos) { return TransportMode::Bike; }
	else if (mode.find("Car") != string::npos) { return TransportMode::Car; }
	else if (mode.find("Bus") != string::npos) { return TransportMode::Bus; }
	else if (mode.find("Rail") != string::npos) { return TransportMode::Rail; }
	else if (mode.find("Ship") != string::npos) { return TransportMode::Ship; }
}

Node* Navigation::determineNode(int ref)
{
	LOG_ENTRY_EXIT;
	for (size_t i = 0; i < v_Nodes.size(); i++)
		if (v_Nodes[i]->GetRefNum() == ref)
			return v_Nodes[i];
	return 0;
}

void Navigation::parsePlaces(fstream* in, vector<Node*>* nv_Places)
{
	LOG_ENTRY_EXIT;
	if (in->is_open())
	{
		while (!in->eof())
		{
			//get the place name and refrence number lat and long and adds it to a vector for node pointers
			char line[255];
			string placename;
			int refernce;
			in->getline(line, 255, ',');
			placename = string(line);
			in->getline(line, 255, ',');
			//converts string to a int.
			istringstream inRefernce(line);
			inRefernce >> refernce;
			double latitude;
			double longitude;
			double x;
			double y;
			in->getline(line, 255, ',');
			istringstream inLat(line);
			inLat >> latitude;
			in->getline(line, 255);
			istringstream inLong(line);
			inLong >> longitude;


			//converts them and makes x and y global
			LLtoUTM(latitude, longitude, x, y);
			//creates a new object and adds it the the vector.
			m_node = new Node(placename, refernce, x, y);
			nv_Places->push_back(m_node);
		}
		in->close();
	}
}

void Navigation::parseLinks(fstream* in, vector<Arc*>* nv_Links)
{
	LOG_ENTRY_EXIT;
	if (in->is_open())
	{
		while (!in->eof())
		{
			//get the place name and refrence number lat and long and adds it to a vector for node pointers
			char line[255];
			int i_Origin, i_Dest;
			string transportModeStr;

			in->getline(line, 255, ',');

			i_Origin = stoi(line);
			in->getline(line, 255, ',');
			i_Dest = stoi(line);
			in->getline(line, 255);
			transportModeStr = string(line);

			//make arc here
			Node* n_Origin = determineNode(i_Origin);
			Node* n_Destination = determineNode(i_Dest);
			TransportMode _transportMode = determineTransportMode(transportModeStr);

			m_arc = new Arc(_transportMode, n_Origin, n_Destination);

			nv_Links->push_back(m_arc);
		}
		in->close();
	}
}

bool Navigation::ProcessCommand(const string& commandString)
{
	LOG_ENTRY_EXIT;
	istringstream inString(commandString);
	string command;
	inString >> command;

	// Add your code here

	return false;
}

bool Navigation::BuildNetwork(const string &fileNamePlaces, const string &fileNameLinks)
{
	LOG_ENTRY_EXIT;
	m_node = NULL;
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);

	if (finPlaces.fail() || finLinks.fail()) return false;

	parsePlaces(&finPlaces, &v_Nodes);
	parseLinks(&finLinks, &v_Arcs);

	return true;
}

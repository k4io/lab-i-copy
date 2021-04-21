#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <fstream>




#include "ACW_Wrapper.h"

using namespace std;

Navigation::Navigation() : _outFile("Output.txt")
{
}

Navigation::~Navigation()
{
	
}

double Navigation::RoundTo(double in, double decimalPlaces) 
{
	stringstream tmp;
	tmp << setprecision(3) << fixed << in;
	return stod(tmp.str());
}

TransportMode Navigation::determineTransportMode(string mode) 
{
	if (mode.find("Foot") != string::npos) { return TransportMode::Foot; }
	else if (mode.find("Bike") != string::npos) { return TransportMode::Bike; }
	else if (mode.find("Car") != string::npos) { return TransportMode::Car; }
	else if (mode.find("Bus") != string::npos) { return TransportMode::Bus; }
	else if (mode.find("Rail") != string::npos) { return TransportMode::Rail; }
	else if (mode.find("Ship") != string::npos) { return TransportMode::Ship; }
}

Node* Navigation::determineNode(int ref)
{
	for (size_t i = 0; i < v_Nodes.size(); i++)
		if (v_Nodes[i]->GetRefNum() == ref)
			return v_Nodes[i];
	return 0;
}

void Navigation::parsePlaces(fstream* in, vector<Node*>* nv_Places)
{
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

			m_arc = new Arc(_transportMode, 
				&n_Origin->m_X,
				&n_Origin->m_Y,
				&n_Destination->m_X,
				&n_Destination->m_Y, 
				&n_Origin->m_ref, 
				&n_Destination->m_ref
			);

			nv_Links->push_back(m_arc);
		}
		in->close();
	}
}

bool Navigation::ProcessCommand(const string& commandString)
{
	/*
	MaxDist
	MaxLink
	FindDist 9361783 11391765
	FindNeighbour 8611522
	Check Rail 14601225 12321385 8611522 9361783
	Check Ship 14601225 12321385 8611522 9361783
	FindRoute Rail 9081958 15832241
	FindRoute Ship 9081958 15832241
	FindShortestRoute Rail 9081958 15832241
	FindShortestRoute Ship 9081958 15832241
	*/
	istringstream inString(commandString);
	string command;
	inString >> command;

	if (command.find("MaxDist") != string::npos)
	{
		double largest = 0; 
		Node* currentNode, * destinationNode, * lStart{}, * lFinish{};
		for (size_t i = 0; i < v_Nodes.size(); i++)
		{
			currentNode = v_Nodes[i];
			for (size_t j = 0; j < v_Nodes.size(); j++)
			{
				destinationNode = v_Nodes[j];
				if (currentNode->GetDistanceTo(destinationNode) > largest) 
				{
					lStart = currentNode, lFinish = destinationNode;
					largest = currentNode->GetDistanceTo(destinationNode);
				} else continue;
			}
		}

		std::string output = "MaxDist\n"
			+ lStart->GetPlaceName() + ", "
			+ lFinish->GetPlaceName() + ", "
			+ to_string(RoundTo(largest, 3)) + "\n";

		_outFile << output << endl;
		return true;
	}

	else if (command.find("MaxLink") != string::npos) {
		int record = 0;
		Arc* recordLink{};
		for (size_t i = 0; i < v_Arcs.size(); i++)
		{
			if (v_Arcs[i]->getLength() > record)
				recordLink = v_Arcs[i];
		}

		string outStr = "MaxLink\n";
		outStr += to_string(*recordLink->_OriginRef) + ", "
			+ to_string(*recordLink->_DestinationRef) + ", "
			+ to_string(RoundTo(recordLink->length, 3)) + "\n";
		_outFile << outStr << endl;
		return true;
	}

	else if (command.find("FindDist") != string::npos) {
		string params = commandString.substr(9, commandString.size());
		int startingReference = stoi(params.substr(0, params.find(" ")));
		int destinationReference = stoi(params.substr(params.find(" "), params.size()));
		Node* startingNode{};
		Node* destinationNode{};
		for (size_t i = 0; i < v_Nodes.size(); i++)
		{
			if (v_Nodes[i]->GetRefNum() == startingReference)
			{	startingNode = v_Nodes[i];	}

			if (v_Nodes[i]->GetRefNum() == destinationReference)
			{	destinationNode = v_Nodes[i];	}

			if (startingNode && destinationNode)
				break;
		}

		double len = startingNode->GetDistanceTo(destinationNode);
		
		std::string _lstr = to_string(RoundTo((len / 1000), 3));
		_lstr.erase(_lstr.find_last_not_of('0') + 1, std::string::npos);

		std::string output = commandString + "\n"
			+ startingNode->GetPlaceName() + ", "
			+ destinationNode->GetPlaceName() + ", "
			+ _lstr.c_str() + "\n";

		_outFile << output << endl;
		return true;
	}

	else if (command.find("FindNeighbour") != string::npos) {
		int startingReference = stoi(commandString.substr(
									commandString.find(' '), 
									commandString.size()));
		vector<Node*> v_neighbors{};
		
		Node* startingNode = determineNode(startingReference);

		for (size_t i = 0; i < startingNode->v_Links.size(); i++)
		{
			if (*startingNode->v_Links[i]->_OriginRef == startingReference) {
				v_neighbors.push_back(
					determineNode(
						*startingNode->v_Links[i]->_DestinationRef
					));
			}
			else
				v_neighbors.push_back(
					determineNode(
						*startingNode->v_Links[i]->_OriginRef
					));
		}
		std::string outStr = commandString + "\n";

		for (size_t i = 0; i < v_neighbors.size(); i++)
			outStr += to_string(v_neighbors[i]->m_ref) + "\n";
		
		_outFile << outStr << endl;
		return true;
	}

	else if (command.find("Check") != string::npos) {
		//Example:
		//Check <mode> 14601225 12321385 8611522 9361783

		string params = commandString.substr(6, commandString.size());
		string strTMode = commandString.substr(0, params.find(' '));
		TransportMode _mode{};
		if (strTMode.find("Foot")) _mode = TransportMode::Foot;
		if (strTMode.find("Bike")) _mode = TransportMode::Bike;
		if (strTMode.find("Car"))  _mode = TransportMode::Car;
		if (strTMode.find("Bus"))  _mode = TransportMode::Bus;
		if (strTMode.find("Rail")) _mode = TransportMode::Rail;
		if (strTMode.find("Ship")) _mode = TransportMode::Ship;

		params = params.substr(4, params.size());

		vector<Node*> targetDestinations{};

		if (params[0] == ' ')
			params = params.substr(1, params.size());

		string str = params.substr(0, params.find(' '));

		while (params.size() > 3)
		{
			string cid = params.substr(0, params.find(' '));
			targetDestinations.push_back(
				determineNode(
					stoi(cid)
					)
			);
			params = params.substr(cid.size(), params.size());
			if (params[0] == ' ')
				params = params.substr(1, params.size());
		}

		string strout = commandString + "\n";

		for (size_t i = 0; i < targetDestinations.size(); i++)
		{
			for (size_t f = 0; f < targetDestinations[i]->v_Links.size(); f++)
			{
				//TO DO - DO THE THING HERE: https://i.imgur.com/jOP9ieo.png
			}
		}
	}
	else if (command.find("FindRoute") != string::npos) {

	}
	else if (command.find("FindShortestRoute") != string::npos) {

	}

	return false;
}

bool Navigation::BuildNetwork(const string &fileNamePlaces, const string &fileNameLinks)
{
	m_node = NULL;
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);

	if (finPlaces.fail() || finLinks.fail()) return false;

	parsePlaces(&finPlaces, &v_Nodes);
	parseLinks(&finLinks, &v_Arcs);

	vector<Node*> newNodes{};


	//Iterate every arc for each node to determine if the arc has a reference to that node.
	for (size_t i = 0; i < v_Nodes.size(); i++)
	{
		Node* newNode = v_Nodes[i];
 		for (size_t j = 0; j < v_Arcs.size(); j++)
		{
			if (*v_Arcs[j]->_OriginRef == v_Nodes[i]->m_ref
				|| *v_Arcs[j]->_DestinationRef == v_Nodes[i]->m_ref)
			{
				newNode->v_Links.push_back(v_Arcs[j]);
			}
		}
		newNodes.push_back(newNode);
	}

	v_Nodes = newNodes;

	return true;
}

#include "Navigation.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <fstream>




#include "ACW_Wrapper.h"

using namespace std;

Navigation::Navigation() : _outFile("Output.txt"), m_node(nullptr), m_arc(nullptr)
{

}

Navigation::~Navigation()
{
	delete m_node;
	delete m_arc;
	v_Arcs.clear();
	v_Nodes.clear();
}

Navigation& Navigation::operator=(const Navigation& ul)
{
	_outFile = ofstream("Output.txt");
	m_node = ul.m_node;
	m_arc = ul.m_arc;
	v_Arcs = ul.v_Arcs;
	v_Nodes = ul.v_Nodes;
	return *this;
}

double Navigation::RoundTo(const double in, const int decimalPlaces) const
{
	stringstream tmp;
	tmp << setprecision(decimalPlaces) << fixed << in;
	return stod(tmp.str());
}

TransportMode Navigation::determineTransportMode(const string &mode) const
{
	if (mode.find("Foot") != string::npos) { return TransportMode::Foot; }
	else if (mode.find("Bike") != string::npos) { return TransportMode::Bike; }
	else if (mode.find("Car") != string::npos) { return TransportMode::Car; }
	else if (mode.find("Bus") != string::npos) { return TransportMode::Bus; }
	else if (mode.find("Rail") != string::npos) { return TransportMode::Rail; }
	else if (mode.find("Ship") != string::npos) { return TransportMode::Ship; }
	else return TransportMode::ERROR;
}

Node* Navigation::determineNode(const int ref)
{
	for (size_t i = 0; i < v_Nodes.size(); i++)
		if (v_Nodes[i]->GetRefNum() == ref)
			return v_Nodes[i];
	return 0;
}

void Navigation::parsePlaces(fstream& const in, vector<Node*>* const nv_Places)
{
	if (in.is_open())
	{
		while (!in.eof())
		{
			//get the place name and refrence number lat and long and adds it to a vector for node pointers
			char line[255];
			//string line;
			string placename;
			int refernce;


			in.getline(line, 255, ',');
			placename = string(line);
			in.getline(line, 255, ',');
			//converts string to a int.
			istringstream inRefernce(line);
			inRefernce >> refernce;
			double latitude;
			double longitude;
			double x;
			double y;
			in.getline(line, 255, ',');
			istringstream inLat(line);
			inLat >> latitude;
			in.getline(line, 255);
			istringstream inLong(line);
			inLong >> longitude;


			//converts them and makes x and y global
			LLtoUTM(latitude, longitude, x, y);
			//creates a new object and adds it the the vector.
			m_node = new Node(placename, refernce, x, y);
			nv_Places->push_back(m_node);
		}
		in.close();
	}
}

void Navigation::parseLinks(fstream* const in, vector<Arc*>* const nv_Links)
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

bool Navigation::canPass(const TransportMode const _t, const Arc* const _a) const
{
	//get heirarchy and then return true or false 
	//if the transport mode can pass through the 
	//arc at some point within the heirarchy

	/*
	* Heirarchy:
	* 
	* 1. a rail or ship journey may only use Arcs of the corresponding mode;
	* 2. a bus journey may use bus and ship Arcs, while a car journey may use car, bus and ship Arcs;
	* 3. a bike journey may use bike Arcs and Arcs defined in 1 and 2;
	* 4. a foot journey may use any Arc.
	*/

	//First rule (Rail & Ship)
	if (_t == TransportMode::Rail && _a->t_Mode == TransportMode::Rail) return true;
	if (_t == TransportMode::Ship && _a->t_Mode == TransportMode::Ship) return true;

	//Second rule (Bus & Car)
	if (_t == TransportMode::Bus && _a->t_Mode == TransportMode::Ship) return true;
	if (_t == TransportMode::Bus && _a->t_Mode == TransportMode::Bus) return true;

	if (_t == TransportMode::Car && _a->t_Mode == TransportMode::Ship) return true;
	if (_t == TransportMode::Car && _a->t_Mode == TransportMode::Bus) return true;
	if (_t == TransportMode::Car && _a->t_Mode == TransportMode::Car) return true;

	//Third rule (bike)
	if (_t == TransportMode::Bike && _a->t_Mode != TransportMode::Foot) return true;

	//Fourth rule (foot)
	if (_t == TransportMode::Foot && _a->t_Mode != TransportMode::ERROR) return true;

	return false;
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
		double largest = 0;															//Track for largest distance
		Node* currentNode, * destinationNode, * lStart{}, * lFinish{};				//Init node buffers 
		for (size_t i = 0; i < v_Nodes.size(); i++)									//Iterate global node list
		{
			currentNode = v_Nodes[i];												//Set working node 'currentNode'
			for (size_t j = 0; j < v_Nodes.size(); j++)								//Iterate global list again
			{
				destinationNode = v_Nodes[j];										//Set working node 'destinationNode'
				if (currentNode->GetDistanceTo(destinationNode) > largest)			//Check distance between working nodes 'currentNode' and 'destinationNode'
				{	
					lStart = currentNode, lFinish = destinationNode;				//Set working start and finish nodes
					largest = currentNode->GetDistanceTo(destinationNode);			//Set largest record to current length
				} else continue;													//If not larger than record continue to next iteration
			}
		}

		const std::string output = "MaxDist\n"
			+ *lStart->GetPlaceName() + ", "
			+ *lFinish->GetPlaceName() + ", "
			+ to_string(RoundTo(largest / 1000, 3)) + "\n";

		_outFile << output << endl;
		return true;
	}

	else if (command.find("MaxLink") != string::npos) {
		double recordlen = 0.0;
		Arc* recordLink{};
		for (size_t i = 0; i < v_Arcs.size(); i++)
		{
			if (v_Arcs[i]->getLength() > recordlen) {
				recordlen = v_Arcs[i]->length;
				recordLink = v_Arcs[i];
			}
 		}
 		if (!recordLink) return false;

		string outStr = "MaxLink\n";
		outStr += to_string(*recordLink->_OriginRef) + ", "
			+ to_string(*recordLink->_DestinationRef) + ", "
			+ to_string(RoundTo(recordLink->length, 3)) + "\n";
		_outFile << outStr << endl;
		return true;
	}

	else if (command.find("FindDist") != string::npos) {
		const string params				= commandString.substr(9, commandString.size());
		const int startingReference		= stoi(params.substr(0, params.find(" ")));
		const int destinationReference	= stoi(params.substr(params.find(" "), params.size()));
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

		std::string const output = commandString + "\n"
			+ *startingNode->GetPlaceName() + ", "
			+ *destinationNode->GetPlaceName() + ", "
			+ _lstr.c_str() + "\n";

		_outFile << output << endl;
		return true;
	}

	else if (command.find("FindNeighbour") != string::npos) {
		int const startingReference = stoi(commandString.substr(
									commandString.find(' '), 
									commandString.size()));
		vector<Node*> v_neighbors{};
		
		Node* const startingNode = determineNode(startingReference);

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
		TransportMode const _mode = determineTransportMode(params);

		params = params.substr(4, params.size());

		vector<Node*> targetDestinations{};

		if (params[0] == ' ')
			params = params.substr(1, params.size());

		string const str = params.substr(0, params.find(' '));

		while (params.size() > 3)
		{
			string const cid = params.substr(0, params.find(' '));
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
			if (i + 1 > targetDestinations.size() - 1) break;
			Node* const currentNode = targetDestinations[i];
			Node* const targetNode = targetDestinations[i + 1];
			bool targetIsLinked = false;

			strout += to_string(currentNode->m_ref) + ", "
					+ to_string(targetNode->m_ref);

			for (size_t f = 0; f < currentNode->v_Links.size(); f++)
			{
				if (*currentNode->v_Links[f]->_OriginRef == targetNode->m_ref
					|| *currentNode->v_Links[f]->_DestinationRef == targetNode->m_ref)
				{
					if (canPass(_mode, currentNode->v_Links[f]))
					{
						targetIsLinked = true;
						strout += ", PASS\n";
						break;
					}
					else
					{
						targetIsLinked = false;
						strout += ", FAIL\n";
						break;
					}
				}
			}
			if (!targetIsLinked)
			{
				break;
			}
		}
		_outFile << strout << endl;
		return true;
	}

	else if (command.find("FindRouteFFF") != string::npos) {
		string params = commandString.substr(9, commandString.size());

		TransportMode const _mode = determineTransportMode(params);

		Node* firstNode{};
		Node* targetNode{};

		params		= params.substr(params.find(' ') + 1, params.size());
		params		= params.substr(params.find(' ') + 1, params.size());
		firstNode	= determineNode(stoi(params.substr(0, params.find(' '))));
		params		= params.substr(params.find(' ') + 1, params.size());
		targetNode	= determineNode(stoi(params.substr(0, params.find(' '))));

		if (!firstNode || !targetNode) return false;

		Node* currentNode = firstNode, * ParentNode = firstNode, * const tempNode{};
		Arc* const currentArc{};

		vector<Node*> v_Failed{}, v_History{}, neighbors{};

		const string outstr{};

		while (currentNode != targetNode)
		{
			v_History.push_back(const_cast<Node*>(currentNode));
			getNeighboringNodes(currentNode, v_Failed, &neighbors);
			if (neighbors.size() < 1)
			{
				v_Failed.push_back(const_cast<Node*>(currentNode));
				currentNode = ParentNode;
				ParentNode = v_History[v_History.size() - 1];
			}
			else
			{
				for (size_t i = 0; i < neighbors.size(); i++)
				{
					for (size_t j = 0; j < v_History.size(); j++)
					{
						if (neighbors[i]->m_ref == v_History[j]->m_ref)
							continue;

						//Check if current neighbor has failed previous if so try another
						if (find(v_Failed.begin(),
							v_Failed.end(),
							neighbors[i]) != v_Failed.end())
						{
							i++;
							continue;
						}
						currentNode = neighbors[i];
						break;
					}
				}
				v_History = {};
			}
		}
		_outFile << outstr << endl;
	}

	else if (command.find("FindShortestRoute") != string::npos) {

	}

	return false;
}

void Navigation::getNeighboringNodes(const Node* const n_master, vector<Node*> &failedNodes, vector<Node*>* const neigbors)
{
	Node* const currentNode = const_cast<Node*>(n_master);
	for (size_t i = 0; i < currentNode->v_Links.size(); i++)
	{
		Arc* const currentArc = currentNode->v_Links[i];
		if (*currentArc->_DestinationRef == currentNode->m_ref
			&& find(failedNodes.begin(),
				failedNodes.end(),
				determineNode(*currentArc->_OriginRef)) == failedNodes.end())
			neigbors->push_back(determineNode(*currentArc->_OriginRef));
		if (*currentArc->_OriginRef == currentNode->m_ref
			&& find(failedNodes.begin(),
				failedNodes.end(),
				determineNode(*currentArc->_DestinationRef)) == failedNodes.end())
			neigbors->push_back(determineNode(*currentArc->_DestinationRef));
	}
	return;
}

bool Navigation::BuildNetwork(const string &fileNamePlaces, const string &fileNameLinks)
{
	m_node = NULL;
	fstream finPlaces(fileNamePlaces);
	fstream finLinks(fileNameLinks);

	if (finPlaces.fail() || finLinks.fail()) return false;

	parsePlaces(finPlaces, &v_Nodes);
	parseLinks(&finLinks, &v_Arcs);

	vector<Node*> newNodes{};


	//Iterate every arc for each node to determine if the arc has a reference to that node.
	for (size_t i = 0; i < v_Nodes.size(); i++)
	{
		Node* const newNode = v_Nodes[i];
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

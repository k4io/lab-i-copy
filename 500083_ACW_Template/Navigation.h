#pragma once

#include <fstream>
#include <string>
//#include "Node.h"
#include "Arc.h"

class Navigation
{
	std::ofstream _outFile;

public:
	Navigation();
	~Navigation();

	bool BuildNetwork(const std::string& fileNamePlaces, const std::string& fileNameLinks);
	bool ProcessCommand(const std::string& commandString);
	void parsePlaces(fstream* in, vector<Node*>* nv_Places);
	void parseLinks(fstream* in, vector<Arc*>* nv_Links);
	Node* determineNode(int ref);
	TransportMode determineTransportMode(string mode);

private:
	Node* m_node;
	Arc* m_arc;
	vector<Node*> v_Nodes;
	vector<Arc*> v_Arcs;
};
#pragma once

#include <fstream>
#include <algorithm> //for std::find
#include <string>
#include "Node.h"
#include "Arc.h"

class Navigation
{
	struct Node_Path
	{
		vector<Node*> places;
		int _length;
	};
	std::ofstream _outFile;

public:
	Navigation();
	~Navigation();

	/// <summary>
	/// Copy operator
	/// </summary>
	/// <param name="ul"> - copy object</param>
	/// <returns>reference to new object</returns>
	Navigation& operator=(const Navigation& ul);
	Navigation(const Navigation& ul);

	/// <summary>
	/// Member function to create node and arc network.
	/// </summary>
	/// <param name="fileNamePlaces"> - Reference to filename for places</param>
	/// <param name="fileNameLinks"> - Reference to filename for links</param>
	/// <returns>Success of build</return>
	bool BuildNetwork(const std::string& fileNamePlaces, const std::string& fileNameLinks);

	/// <summary>
	/// Member function to process commands
	/// </summary>
	/// <param name="commandString"> - Reference to command string</param>
	/// <returns>Success of command</returns>
	bool ProcessCommand(const std::string& commandString);

	/// <summary>
	/// Parses from file into Node array
	/// </summary>
	/// <param name="in"> - Pointer to filestream in</param>
	/// <param name="nv_Places"> - Pointer to array buffer</param>
	void parsePlaces(fstream& const in, vector<Node*>* const nv_Places);

	/// <summary>
	/// Parses from file into Arc array 
	/// </summary>
	/// <param name="in"> - Pointer to filestream in</param>
	/// <param name="nv_Links"> - Pointer to array buffer</param>
	void parseLinks(fstream* const in, vector<Arc*>* const nv_Links);

	/// <summary>
	/// Member function to determine 
	/// Node by reference.
	/// </summary>
	/// <param name="ref"> - Target reference</param>
	/// <returns>Pointer to target, nullptr if not found</returns>
	Node* determineNode(const int ref);
	
	/// <summary>
	/// Member function to determine
	/// mode of transport given a string
	/// </summary>
	/// <param name="mode"> - transport mode</param>
	/// <see cref="structs::TransportMode"/>
	/// <returns>Transport mode, TransportMode::ERROR if not found</returns>
	TransportMode determineTransportMode(const string& mode) const;

	/// <summary>
	/// Member function to round value to
	/// specified number of decimal places
	/// </summary>
	/// <param name="in"> - number to round</param>
	/// <param name="decimalPlaces"> - decimal places to round to</param>
	/// <returns>new number rounded to specific amount</returns>
	double RoundTo(const double in, const int decimalPlaces) const;

	/// <summary>
	/// Member function to determine if
	/// an Arc contains a target transport mode
	/// </summary>
	/// <param name="_t"> - Transport mode</param>
	/// <param name="_a"> - Arc to check</param>
	/// <returns>True if correct mode</returns>
	bool canPass(const TransportMode const _t, const Arc* const _a) const;
	
	/// <summary>
	/// Member function to get all neighboring
	/// nodes connected via link
	/// </summary>
	/// <param name="n_master"> - Master node to originate search from</param>
	/// <param name="failedNodes"> - Reference to buffer for failed Nodes</param>
	/// <param name="neighbors"> - Reference to buffer for neighboring Nodes</param>
	void getNeighboringNodes(const Node* const n_master, vector<Node*> &failedNodes, vector<Node*>* const neighbors);

	/// <summary>
	/// Member function to get all neighboring
	/// nodes connected via link if they can
	/// pass with correct transport mode
	/// </summary>
	/// <param name="n_master"> - Master node to originate search from</param>
	/// <param name="failedNodes"> - Reference to buffer for failed Nodes</param>
	/// <param name="neighbors"> - Reference to buffer for neighboring Nodes</param>
	/// <param name="_mode"> - Transport mode to use</param>
	void getNeighboringNodes(const Node* const n_master, vector<Node*>& failedNodes, vector<Node*>* const neigbors, TransportMode _mode);

	/// <summary>
	/// Member function to find all possible paths
	/// from one node to another with the correct
	/// transport method (if any) (doesnt actually get ALL possible paths, just never the same stops)
	/// </summary>
	/// <param name="originNode"> - Node to search from</param>
	/// <param name="destinationNode"> - Target node to search for</param>
	/// <param name="_mode"> - Transport mode to use</param>
	/// <returns>Vector array of encapsulated paths</returns>
	vector<Node_Path> findAllRoutes(const Node* const originNode, const Node* const destinationNode, TransportMode const _mode);

	/// <summary>
	/// Member function that has the same functionality
	/// as findAllRoutes but was made with the idea of
	/// only looking for 1 path.
	/// </summary>
	/// <param name="originNode"> - Node to search from</param>
	/// <param name="destinationNode"> - Target node to search for</param>
	/// <param name="_mode"> - Transport mode to use</param>
	/// <returns>Vector array of encapsulated nodes from 1 path</returns>
	vector<Node*> findRoute(const Node* const originNode, const Node* const destinationNode, TransportMode const _mode);


private:
	Node* m_node;
	Arc* m_arc;
	vector<Node*> v_Nodes;
	vector<Arc*> v_Arcs;
};
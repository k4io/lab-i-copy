#pragma once

/*
* Transport mode heirachy:
* 1. a rail or ship journey may only use Arcs of the corresponding mode; 
* 2. a bus journey may use bus and ship Arcs, while a car journey may use car, bus and ship Arcs;
* 3. a bike journey may use bike Arcs and Arcs defined in 1 and 2;
* 4. a foot journey may use any Arc.
*/

//Local includes
#include "Structs.hpp"
#include "Node.h"

//Standard includes
#include <iostream>


using namespace structs;
class Arc
{
public:
	/// <summary>
	/// Constructor for arc class.
	/// </summary>
	/// <param name="_transport">Transport mode</param>
	/// <param name="_Origin">Origin arc</param>
	/// <param name="_Destination">Destination arc</param>
	Arc(TransportMode _transport, Node* _Origin, Node* _Destination);

	~Arc();

	/// <summary>
	/// Function to retrieve transport mode of the current arc.
	/// </summary>
	/// <returns>The transport mode attribute</returns>
	TransportMode getTransportMode();

	/// <summary>
	/// Function to retrieve origin node of the current arc.
	/// </summary>
	/// <returns>The origin node attribute</returns>
	Node* getOrigin();

	/// <summary>
	/// Function to retrieve destination node of the current arc.
	/// </summary>
	/// <returns>The destination node attribute</returns>
	Node* getDest();

	/// <summary>
	/// Function to set transport mode.
	/// </summary>
	/// <param name="_t">Required transport mode</param>
	void setTransportMode(TransportMode _t);

	/// <summary>
	/// Function to set origin node.
	/// </summary>
	/// <param name="_n">Required origin node</param>
	void setOrigin(Node* _n);

	/// <summary>
	/// Function to set destination node.
	/// </summary>
	/// <param name="_n">Required destination node</param>
	void setDest(Node* _n);



private:
	TransportMode t_Mode;	//Transport mode
	Node* n_Origin;			//Origin destination node
	Node* n_Dest;			//Destination node
};

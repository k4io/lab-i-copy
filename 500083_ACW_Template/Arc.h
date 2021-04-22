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

//Standard includes
#include <iostream>


using namespace structs;
class Arc
{
public:
	friend class Navigation;
	/// <summary>
	/// Constructor for arc class.
	/// </summary>
	/// <param name="_transport"></param>
	/// <param name="_Origin_X"></param>
	/// <param name="_Origin_Y"></param>
	/// <param name="_Destination_X"></param>
	/// <param name="_Destination_Y"></param>
	/// <param name="OriginRef"></param>
	/// <param name="DestinationRef"></param>
	Arc(TransportMode _transport,
		double* _Origin_X,
		double* _Origin_Y,
		double* _Destination_X,
		double* _Destination_Y,
		int* OriginRef,
		int* DestinationRef);

	~Arc();

	/// <summary>
	/// Function to retrieve transport mode of the current arc.
	/// </summary>
	/// <returns>The transport mode attribute</returns>
	TransportMode getTransportMode();

	/// <summary>
	/// Function to retrieve origin node of the current arc.
	/// </summary>
	/// <returns>The origin node's reference attribute</returns>
	int* getOrigin();

	/// <summary>
	/// Function to retrieve destination node of the current arc.
	/// </summary>
	/// <returns>The destination node's reference attribute</returns>
	int* getDest();

	/// <summary>
	/// Function to retrieve length of arc.
	/// </summary>
	/// <returns>The link's length between nodes</returns>
	double getLength();

	/// <summary>
	/// Function to set transport mode.
	/// </summary>
	/// <param name="_t">Required transport mode</param>
	void setTransportMode(TransportMode _t);

	/// <summary>
	/// Function to set origin node.
	/// </summary>
	/// <param name="_n">Required origin node</param>
	void setOrigin(int* _n);

	/// <summary>
	/// Function to set destination node.
	/// </summary>
	/// <param name="_n">Required destination node</param>
	void setDest(int* _n);

	/// <summary>
	/// Function to set length.
	/// </summary>
	/// <param name="_n">Required length</param>
	void setLen(double* _n);

private:
	TransportMode t_Mode;	//Transport mode
	double* _Origin_X,		//Origin X value
		* _Origin_Y,		//Origin Y value
		* _Destination_X,   //Destination X value
		* _Destination_Y;	//Destination Y value
	int * _OriginRef,		//Origin reference number
		* _DestinationRef;  //Destination reference number
	double	length;			//Length of arc
};

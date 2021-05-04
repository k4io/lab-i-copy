#pragma once
#include <string>
#include <vector>
#include "Arc.h"

using namespace std;

class Node {
public:
	friend class Navigation;
	Node(void);
	~Node(void);

	/// <summary>
	/// basic constructor for Node.
	/// </summary>
	/// <param name="name"> - Name of location (node)</param>
	/// <param name="ref"> - Reference number of node</param>
	/// <param name="x"> - X value of location (node)</param>
	/// <param name="y"> - Y value of location (node)</param>
	Node(string& name, int const ref, double const x, double const y);

	/// <summary>
	/// Getter for location name
	/// </summary>
	/// <returns>pointer to location string</returns>
	string* const GetPlaceName();
	/// <summary>
	/// Getter for reference number
	/// </summary>
	/// <returns>reference number</returns>
	int GetRefNum() const;
	/// <summary>
	/// Getter for X value of location
	/// </summary>
	/// <returns>X value of location</returns>
	double GetX()	const;
	/// <summary>
	/// Getter for Y value of location
	/// </summary>
	/// <returns>Y value of location</returns>
	double GetY()	const;
	/// <summary>
	/// Member function to retrieve distance
	/// to a target node via reference number.
	/// </summary>
	/// <param name="ref"> - Reference number of target node</param>
	/// <returns>distance between current node and target node</returns>
	double GetDistanceTo(Node* const ref);
	/// <summary>
	/// Iterates through objects links list
	/// for target reference.
	/// </summary>
	/// <param name="locationReference"> - Target node reference</param>
	/// <returns>Pointer to found arc,
	/// nullptr on failure</returns>
	Arc* getArc(const int* const locationReference);

	/// <summary>
	/// Setter for location name
	/// </summary>
	/// <param name="n"> - Reference to string</param>
	void SetPlaceName(const string& n);
	/// <summary>
	/// Setter for reference number
	/// </summary>
	/// <param name="r"> - Reference number</param>
	void SetRefName(int const r);
	/// <summary>
	/// Setter for X value
	/// </summary>
	/// <param name="x">value</param>
	void SetX(double const x);
	/// <summary>
	/// Setter for Y value
	/// </summary>
	/// <param name="y">value</param>
	void SetY(double const y);
private:
	vector<Arc*> v_Links;
	string m_name;
	int m_ref;
	double m_X;
	double m_Y;
};
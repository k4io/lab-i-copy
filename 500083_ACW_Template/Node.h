#pragma once
#include <string>
#include <vector>
#include "Arc.h"

using namespace std;

class Node {
public:
	friend class Navigation;
	Node(void);
	Node(string name, int ref, double x, double y);
	~Node(void);


	//Getter
	string GetPlaceName();
	int GetRefNum();
	double GetX();
	double GetY();
	double GetDistanceTo(Node* ref);
	Arc* getArc(int* locationReference);

	//Setter
	void SetPlaceName(string n);
	void SetRefName(int r);
	void SetX(double x);
	void SetY(double y);
private:
	vector<Arc*> v_Links;
	string m_name;
	int m_ref;
	double m_X;
	double m_Y;
};
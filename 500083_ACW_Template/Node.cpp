#include  "Node.h"


Node::Node(void): m_name(""), m_ref(0), m_X(0), m_Y(0)
{
	//LOG_ENTRY_EXIT;
}

Node::Node(string name, int ref, double x, double y): m_name(name), m_ref(ref), m_X(x), m_Y(y)
{
	//LOG_ENTRY_EXIT;
}

Node::~Node(void)
{
	
}

string Node::GetPlaceName()
{
	
	return m_name;
}

int Node::GetRefNum()
{
	return m_ref;
}

double Node::GetX()
{
	
	return m_X;
}

double Node::GetY()
{
	
	return m_Y;
}

double Node::GetDistanceTo(Node* ref)
{
	double x1, x2, y1, y2, dy, dx, total;
	Node* n0 = this;
	Node* n1 = ref;

	x1 = n0->GetX();
	x2 = n1->GetX();
	y1 = n0->GetY();
	y2 = n1->GetY();
	dx = pow((x2 - x1), 2);
	dy = pow((y2 - y1), 2);
	total = sqrt(dx + dy);
	return total;
}

void Node::SetPlaceName(string n)
{
	
	m_name = n;
}

void Node::SetRefName(int r)
{
	
	m_ref = r;
}

void Node::SetX(double x)
{
	
	m_X = x;
}

void Node::SetY(double y)
{
	
	m_Y = y;
}



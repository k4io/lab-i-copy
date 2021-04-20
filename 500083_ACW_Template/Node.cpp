#include  "Node.h"


Node::Node(void): m_name(""), m_ref(0), m_X(0), m_Y(0)
{
}

Node::Node(string name, int ref, double x, double y): m_name(name), m_ref(ref), m_X(x), m_Y(y)
{
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



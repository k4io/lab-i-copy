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
	LOG_ENTRY_EXIT;
}

string Node::GetPlaceName()
{
	LOG_ENTRY_EXIT;
	return m_name;
}

int Node::GetRefNum()
{
	//LOG_ENTRY_EXIT;
	return m_ref;
}

double Node::GetX()
{
	LOG_ENTRY_EXIT;
	return m_X;
}

double Node::GetY()
{
	LOG_ENTRY_EXIT;
	return m_Y;
}

void Node::SetPlaceName(string n)
{
	LOG_ENTRY_EXIT;
	m_name = n;
}

void Node::SetRefName(int r)
{
	LOG_ENTRY_EXIT;
	m_ref = r;
}

void Node::SetX(double x)
{
	LOG_ENTRY_EXIT;
	m_X = x;
}

void Node::SetY(double y)
{
	LOG_ENTRY_EXIT;
	m_Y = y;
}



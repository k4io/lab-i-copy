#include  "Node.h"


Node::Node(void): m_name(""), m_ref(0), m_X(0), m_Y(0)
{
	//LOG_ENTRY_EXIT;
}

Node::Node(string& name, int const ref, double const x, double const y): m_name(name), m_ref(ref), m_X(x), m_Y(y)
{
	//LOG_ENTRY_EXIT;
}

Arc* Node::getArc(const int* const locationReference)
{
	for (size_t i = 0; i < v_Links.size(); i++)
	{
		if (*v_Links[i]->getDest() == *locationReference
			|| *v_Links[i]->getOrigin() == *locationReference)
			return v_Links[i];
	}
	return nullptr;
}

Node::~Node(void)
{
	
}

string* const Node::GetPlaceName()
{
	//return const_cast<string*>(m_name);
	return const_cast<string*>(&m_name);
}

int Node::GetRefNum() const
{
	return m_ref;
}

double Node::GetX() const
{
	
	return m_X;
}

double Node::GetY() const
{
	
	return m_Y;
}

double Node::GetDistanceTo(Node* const ref)
{
	double x1, x2, y1, y2, dy, dx, total;
	Node* const n0 = this;
	Node* const n1 = ref;

	x1 = n0->GetX();
	x2 = n1->GetX();
	y1 = n0->GetY();
	y2 = n1->GetY();
	dx = pow((x2 - x1), 2);
	dy = pow((y2 - y1), 2);
	total = sqrt(dx + dy);
	return total;
}

void Node::SetPlaceName(const string& n)
{
	m_name = n;
}

void Node::SetRefName(int const r)
{
	m_ref = r;
}

void Node::SetX(double const x)
{
	m_X = x;
}

void Node::SetY(double const y)
{
	m_Y = y;
}



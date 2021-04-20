#include "Arc.h"

TransportMode Arc::getTransportMode() { return t_Mode; }

Node* Arc::getOrigin() {  return n_Origin; }

Node* Arc::getDest() { return n_Dest; }

int* Arc::getLength() { return length; }

void Arc::setOrigin(Node* _n) {  n_Origin = _n; }

void Arc::setDest(Node* _n) {  n_Dest = _n; }

void Arc::setLen(int* _n) {  length = _n; }

void Arc::setTransportMode(TransportMode _t) {  t_Mode = _t; }

Arc::Arc(TransportMode _transport, Node* _Origin, Node* _Destination) {
	setTransportMode(_transport);
	setOrigin(_Origin);
	setDest(_Destination);

	double v0 = (_Origin->GetX() - _Destination->GetX());
	double v1 = pow(v0, 2);
	double v2 = (_Origin->GetY() - _Destination->GetY());
	double v3 = pow(v2, 2);
	double v4 = sqrt(v1 + v3);
	int _n = v4;
	setLen(&_n);
}

Arc::~Arc() {
	
}
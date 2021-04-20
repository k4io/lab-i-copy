#include "Arc.h"

TransportMode Arc::getTransportMode() { return t_Mode; }

Node* Arc::getOrigin() { return n_Origin; }

Node* Arc::getDest() { return n_Dest; }

void Arc::setOrigin(Node* _n) { n_Origin = _n; }

void Arc::setDest(Node* _n) { n_Dest = _n; }

void Arc::setTransportMode(TransportMode _t) { t_Mode = _t; }

Arc::Arc(TransportMode _transport, Node* _Origin, Node* _Destination) {
	setTransportMode(_transport);
	setOrigin(_Origin);
	setDest(_Destination);
}

Arc::~Arc() {

}
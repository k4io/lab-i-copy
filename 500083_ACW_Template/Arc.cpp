#include "Arc.h"

TransportMode Arc::getTransportMode() { return t_Mode; }

Node* Arc::getOrigin() { LOG_ENTRY_EXIT; return n_Origin; }

Node* Arc::getDest() { LOG_ENTRY_EXIT; return n_Dest; }

void Arc::setOrigin(Node* _n) { LOG_ENTRY_EXIT; n_Origin = _n; }

void Arc::setDest(Node* _n) { LOG_ENTRY_EXIT; n_Dest = _n; }

void Arc::setTransportMode(TransportMode _t) { LOG_ENTRY_EXIT; t_Mode = _t; }

Arc::Arc(TransportMode _transport, Node* _Origin, Node* _Destination) {
	LOG_ENTRY_EXIT;
	setTransportMode(_transport);
	setOrigin(_Origin);
	setDest(_Destination);
}

Arc::~Arc() {
	LOG_ENTRY_EXIT;
}
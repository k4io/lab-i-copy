#include "Arc.h"

TransportMode Arc::getTransportMode() { return t_Mode; }

int* Arc::getOrigin() {  return _OriginRef; }

int* Arc::getDest() { return _DestinationRef; }

int Arc::getLength() { return length; }

void Arc::setOrigin(int* _n) { _OriginRef = _n; }

void Arc::setDest(int* _n) { _DestinationRef = _n; }

void Arc::setLen(int* _n) {  length = *_n; }

void Arc::setTransportMode(TransportMode _t) {  t_Mode = _t; }

Arc::Arc(TransportMode _transport, 
	double* _Origin_X,
	double* _Origin_Y,
	double* _Destination_X,
	double* _Destination_Y,
	int* OriginRef, 
	int* DestinationRef
) {
	setTransportMode(_transport);

	this->_Origin_X = _Origin_X;
	this->_Origin_Y = _Origin_Y;
	this->_Destination_X = _Destination_X;
	this->_Destination_Y = _Destination_Y;
	this->_OriginRef = OriginRef;
	this->_DestinationRef = DestinationRef;

	double v0 = (_Origin_X - _Destination_X);
	double v1 = pow(v0, 2);
	double v2 = (_Origin_Y - _Destination_Y);
	double v3 = pow(v2, 2);
	double v4 = sqrt(v1 + v3);
	int _n = v4;



	setLen(&_n);
}

Arc::~Arc() {
	
}
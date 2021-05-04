#include "Arc.h"

Arc& Arc::operator=(const Arc& ul)
{
	this->length = ul.length;
	this->t_Mode = ul.t_Mode;
	this->_DestinationRef = _DestinationRef;
	this->_OriginRef = _OriginRef;
	this->_Destination_X = _Destination_X;
	this->_Destination_Y = _Destination_Y;
	this->_Origin_X = _Origin_X;
	this->_Origin_Y = _Origin_Y;
	return *this;
}

TransportMode Arc::getTransportMode() const { return t_Mode; }

int* Arc::getOrigin() const {  return _OriginRef; }

int* Arc::getDest() const { return _DestinationRef; }

double Arc::getLength() const { return length; }

void Arc::setOrigin(int* const _n) { _OriginRef = _n; }

void Arc::setDest(int* const _n) { _DestinationRef = _n; }

void Arc::setLen(const double* const _n) {  length = *_n; }

void Arc::setTransportMode(const TransportMode const _t) {  t_Mode = _t; }

Arc::Arc(const TransportMode const _transport,
	const double* const n_Origin_X,
	const double* const n_Origin_Y,
	const double* const n_Destination_X,
	const double* const n_Destination_Y,
	const int* const nOriginRef,
	const int* const nDestinationRef
) {
	setTransportMode(_transport);

	this->_Origin_X = const_cast<double*>(n_Origin_X);
	this->_Origin_Y = const_cast<double*>(n_Origin_Y);
	this->_Destination_X = const_cast<double*>(n_Destination_X);
	this->_Destination_Y = const_cast<double*>(n_Destination_Y);
	this->_OriginRef = const_cast<int*>(nOriginRef);
	this->_DestinationRef = const_cast<int*>(nDestinationRef);


	{ //This code determines length via pythagoras 
	  //theorum and square roots the answer for result.
		const double v0 = (*_Destination_X - *_Origin_X);
		const double v1 = v0 * v0;
		const double v2 = (*_Destination_Y - *_Origin_Y);
		const double v3 = v2 * v2;
		const double v4 = v1 + v3;
		const double v5 = sqrt(v4);
		const double _n = (v5 / 1000);
		setLen(&_n);
	}
}

Arc::~Arc() {
	
}
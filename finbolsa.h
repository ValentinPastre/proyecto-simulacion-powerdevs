//CPP:proyecto-simulacion-powerdevs/finbolsa.cpp
#if !defined finbolsa_h
#define finbolsa_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "cmath"


class finbolsa: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;
double total_capacity;
double actual_capacity;
double flowOut;
double outputCount;

double finBolsa;
#ifndef FINBOLSA
	#define FINBOLSA -1.0
#endif
#ifndef INF
	#define INF 10e20
#endif
#ifndef CONFIRMACION_ENFERMERO
	#define CONFIRMACION_ENFERMERO -2.0
#endif
public:
	finbolsa(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif

//CPP:proyecto-simulacion-powerdevs/actuador.cpp
#if !defined actuador_h
#define actuador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class actuador: public Simulator { 
// Declare the state,
// output variables
// and parameters

// caudal siendo inyectado.
double OM;
double cau;
double sigma;

double delay;
double desviation;

#ifndef DETENER
	#define DETENER -3.0
#endif
#ifndef INF
	#define INF 10e20
#endif
public:
	actuador(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif

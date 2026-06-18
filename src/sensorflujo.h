//CPP:proyecto-bomba-infusion/sensorflujo.cpp
#if !defined sensorflujo_h
#define sensorflujo_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class sensorflujo: public Simulator { 
// Declare the state,
// output variables
// and parameters

double sigma;
double cau;
public:
	sensorflujo(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif

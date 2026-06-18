//CPP:proyecto-bomba-infusion/ordenes.cpp
#if !defined ordenes_h
#define ordenes_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "cmath"


class ordenes: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;
double lambda_parameter;
double out;
public:
	ordenes(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif

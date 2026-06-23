//CPP:proyecto-simulacion-powerdevs/controlador.cpp
#if !defined controlador_h
#define controlador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "proyecto-simulacion-powerdevs/constantes.h"


class controlador: public Simulator { 
double OM;
double SFn;
double FB;
double state;
double sigma;

double out;
double outPort;

public:
	controlador(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
	double flowFix(double x);
	double flowCount(double x, double y);
};
#endif

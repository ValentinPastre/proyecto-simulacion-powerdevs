//CPP:proyecto-simulacion-powerdevs/actuador.cpp
#if !defined actuador_h
#define actuador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "proyecto-simulacion-powerdevs/constantes.h"


class actuador: public Simulator { 
double OM;
double cau;
double sigma;

double delay;
double deviation;
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

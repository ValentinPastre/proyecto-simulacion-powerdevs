//CPP:proyecto-bomba-infusion/controlador.cpp
#if !defined controlador_h
#define controlador_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class controlador: public Simulator { 
// Declare the state,
// output variables
// and parameters

double OM;
double SFn;
double FB;
double state;
double sigma;

double out;
double outPort;

//Flags que representan lo siguiente.
#define FINBOLSA -1.0
#ifndef CONFIRMACION_ENFERMERO
	#define CONFIRMACION_ENFERMERO -2.0
#endif
#ifndef DETENER
	#define DETENER -3.0
#endif
#ifndef INF
	#define INF 10e20
#endif
#ifndef ALARMA_BAJA
	#define ALARMA_BAJA -4.0
#endif
#ifndef ALARMA_MEDIA
	#define ALARMA_MEDIA -5.0
#endif
#ifndef ALARMA_CRITICA
	#define ALARMA_CRITICA -6.0
#endif
#define START -7.0
#define RUNNING -8.0
#define STOPPING -9.0
#define STOPPED -10.0
#define NOFINBOLSA -11.0



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

//CPP:proyecto-bomba-infusion/confirmacionenf.cpp
#if !defined confirmacionenf_h
#define confirmacionenf_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class confirmacionenf: public Simulator { 
// Declare the state,
// output variables
// and parameters
double sigma;
double confirmacion;
double useInputs;
int MAX_BOUND;

#ifndef CONFIRMACION_ENFERMERO
	#define CONFIRMACION_ENFERMERO -2.0
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
#ifndef INF
	#define INF 10e20
#endif
public:
	confirmacionenf(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif

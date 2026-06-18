//CPP:proyecto-bomba-infusion/logger.cpp
#if !defined logger_h
#define logger_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class logger: public Simulator { 
double sigma;
FILE *FOutput;
double timeCounter;
public:
	logger(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif

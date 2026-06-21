//CPP:proyecto-simulacion-powerdevs/logger.cpp
#if !defined logger_h
#define logger_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class logger: public Simulator { 
double sigma;
FILE *FOutput;
FILE *FAlarms;
char* FName;
char* FNameAlarms;
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

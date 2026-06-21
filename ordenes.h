// CPP:proyecto-simulacion-powerdevs/ordenes.cpp
#if !defined ordenes_h
#define ordenes_h

#include "event.h"
#include "simulator.h"
#include "stdarg.h"

#include "cmath"

class ordenes : public Simulator {
  double sigma;
  double lambdaParameter;
  double out;

  // parametro para simular el caso de que salga una orden medica con caudal
  // igual a 0
  double totalTime;

public:
  ordenes(const char *n) : Simulator(n) {};
  void init(double, ...);
  double ta(double t);
  void dint(double);
  void dext(Event, double);
  Event lambda(double);
  void exit();
};
#endif

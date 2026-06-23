// CPP:proyecto-simulacion-powerdevs/alarmas.cpp
#if !defined alarmas_h
#define alarmas_h

#include "event.h"
#include "simulator.h"
#include "stdarg.h"

#include "proyecto-simulacion-powerdevs/constantes.h"

class alarmas : public Simulator {
  double sigma;
  double state;
  double criticalRepetitions;

public:
  alarmas(const char *n) : Simulator(n) {};
  void init(double, ...);
  double ta(double t);
  void dint(double);
  void dext(Event, double);
  Event lambda(double);
  void exit();
};
#endif

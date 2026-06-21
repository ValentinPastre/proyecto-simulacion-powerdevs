// CPP:proyecto-simulacion-powerdevs/finbolsa.cpp
#if !defined finbolsa_h
#define finbolsa_h

#include "event.h"
#include "simulator.h"
#include "stdarg.h"

#include "cmath"
#include "proyecto-simulacion-powerdevs/constantes.h"

class finbolsa : public Simulator {
  double sigma;
  double totalCapacity;
  double actualCapacity;
  double flowOut;
  double outputCount;

  double finBolsa;

public:
  finbolsa(const char *n) : Simulator(n) {};
  void init(double, ...);
  double ta(double t);
  void dint(double);
  void dext(Event, double);
  Event lambda(double);
  void exit();
};
#endif

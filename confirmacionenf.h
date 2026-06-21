// CPP:proyecto-simulacion-powerdevs/confirmacionenf.cpp
#if !defined confirmacionenf_h
#define confirmacionenf_h

#include "event.h"
#include "simulator.h"
#include "stdarg.h"

#include "proyecto-simulacion-powerdevs/constantes.h"

class confirmacionenf : public Simulator {
  double sigma;
  double confirmation;

public:
  confirmacionenf(const char *n) : Simulator(n) {};
  void init(double, ...);
  double ta(double t);
  void dint(double);
  void dext(Event, double);
  Event lambda(double);
  void exit();
};
#endif

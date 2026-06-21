#include "finbolsa.h"
void finbolsa::init(double t, ...) {
  va_list parameters;
  va_start(parameters, t);

  sigma = INF;
  finBolsa = FINBOLSA;
  totalCapacity = va_arg(parameters, double);
  actualCapacity = totalCapacity;
  outputCount = 0.0;
}
double finbolsa::ta(double t) { return sigma; }
void finbolsa::dint(double t) {
  if (actualCapacity > 0.0 && actualCapacity <= totalCapacity * 0.1) {
    actualCapacity = actualCapacity - (flowOut / 3600.0);
    sigma = 1.0;
    outputCount = 1.0;
  } else if (actualCapacity > 0.0) {
    actualCapacity = actualCapacity - (flowOut / 3600.0);
    sigma = 1.0;
  } else {
    sigma = INF;
  }
}
void finbolsa::dext(Event x, double t) {
  double xv = *(double *)x.value;
  double port = x.port;

  if (xv > 0.0 && port == 0.0) {
    flowOut = xv;
    sigma = 0.0;
  } else if (xv <= 0 && port == 0.0) {
    flowOut = xv;
    sigma = INF;
  } else if (xv == CONFIRMACION_ENFERMERO && port == 1.0 &&
             actualCapacity <= totalCapacity * 0.1) {
    outputCount = 0.0;
    actualCapacity = totalCapacity;
    sigma = 0.0;
  }
}
Event finbolsa::lambda(double t) {
  if (actualCapacity <= totalCapacity * 0.1 && outputCount == 0.0) {
    return Event(&finBolsa, 0);
  } else {
    return Event();
  }
}
void finbolsa::exit() {}

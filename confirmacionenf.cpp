#include "confirmacionenf.h"
void confirmacionenf::init(double t, ...) {
  va_list parameters;
  va_start(parameters, t);

  sigma = INF;
  confirmation = CONFIRMACION_ENFERMERO;
}
double confirmacionenf::ta(double t) { return sigma; }
void confirmacionenf::dint(double t) { sigma = INF; }
void confirmacionenf::dext(Event x, double t) {
  double xv = *(double *)x.value;

  if (xv == ALARMA_BAJA) {
    sigma = (double)(61 + (double)(rand() % 300));
  } else if (xv == ALARMA_CRITICA) {
    sigma = (double)(1 + (double)(rand() % 120));
  } else {
    sigma = sigma - e;
  }
}
Event confirmacionenf::lambda(double t) { return Event(&confirmation, 0); }
void confirmacionenf::exit() {}

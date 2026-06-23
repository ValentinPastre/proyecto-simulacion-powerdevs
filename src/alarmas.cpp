#include "alarmas.h"
void alarmas::init(double t, ...) {
  va_list parameters;
  va_start(parameters, t);

  sigma = INF;
  state = CONFIRMED;
  criticalRepetitions = 0.0;
}
double alarmas::ta(double t) { return sigma; }
void alarmas::dint(double t) {
  if (state == ALARMA_MEDIA) {
    state = ALARMA_MEDIA;
    sigma = INF;
  } else if (state == ALARMA_CRITICA && criticalRepetitions == 0.0) {
    state = ALARMA_CRITICA;
    criticalRepetitions += 1.0;
    sigma = 30.0;
  } else if (state == ALARMA_CRITICA && criticalRepetitions != 0.0) {
    state = ALARMA_CRITICA;
    criticalRepetitions += 1.0;
    sigma = 10.0;
  } else if (state == ALARMA_BAJA) {
    state = ALARMA_BAJA;
    sigma = INF;
  }
}
void alarmas::dext(Event x, double t) {
  double xv = *(double *)x.value;
  double port = x.port;

  if (xv == ALARMA_MEDIA && port == 0.0) {
    state = ALARMA_MEDIA;
    sigma = 0.0;
  } else if (xv == ALARMA_CRITICA && port == 0.0) {
    state = ALARMA_CRITICA;
    criticalRepetitions = 0.0;
    sigma = 0.0;
  } else if (xv == ALARMA_BAJA && port == 0.0) {
    state = ALARMA_BAJA;
    sigma = 0;
  } else if ((xv == CONFIRMACION_ENFERMERO && port == 1.0) ||
             (xv > 0.0 && port == 2.0)) {
    state = CONFIRMED;
    sigma = INF;
  }
}
Event alarmas::lambda(double t) { return Event(&state, 0); }
void alarmas::exit() {}

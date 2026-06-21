#include "ordenes.h"
#include "constantes.h"
void ordenes::init(double t, ...) {
  va_list parameters;
  va_start(parameters, t);
  srand(genSeed);

  sigma = 0;
  lambdaParameter = va_arg(parameters, double);
  totalTime = 0.0;
}
double ordenes::ta(double t) { return sigma; }
void ordenes::dint(double t) {
  sigma =
      -log(((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) / lambdaParameter;
}
void ordenes::dext(Event x, double t) {}
Event ordenes::lambda(double t) {
  // totalTime += e;

  // if (totalTime < 10000) {
  out = (double)(rand() % 200);
  /*
  } else {
          out = 0.0;
  }
  */
  return Event(&out, 0);
}
void ordenes::exit() {}

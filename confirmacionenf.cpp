#include "confirmacionenf.h"
void confirmacionenf::init(double t,...) {
va_list parameters;
va_start(parameters,t);

sigma = INF;
confirmacion = CONFIRMACION_ENFERMERO;
useInputs = va_arg(parameters, double);
MAX_BOUND = (int) va_arg(parameters, double);
}
double confirmacionenf::ta(double t) {
return sigma;
}
void confirmacionenf::dint(double t) {
if (useInputs == 0.0) {
	sigma = (double) (1 + (double)(rand() % MAX_BOUND));
} else if (useInputs == 1.0) {
	sigma = INF;
} else {
	sigma = sigma - e;
}
}
void confirmacionenf::dext(Event x, double t) {
double xv = *(double*) x.value;

if (useInputs == 1.0 && xv == ALARMA_BAJA) {
	sigma = (double) (61 + (double)(rand() % 300));
} else if (useInputs == 1.0 && xv == ALARMA_CRITICA) {
	sigma = (double) (1 + (double)(rand() % 120));
} else {
	sigma = sigma - e;
}
}
Event confirmacionenf::lambda(double t) {
// double* confirmacionEnfermero = new double();
// *confirmacionEnfermero = CONFIRMACION_ENFERMERO;

return Event(&confirmacion, 0);
}
void confirmacionenf::exit() {
//Code executed at the end of the simulation.

}

#include "actuador.h"
void actuador::init(double t,...) {
va_list parameters;
va_start(parameters,t);

cau = 0;
sigma = INF;
delay = va_arg(parameters, double);
// DETENER = va_arg(parameters, double);
}
double actuador::ta(double t) {
return sigma;
}
void actuador::dint(double t) {
sigma = INF;
}
void actuador::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

double xv = *(double*)x.value;

double min = (xv - (xv * 0.12));
double max = (xv + (xv * 0.12));

if (xv != DETENER) {
	cau = min + ((((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) * (max - min));
} else {
	cau = 0;
}

sigma = (((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) * delay;
}
Event actuador::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

return Event(&cau, 0);
}
void actuador::exit() {
//Code executed at the end of the simulation.

}

#include "actuador.h"
void actuador::init(double t,...) {
va_list parameters;
va_start(parameters,t);

OM = 0.0;
cau = 0.0;
sigma = INF;
delay = va_arg(parameters, double);
deviation = va_arg(parameters, double);
}
double actuador::ta(double t) {
return sigma;
}
void actuador::dint(double t) {
if (cau != 0.0) {
	double min = (OM - (OM * deviation));
	double max = (OM + (OM * deviation));
	cau = min + ((((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) * (max - min));
	sigma = 1 + (double)(rand() % 600);
} else {
	sigma = INF;
}
}
void actuador::dext(Event x, double t) {
double xv = *(double*)x.value;

double min = (xv - (xv * deviation));
double max = (xv + (xv * deviation));

if (xv != DETENER) {
	OM = xv;
	cau = min + ((((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) * (max - min));
} else {
	OM = 0.0;
	cau = 0.0;
}

sigma = (((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) * delay;
}
Event actuador::lambda(double t) {
return Event(&cau, 0);
}
void actuador::exit() {


}

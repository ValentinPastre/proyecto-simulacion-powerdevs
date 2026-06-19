#include "finbolsa.h"
void finbolsa::init(double t,...) {
va_list parameters;
va_start(parameters,t);

sigma = INF;
finBolsa = FINBOLSA;
total_capacity = va_arg(parameters, double);
actual_capacity = total_capacity;
outputCount = 0.0;
}
double finbolsa::ta(double t) {
return sigma;
}
void finbolsa::dint(double t) {
if (actual_capacity > 0.0 && actual_capacity <= total_capacity * 0.1) {
	actual_capacity = actual_capacity - (flowOut/3600.0);
	sigma = 1.0;
	outputCount = 1.0;
}else if (actual_capacity > 0.0) {
	actual_capacity = actual_capacity - (flowOut/3600.0);
	sigma = 1.0;
}else {
	sigma = INF;
}

}
void finbolsa::dext(Event x, double t) {
double xv = *(double*) x.value;
double port = x.port;

if (xv > 0.0 && port == 0.0) {
	flowOut = xv;
	sigma = 0.0;
} else if (xv <= 0 && port == 0.0) {
	flowOut = xv;
	sigma = INF;
} else if (xv == CONFIRMACION_ENFERMERO && port == 1.0 
					&& actual_capacity <= total_capacity * 0.1) {
	outputCount = 0.0;
	actual_capacity = total_capacity;
	sigma = 0.0;
}
}
Event finbolsa::lambda(double t) {
if (actual_capacity <= total_capacity * 0.1 && outputCount == 0.0) {
	return Event(&finBolsa,0);
} else {
	return Event();
}
}
void finbolsa::exit() {

}

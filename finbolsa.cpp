#include "finbolsa.h"
void finbolsa::init(double t,...) {
va_list parameters;
va_start(parameters,t);

sigma = INF;
finBolsa = FINBOLSA;
total_capacity = va_arg(parameters, double);
actual_capacity = total_capacity;
}
double finbolsa::ta(double t) {
return sigma;
}
void finbolsa::dint(double t) {
if (actual_capacity > 0) {
	actual_capacity = actual_capacity - (flowOut/3600.0);
	sigma = 1;
} else {
	sigma = INF;
}

}
void finbolsa::dext(Event x, double t) {
double xv = *(double*) x.value;

if (xv > 0) {
	flowOut = xv;
} else {
	flowOut = xv;
	sigma = INF;
}
}
Event finbolsa::lambda(double t) {
if (actual_capacity <= total_capacity * 0.1) {
	return Event(&finBolsa,0);
} else {
	return Event();
}
}
void finbolsa::exit() {

}

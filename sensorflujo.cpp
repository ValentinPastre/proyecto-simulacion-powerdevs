#include "sensorflujo.h"
void sensorflujo::init(double t,...) {
va_list parameters;
va_start(parameters,t);

sigma = 1.0;
cau = 0.0;
}
double sensorflujo::ta(double t) {
return sigma;
}
void sensorflujo::dint(double t) {
sigma = 1.0;
}
void sensorflujo::dext(Event x, double t) {
double xv = *(double*) x.value;

if (xv != cau) {
	cau = xv;
	sigma = sigma - e;
}
}
Event sensorflujo::lambda(double t) {
return Event(&cau, 0);
}
void sensorflujo::exit() {

}

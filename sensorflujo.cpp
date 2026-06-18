#include "sensorflujo.h"
void sensorflujo::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

sigma = 1.0;
cau = 0.0;
}
double sensorflujo::ta(double t) {
//This function returns a double.
return sigma;
}
void sensorflujo::dint(double t) {
sigma = 1.0;
}
void sensorflujo::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

double xv = *(double*) x.value;

if (xv != cau) {
	cau = xv;
	sigma = sigma - e;
}
}
Event sensorflujo::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


return Event(&cau, 0);
}
void sensorflujo::exit() {
//Code executed at the end of the simulation.

}

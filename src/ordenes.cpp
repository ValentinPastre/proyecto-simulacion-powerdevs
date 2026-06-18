#include "ordenes.h"
void ordenes::init(double t,...) {
va_list parameters;
va_start(parameters,t);

sigma = 0;
lambda_parameter = va_arg(parameters, double);

}
double ordenes::ta(double t) {
//This function returns a double.
return sigma;
}
void ordenes::dint(double t) {
sigma=-log(((double)rand() + 1.0) / ((double)RAND_MAX + 1.0)) / lambda_parameter;
//sigma=(double)(rand() % 3600);
}
void ordenes::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

}
Event ordenes::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

// double* out = new double();
// *out = (double)(rand() % 200);
out = (double)(rand() % 200);
return Event(&out, 0);
}
void ordenes::exit() {
//Code executed at the end of the simulation.

}

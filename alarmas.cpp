#include "alarmas.h"
void alarmas::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
sigma = INF;
state = CONFIRMED;
critical_repetitions = 0.0;
}
double alarmas::ta(double t) {
//This function returns a double.
return sigma;
}
void alarmas::dint(double t) {
if (state == ALARMA_MEDIA) {
	state = ALARMA_MEDIA;
	sigma = INF;
} else if (state == ALARMA_CRITICA && critical_repetitions == 0.0) {
	state = ALARMA_CRITICA;
	critical_repetitions += 1.0;
	sigma = 30.0;
} else if (state == ALARMA_CRITICA && critical_repetitions != 0.0) {
	state = ALARMA_CRITICA;
	critical_repetitions += 1.0;
	sigma = 10.0;
} else if (state == ALARMA_BAJA) {
	state = ALARMA_BAJA;
	sigma = INF;
}
}
void alarmas::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

double xv = *(double*) x.value;
double port = x.port;

if (xv == ALARMA_MEDIA && port == 0.0) {
	state = ALARMA_MEDIA;
	sigma = 0.0;
} else if (xv == ALARMA_CRITICA && port == 0.0) {
	state = ALARMA_CRITICA;
	critical_repetitions = 0.0;
	sigma = 0.0;
} else if (xv == ALARMA_BAJA && port == 0.0) {
	state = ALARMA_BAJA;
	sigma = 0;
} else if (xv == CONFIRMACION_ENFERMERO && port == 1.0
	|| xv != 0 && port == 2.0) {
	state = CONFIRMED;
	critical_repetitions = 0.0;
	sigma = INF;
}
}
Event alarmas::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


return Event(&state, 0);
}
void alarmas::exit() {
//Code executed at the end of the simulation.

}

#include "controlador.h"
void controlador::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

OM = 0.0;
SFn = 0.0;
FB = NOFINBOLSA;
state = STOPPED;
sigma = INF;
}
double controlador::ta(double t) {
//This function returns a double.
return sigma;
}
void controlador::dint(double t) {
if (state == STOPPING && (SFn >= 20.0 || FB == FINBOLSA || OM == 0.0)) {
	SFn = 0.0;
	state = STOPPED;
	sigma = INF;
} else if (SFn >= 20.0 && state != STOPPING) {
	state = STOPPING;
	sigma = 0.0;
} else if (state == RUNNING && FB == FINBOLSA) {
	SFn = 0.0;
	state = STOPPING;
	sigma = (double)(rand() % 60);
} else if (SFn > 5.0) {
	// SFn = controlador::flowFix(SFn);
	sigma = 20.0;
} else if (state == START) {
	state = RUNNING;
	sigma = 0.0;
} else if (state == RUNNING) {
	state = RUNNING;
	sigma = INF;
}
}
void controlador::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

double xv = *(double*) x.value; double port = x.port;

if (xv > 0.0 && port == 0.0 && state == STOPPED) {
	OM = xv;
	state = START;
	sigma = (double)(rand() % 3);
} else if (xv > 0.0 && port == 0.0 && state == RUNNING) {
	OM = xv;
	sigma = (double)(rand() % 3);
} else if (xv == 0.0 && port == 0.0 && state == RUNNING) {
	OM = 0.0;
	state = STOPPING;
	sigma = (double)(rand() % 3);
} else if (port == 1.0 && SFn >= 6.0 && SFn < 7.0) { // Hago este intervalo por si hay algun error de redondeo con los doubles.
	SFn = controlador::flowCount(SFn, xv);
	sigma = 0.0;
} else if (port == 1.0 && state != STOPPED) {
	SFn = controlador::flowCount(SFn, xv);
	sigma = sigma - e;
} else if (port == 2.0 && state == RUNNING && SFn <= 5.0) {
	FB = FINBOLSA;
	sigma = 0.0;
} else if (port == 3.0 && state == STOPPED && OM != 0.0) {
	SFn = 0.0;
	FB = NOFINBOLSA;
	state = START;
	sigma = (double)(rand() % 3);
}
}
Event controlador::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

if (state == RUNNING && FB == FINBOLSA) {
	out = ALARMA_BAJA;
	outPort = 1;
} else if (SFn > 5.0 && SFn < 15.0 && state == RUNNING) {
	out = ALARMA_MEDIA;
	outPort = 1;
} else if (SFn >= 20.0 && state == STOPPING) {
	out = ALARMA_CRITICA;
	outPort = 1;
} else if (state == STOPPING) {
	out = DETENER;
	outPort = 0;
} else if (state == RUNNING) {
	out = OM;
	outPort = 0;
}

return Event(&out, outPort);
}
void controlador::exit() {
//Code executed at the end of the simulation.

/*
double controlador::flowFix(double x) {
	if (rand() <= 0.75) {
		return 0;
	} else {
		return x;
	}
}

double controlador::flowCount(double x, double y) {
	if ((y >= OM + (OM * 0.1)) || (y <= OM - (OM * 0.1))) {
		x += 1;
		return x;
	} else {
		return 0;
	}
}
*/
}

double controlador::flowFix(double x) {
	if (rand() <= 0.75) {
		return 0;
	} else {
		return x;
	}
}

double controlador::flowCount(double x, double y) {
	if ((y >= OM + (OM * 0.1)) || (y <= OM - (OM * 0.1))) {
		x += 1;
		return x;
	} else {
		return 0;
	}
}

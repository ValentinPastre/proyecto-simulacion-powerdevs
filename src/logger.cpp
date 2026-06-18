#include "logger.h"
void logger::init(double t,...) {
va_list parameters;
va_start(parameters,t);

char* FName;
FName = va_arg(parameters, char*);

sigma = 10e20;
FOutput = fopen(FName, "w");
if (FOutput != NULL) {
	fprintf(FOutput, "Time,Signal_Type,Value\n");
	fclose(FOutput);
}
FOutput = fopen(FName, "a");

timeCounter = 0.0;
}
double logger::ta(double t) {
return sigma;
}
void logger::dint(double t) {
sigma = 10e20;
}
void logger::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

double xv = *(double*) x.value;
double port = x.port;

timeCounter = timeCounter + e;

if (FOutput != NULL) {
	if (port == 0.0) {
		fprintf(FOutput, "%g,ORDEN_MEDICA,%g\n", timeCounter, xv);
	} else if (port == 1.0) {
		fprintf(FOutput, "%g,CAUDAL_ACTUADOR,%g\n", timeCounter, xv);
	} else if (port == 2.0) {
		fprintf(FOutput, "%g,CAUDAL_SENSOR,%g\n", timeCounter, xv);
	} else if (port == 3.0) {
		fprintf(FOutput, "%g,FIN_BOLSA,%g\n", timeCounter, xv);
	} else if (port == 4.0) {
		fprintf(FOutput, "%g,CONFIRMACION_ENFERMERO,%g\n", timeCounter, xv);
	} else if (port == 5.0) {
			if (xv == -4.0) {
				fprintf(FOutput, "%g,ALARMA_BAJA,%g\n", timeCounter, xv);
			} else if (xv == -5.0) {
				fprintf(FOutput, "%g,ALARMA_MEDIA,%g\n", timeCounter, xv);
			} else if (xv == -6.0) {
				fprintf(FOutput, "%g,ALARMA_CRITICA,%g\n", timeCounter, xv);
			}
	}
}
}
Event logger::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


return Event();
}
void logger::exit() {
if (FOutput != NULL) {
	fclose(FOutput);
}
}

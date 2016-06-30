#pragma once
#include "Red.h"
class BackPropagation
{
public:
	Red *mired;
	double ratio_aprenidzaje = 0.1;
	double momentum = 0.0;

	double **neuroerrores = NULL;
	double ***actualizacion_pesos = NULL;
	double **actualizacion_threshold = NULL;

	BackPropagation(Red &red);
	double Entrenar(double **entrada, double**salida,int cuantasvueltas);
	double Correr(double *entrada, double *salida);
	double Calcular_error(double* salidadeseada);
	void Calcular_actualizacion(double* entrada);
	void Actualizar_Red();
	~BackPropagation();
};


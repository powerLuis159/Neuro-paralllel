#pragma once
#include "Capa.h"
class Red
{
public:
	double *salida;
	int contador_entradas;
	int contador_capas;
	std::list<Capa> capas;
	Red(int,int,int*);
	double* computar(double *entrada);
	~Red();
};


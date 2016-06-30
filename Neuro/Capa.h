#pragma once
#include "stdafx.h"
#include "Neurona.h"
class Capa
{
public:
	std::list<Neurona> neuronas;
	int contador_neuronas;
	int contador_entradas;
	double* computar(double * entrada);
	Capa(int cn, int ce);
	~Capa();
};


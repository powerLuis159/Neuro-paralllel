#pragma once
#include <math.h>
class Neurona
{
	
	
public:
	int tamaño_entradas;
	double salida;
	double threshold=0.0;
	double alpha;
	double* pesos;
	double func(double x);
	double computar(double* entrada);
	void aleatorios();
	Neurona(int);
	~Neurona();
};


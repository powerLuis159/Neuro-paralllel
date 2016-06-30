#include "stdafx.h"
#include "Neurona.h"


double Neurona::func(double x)
{
	return (1/(1+exp(-alpha*x)));
}

double Neurona::computar(double * entrada)
{
	double sum = 0.0;
	for(int i=0; i<tamaño_entradas;i++)
	{
		sum += entrada[i] * pesos[i];
	}
	sum += threshold;
	salida = func(sum);
	
	return salida;
}

void Neurona::aleatorios()
{
	for (int i = 0; i < tamaño_entradas;i++)
	{
		pesos[i] = (double)(rand() % 1000) / 1000;
	}
	threshold = (double)(rand() % 1000) / 1000;
}

Neurona::Neurona(int entradas)
{
	tamaño_entradas = entradas;
	pesos = new double[entradas];
	aleatorios();
}


Neurona::~Neurona()
{
}

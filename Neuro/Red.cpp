#include "stdafx.h"
#include "Red.h"


Red::Red(int contadorentradas,int contadorcapas,int *contadorneuronas)
{
	contador_entradas = contadorentradas;
	contador_capas = contadorcapas;
	capas.push_back(Capa(contadorneuronas[0], contadorentradas));
	for (int i = 1;i < contadorcapas;i++)
	{
		capas.push_back(Capa(contadorneuronas[i], contadorneuronas[i-1]));
	}
}

double* Red::computar(double *entrada)
{
	salida = entrada;
	std::list<Capa>::iterator it;
	it = capas.begin();
	for (int i = 0;i < contador_capas;i++)
	{
		salida = it->computar(salida);
		it++;
	}
	return salida;
}


Red::~Red()
{
}

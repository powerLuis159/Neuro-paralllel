#include "stdafx.h"
#include "Capa.h"


double * Capa::computar(double * entrada)
{
	double *salida = entrada;
	std::list<Neurona>::iterator it;
	it = neuronas.begin();
	for (int i = 0;i < contador_neuronas;i++)
	{
		salida[i] = it->computar(salida);
		it++;
	}
	return salida;
}

Capa::Capa(int contadornueronas,int contadorentradas)
{
	contador_entradas = contadorentradas;
	contador_neuronas = contadornueronas;
	for (int i = 0;i < contadornueronas;i++)
	{
		neuronas.push_back(Neurona(contadorentradas));
	}
}


Capa::~Capa()
{
}

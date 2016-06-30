#include "stdafx.h"
#include "BackPropagation.h"


BackPropagation::BackPropagation(Red &red)
{
	mired = &red;
	neuroerrores = new double*[red.contador_capas];
	actualizacion_pesos = new double**[red.contador_capas];
	actualizacion_threshold = new double*[red.contador_capas];
	std::list<Capa>::iterator itc;
	itc = red.capas.begin();
	for (int i = 0; i < red.contador_capas;i++)
	{
		neuroerrores[i] = new double[itc->contador_neuronas];
		actualizacion_pesos[i] = new double*[itc->contador_neuronas];
		actualizacion_threshold[i] = new double[itc->contador_neuronas];

		//para cada neurona
		for (int j = 0;j < itc->contador_neuronas;j++)
		{
			actualizacion_pesos[i][j] = new double[itc->contador_entradas];
		}
		itc++;
	}
}

double BackPropagation::Entrenar(double ** entrada, double ** salida, int cuantasvueltas)
{
	double error = 0.0;
#pragma omp parallel for
	for (int i = 0;i < cuantasvueltas;i++)
	{
		error += Correr(entrada[i], salida[i]);
	}
	return error;
}

double BackPropagation::Correr(double * entrada, double * salida)
{
	mired->computar(entrada);
	//calcular error
	double error = Calcular_error(salida);
	//calcular pesos a actualizar
	Calcular_actualizacion(entrada);
	//actualizar red
	Actualizar_Red();

	return error;
}

double BackPropagation::Calcular_error(double * salidadeseada)
{
	std::list<Capa>::iterator itcapa, itcapasiguiente;
	double *errores, *errorsiguiente;
	double error=0,e,sum;
	double salida;
	int contador_capas = mired->contador_capas;
	/*
	itcapa = mired->capas.begin();
	for(int im=0;im<contador_capas-1;im++)
	{
		itcapa++;
	}*/
	itcapa = mired->capas.end();
	itcapa--;
	errores = neuroerrores[contador_capas - 1];

	std::list<Neurona>::iterator itneurona,itneurona2;
	itneurona = itcapa->neuronas.begin();
	for (int i = 0;i < itcapa->contador_neuronas;i++)
	{
		salida = itneurona->salida;
		e = salidadeseada[i] - salida;
		errores[i] = e*2*salida*(1-salida);//funcion derivada derivada de sigmoind
		error += (e*e);
	}

	//calculo de errores para las otras capas
	for (int j = contador_capas - 2;j >= 0;j--)
	{
		itcapasiguiente = itcapa;
		itcapa--;
		errores = neuroerrores[j];
		errorsiguiente = neuroerrores[j + 1];
		//para todas las neuronas en la capa
		itneurona = itcapa->neuronas.begin();
		for (int i = 0; i < itcapa->contador_neuronas;i++)
		{
			sum = 0.0;
			//para todas las neuronas en la siguiente capa
			itneurona2 = itcapasiguiente->neuronas.begin();
			for (int k = 0;k < itcapasiguiente->contador_neuronas;k++)
			{
				sum += errorsiguiente[k] * itneurona2->pesos[k];
				itneurona2++;
			}
			errores[i] = sum * 2 * itneurona->salida*(1 - itneurona->salida);
			itneurona++;
		}
	}
	return error/2;
}

void BackPropagation::Calcular_actualizacion(double * entrada)
{
	std::list<Neurona>::iterator itneurona,itneurona2;
	std::list<Capa>::iterator itcapa, itcapaprevia;
	double **actualizacion_pesos_capa;
	double *actualizacion_threshold_capa;
	double *errores;
	double *actualizacion_pesos_neurona;

	//1.- calcular actualizaciones para la primera capa
	itcapa = mired->capas.begin();
	errores = neuroerrores[0];
	actualizacion_pesos_capa = actualizacion_pesos[0];
	actualizacion_threshold_capa = actualizacion_threshold[0];

	//cache
	double cachedmomentum = ratio_aprenidzaje*momentum;
	double cached1mmomentum = ratio_aprenidzaje*(1 - momentum);
	double cachedError;

	//para cada Neurona de la capa
	itneurona = itcapa->neuronas.begin();
	for (int i = 0;i < itcapa->contador_neuronas;i++)
	{
		cachedError = errores[i] * cached1mmomentum;
		actualizacion_pesos_neurona = actualizacion_pesos_capa[i];

		
		//para cada peso de la neurona
		for (int j = 0;j < itneurona->tamaño_entradas;j++)
		{
			actualizacion_pesos_neurona[j] = cachedmomentum*actualizacion_pesos_neurona[j] + cachedError*entrada[j];
		}

		//Calculo del threshold
		actualizacion_threshold_capa[i] = cachedmomentum*actualizacion_threshold_capa[i] + cachedError;
	}

	//2.- para las demas capas
	for (int k = 1;k < mired->contador_capas;k++)
	{
		itcapaprevia = itcapa;
		itcapa++;
		errores = neuroerrores[k];
		actualizacion_pesos_capa = actualizacion_pesos[k];
		actualizacion_threshold_capa = actualizacion_threshold[k];

		cachedError = errores[k] * cached1mmomentum;
		actualizacion_pesos_neurona = actualizacion_pesos_capa[k];

		itneurona = itcapa->neuronas.begin();
		for (int i = 0;i < itcapa->contador_neuronas;i++)
		{
			cachedError = errores[i] * cached1mmomentum;
			actualizacion_pesos_neurona = actualizacion_pesos_capa[i];

			//Para cada sinapsis
			itneurona2 = itcapaprevia->neuronas.begin();
			for (int j = 0;j < itneurona->tamaño_entradas;j++)
			{
				actualizacion_pesos_neurona[j] = cachedmomentum*actualizacion_pesos_neurona[j] + cachedError*itneurona2->salida;
				itneurona2++;
			}
			//calcular el threshold
			actualizacion_threshold_capa[i] = cachedmomentum*actualizacion_threshold_capa[i] + cachedError;
			itneurona++;
		}
	}
}

void BackPropagation::Actualizar_Red()
{
	std::list<Neurona>::iterator itNeurona;
	std::list<Capa>::iterator itCapa;
	double** actualizacion_peso_capa;
	double* actualizacion_threshold_capa;
	double* actualizacion_peso_neurona;

	//Para cada capa de la red
	itCapa = mired->capas.begin();
	for (int i = 0;i < mired->contador_capas;i++)
	{
		actualizacion_peso_capa = actualizacion_pesos[i];
		actualizacion_threshold_capa = actualizacion_threshold[i];
		//Para cada neurona en la capa
		itNeurona = itCapa->neuronas.begin();
		for (int j = 0; j < itCapa->contador_neuronas;j++)
		{
			actualizacion_peso_neurona = actualizacion_peso_capa[j];
			//Para cada peso en la neurona
			for (int k = 0;k < itNeurona->tamaño_entradas;k++)
			{
#pragma omp atomic
				itNeurona->pesos[k] += actualizacion_peso_neurona[k];
			}
			//actualizar el threshold
#pragma omp atomic
			itNeurona->threshold += actualizacion_threshold_capa[j];
			itNeurona++;
		}
		itCapa++;
	}
}

BackPropagation::~BackPropagation()
{
}

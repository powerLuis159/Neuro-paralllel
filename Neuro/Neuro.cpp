// Neuro.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "Lector.h"
#include "Red.h"
#include "BackPropagation.h"
int main()
{
	int *a = new int[3];
	a[0] = 100;
	a[1] = 50;
	a[2] = 10;
	Red mired(784, 3, a);

	




	BackPropagation entrenador(mired);
	Lector L;
	L.Entrenar(entrenador);
	L.Probar(entrenador);

    return 0;
}


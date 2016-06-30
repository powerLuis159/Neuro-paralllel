#include "stdafx.h"
#include "Lector.h"




void Lector::Entrenar(BackPropagation &entrenador)
{
	char magicnumber[4];//2051
	char magicnumber2[4];
	char number_images[4];//60000
	char number_labels[4];
	char number_of_rows[4];//28
	char number_of_columns[4];//28

	double **entrada,**salida;
	entrada = new double*[60000];
	salida = new double*[60000];

	std::fstream archivo;
	std::fstream etiquetas;
	etiquetas.open("C:\\Users\\user\\Downloads\\Data set\\train-labels.idx1-ubyte");
	archivo.open("C:\\Users\\user\\Downloads\\Data set\\train-images.idx3-ubyte");

	archivo.get(magicnumber[0]);
	archivo.get(magicnumber[1]);
	archivo.get(magicnumber[2]);
	archivo.get(magicnumber[3]);

	archivo.get(number_images[0]);
	archivo.get(number_images[1]);
	archivo.get(number_images[2]);
	archivo.get(number_images[3]);

	archivo.get(number_of_rows[0]);
	archivo.get(number_of_rows[1]);
	archivo.get(number_of_rows[2]);
	archivo.get(number_of_rows[3]);

	archivo.get(number_of_columns[0]);
	archivo.get(number_of_columns[1]);
	archivo.get(number_of_columns[2]);
	archivo.get(number_of_columns[3]);

	etiquetas.get(magicnumber2[0]);
	etiquetas.get(magicnumber2[1]);
	etiquetas.get(magicnumber2[2]);
	etiquetas.get(magicnumber2[3]);

	etiquetas.get(number_labels[0]);
	etiquetas.get(number_labels[1]);
	etiquetas.get(number_labels[2]);
	etiquetas.get(number_labels[3]);
	
	
	char temp;
	for (int i = 0;i < 6000;i++)
	{
		double etiqueta[10];
		double imagen[28 * 28];
		
		
		for (int j = 0;j < 10;j++)
		{
			etiqueta[j] = 0.0;
		}
		etiquetas.get(temp);
		etiqueta[temp] = 1.0;

		for (int j = 0;j < 784;j++)
		{
			archivo.get(temp);
			if (temp > 128)
				imagen[j] = 1.0;
			else
				imagen[j] = 0.0;
		}

		entrada[i] = imagen;
		salida[i] = etiqueta;
	}

	entrenador.Entrenar(entrada, salida, 1000);//tiempo procesamiento 1min/1000 datos.
}

void Lector::Probar(BackPropagation &entrenador)
{
	char magicnumber[4];//2051
	char magicnumber2[4];
	char number_images[4];//10000
	char number_labels[4];
	char number_of_rows[4];//28
	char number_of_columns[4];//28

	double **entrada, **salida;
	entrada = new double*[60000];
	salida = new double*[60000];

	std::fstream archivo;
	std::fstream etiquetas;
	etiquetas.open("C:\\Users\\user\\Downloads\\Data set\\t10k-labels.idx1-ubyte");
	archivo.open("C:\\Users\\user\\Downloads\\Data set\\t10k-images.idx3-ubyte");

	archivo.get(magicnumber[0]);
	archivo.get(magicnumber[1]);
	archivo.get(magicnumber[2]);
	archivo.get(magicnumber[3]);

	archivo.get(number_images[0]);
	archivo.get(number_images[1]);
	archivo.get(number_images[2]);
	archivo.get(number_images[3]);

	archivo.get(number_of_rows[0]);
	archivo.get(number_of_rows[1]);
	archivo.get(number_of_rows[2]);
	archivo.get(number_of_rows[3]);

	archivo.get(number_of_columns[0]);
	archivo.get(number_of_columns[1]);
	archivo.get(number_of_columns[2]);
	archivo.get(number_of_columns[3]);

	etiquetas.get(magicnumber2[0]);
	etiquetas.get(magicnumber2[1]);
	etiquetas.get(magicnumber2[2]);
	etiquetas.get(magicnumber2[3]);

	etiquetas.get(number_labels[0]);
	etiquetas.get(number_labels[1]);
	etiquetas.get(number_labels[2]);
	etiquetas.get(number_labels[3]);


	char temp;
	for (int i = 0;i < 1000;i++)
	{
		double etiqueta[10];
		double imagen[28 * 28];


		for (int j = 0;j < 10;j++)
		{
			etiqueta[j] = 0.0;
		}
		etiquetas.get(temp);
		etiqueta[temp] = 1.0;

		for (int j = 0;j < 784;j++)
		{
			archivo.get(temp);
			if (temp > 128)
				imagen[j] = 1.0;
			else
				imagen[j] = 0.0;
		}

		entrada[i] = imagen;
		salida[i] = etiqueta;
	}
	int counter=0;
	double *a, *b;
	
	for (int i = 0;i < 100;i++)
	{
		a = entrenador.mired->computar(entrada[i]);
		b = salida[i];
		for (int comp = 0;comp < 10;comp++)
		{
			if (a[comp] != b[comp])
			{
				counter++;
			}
		}
	}
	double error = counter / 100;
}

Lector::Lector()
{
}


Lector::~Lector()
{
}

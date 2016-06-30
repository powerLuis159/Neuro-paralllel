#pragma once
#include "stdafx.h"
#include <fstream>
#include <string>
#include "BackPropagation.h"
class Lector
{
public:
	void Entrenar(BackPropagation &);
	void Probar(BackPropagation &);
	Lector();
	~Lector();
};


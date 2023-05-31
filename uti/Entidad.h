#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
class Entidad
{
protected:
	int vida;
	int vidaMax;
	int ataque;
	int puntos;
	float velocidad;
	bool spriteInvertido;
public:
	//virtual ~Entidad();
	//void setPosicion(const float x, const float y);
};


#include "Enemigo.h"

void Enemigo::initVariables(int tipo)
{
	this->tipo = tipo;
	
	switch (tipo)
	{
	case 1:
		vidaMax = 30;
		vida = vidaMax;
		ataque = 10;
		puntos = 10;
		velocidad = 0.1f;
		break;
	case 2:
		vidaMax = 100;
		vida = vidaMax;
		ataque = 20;
		puntos = 20;
		velocidad = 0.2f;
	case 3:
		vidaMax = 200;
		vida = vidaMax;
		ataque = 30;
		puntos = 30;
		velocidad = 0.3f;
		break;
	default:
		std::cout << "Error: No se ha podido inicializar las variables de la clase Enemigo\n";
		break;
	}
}

void Enemigo::initTexture(int tipo)
{
	switch (tipo)
	{
	case 1:
		if (!textura.loadFromFile("recursos/imagenes/enemigoTipo1"))
			std::cout << "Error: No se ha podido cargar la textura del enemigo tipo 1\n";
		break;
	case 2:
		if (!textura.loadFromFile("recursos/imagenes/enemigoTipo2"))
			std::cout << "Error: No se ha podido cargar la textura del enemigo tipo 2\n";
	case 3:
		if (!textura.loadFromFile("recursos/imagenes/enemigoTipo3"))
			std::cout << "Error: No se ha podido cargar la textura del enemigo tipo 3\n";
		break;
	default:
		std::cout << "Error: No se ha podido inicializar las texturas de la clase Enemigo";
		break;
	}
}

void Enemigo::initSprite()
{
	sprite.setTexture(textura);
}

Enemigo::Enemigo(int tipo)
{
	initVariables(tipo);
	initTexture(tipo);
	initSprite();
}

Enemigo::~Enemigo()
{
}

const sf::FloatRect Enemigo::getBounds() const
{
	return sprite.getGlobalBounds();
}

const int& Enemigo::getPuntos() const
{
	return puntos;
}

const int& Enemigo::getAtaque() const
{
	return ataque;
}

void Enemigo::movimiento()
{
}

void Enemigo::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

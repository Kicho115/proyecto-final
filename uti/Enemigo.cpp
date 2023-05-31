#include "Enemigo.h"

void Enemigo::initVariables(int tipo)
{
	this->tipo = tipo;

	spriteInvertido = false;
	vida = vidaMax;
	
	switch (tipo)
	{
	case 1:
		vidaMax = 30;
		ataque = 10;
		puntos = 10;
		velocidad = 1.f;
		break;
	case 2:
		vidaMax = 100;
		ataque = 20;
		puntos = 20;
		velocidad = 0.2f;
	case 3:
		vidaMax = 200;
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
		if (!textura.loadFromFile("recursos/imagenes/enemigoTipo1.png"))
			std::cout << "Error: No se ha podido cargar la textura del enemigo tipo 1\n";
		break;
	case 2:
		if (!textura.loadFromFile("recursos/imagenes/enemigoTipo2.png"))
			std::cout << "Error: No se ha podido cargar la textura del enemigo tipo 2\n";
	case 3:
		if (!textura.loadFromFile("recursos/imagenes/enemigoTipo3.png"))
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
	if (tipo == 1)
		sprite.setScale(0.17f, 0.17f);
}

Enemigo::Enemigo(int tipo, float posX, float posY)
{
	initVariables(tipo);
	initTexture(tipo);
	initSprite();

	sprite.setPosition(posX, posY);
}

Enemigo::~Enemigo()
{
}

const sf::FloatRect Enemigo::getBounds() const
{
	return sprite.getGlobalBounds();
}

const sf::Vector2f& Enemigo::getPos() const
{
	return sprite.getPosition();
}

const int& Enemigo::getPuntos() const
{
	return puntos;
}

const int& Enemigo::getAtaque() const
{
	return ataque;
}

void Enemigo::movimiento(Submarino* submarino)
{
	// Seguir submarino hacia la derecha
	if (submarino->getPos().x > getPos().x)
	{
		if (spriteInvertido)
		{
			sprite.scale(-1.f, 1.f);
			spriteInvertido = false;
		}
		sprite.move(1.f * velocidad, 0.f);
	}

	// Seguir submarino hacia la izquierda
	if (submarino->getPos().x < getPos().x)
	{
		if (!spriteInvertido)
		{
			sprite.scale(-1.f, 1.f);
			spriteInvertido = true;
		}
		sprite.move(-1.f * velocidad, 0.f);
	}
	
	// Seguir submarino hacia arriba
	if (submarino->getPos().y < getPos().y)
		sprite.move(0.f, -1.f * velocidad);
	
	// Seguir submarino hacia abajo
	if (submarino->getPos().y > getPos().y)
		sprite.move(0.f, 1.f * velocidad);
		
}

void Enemigo::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

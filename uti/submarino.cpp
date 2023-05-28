#include "submarino.hpp"

void Submarino::initVariables()
{
	vidaMax = 100;
	vida = vidaMax;
	ataqueCooldownMax = 10.f;
	ataqueCooldown = ataqueCooldownMax;
	ataque = 10;
	puntos = 0;
	velocidad = 0.3f;
}

void Submarino::initTextura()
{
	// Carga la textura desde un archivo
	if (!textura.loadFromFile("recursos/imagenes/sub.png"))
		std::cout << "Error: No se pudo cargar la textura de Jugador.\n";
}

void Submarino::initSprite()
{
	// Asignar textura a sprite
	sprite.setTexture(textura);

	// Escalar el sprite al tamaño deseado
	sprite.scale(1.5f, 1.5f);
}

Submarino::Submarino()
{
	initVariables();
	initTextura();
	initSprite();
}

Submarino::~Submarino()
{
}

int Submarino::getVida()
{
	return vida;
}

int Submarino::getVidaMax()
{
	return vidaMax;
}

void Submarino::setVida(const int vida)
{
	this->vida = vida;
}

void Submarino::perderVida(const int daño)
{
	// Se pierde vida en funcion a la cantidad de daño que se recibe
	vida -= daño;
}

void Submarino::setPosicion(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Submarino::movimiento(const float dirX, const float dirY)
{
	sprite.move(dirX * velocidad, dirY * velocidad);
}

bool Submarino::puedeAtacar()
{
	// Si el cooldown de ataque ha superado el cooldown max, se permite atacar de nuevo
	if (ataqueCooldown >= ataqueCooldownMax)
	{
		ataqueCooldown = 0.f;
		return true;
	}
		return false;
}

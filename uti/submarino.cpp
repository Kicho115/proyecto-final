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

	// Escalar el sprite al tama�o deseado
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

void Submarino::perderVida(const int da�o)
{
	// Se pierde vida en funcion a la cantidad de da�o que se recibe
	vida -= da�o;
}

void Submarino::setPosicion(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Submarino::movimiento()
{
	// Mueve al jugador en funcion de la tecla presionada
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sprite.move(0.f, -1.f * velocidad);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sprite.move(0.f, 1.f * velocidad);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sprite.move(-1.f * velocidad, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		sprite.move(1.f * velocidad, 0.f);
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

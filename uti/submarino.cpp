#include "submarino.hpp"

void Submarino::initVariables()
{
	vidaMax = 100;
	vida = vidaMax;
	ataqueCooldownMax = 10.f;
	ataqueCooldown = ataqueCooldownMax;
	ataque = 10;
	puntos = 0;
	velocidad = 10.0f;
	spriteInvertido = false;
}

void Submarino::initTextura()
{
	// Carga la textura desde un archivo
	if (!textura.loadFromFile("recursos/imagenes/submarino.png"))
		std::cout << "Error: No se pudo cargar la textura de Jugador.\n";
}

void Submarino::initSprite()
{
	// Asignar textura a sprite
	sprite.setTexture(textura);

	// Escalar el sprite al tamaño deseado
	sprite.scale(1.5f, 1.5f);

	sprite.setPosition(960.f - sprite.getGlobalBounds().height / 2, 540.f);
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

const sf::FloatRect Submarino::getBounds() const
{
	return sprite.getGlobalBounds();
}

const sf::Vector2f Submarino::getPos() const
{
	return sprite.getPosition();
}

void Submarino::setVida(const int vida)
{
	this->vida = vida;
}

void Submarino::perderVida(const int daño)
{
	// Se pierde vida en funcion a la cantidad de daño que se recibe
	vida -= daño;
	if (vida < 0)
		vida = 0;
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
	// Cambia la la direccion del sprite en funcion de la direccion a la que se mueve
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!spriteInvertido)
		{
			sprite.scale(-1.f, 1.f);
			spriteInvertido = true;
		}
		sprite.move(-1.f * velocidad, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (spriteInvertido)
		{
			sprite.scale(-1.f, 1.f);
			spriteInvertido = false;
		}
		sprite.move(1.f * velocidad, 0.f);
	}
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

void Submarino::actualizarAtaque()
{
	if (ataqueCooldown < ataqueCooldownMax)
		ataqueCooldown += 0.5f;
}

// Actualiza todo lo relacionado al jugador en el loop del juego
void Submarino::actualizar()
{
	movimiento();
}

void Submarino::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
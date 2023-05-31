#include "Armas.h"

Armas::Armas(sf::Texture* textura, float posX, float posY, float dirX, float dirY, float velocidad)
{
	sprite.setTexture(*textura);
	sprite.setPosition(posX, posY);
	direccion.x = dirX;
	direccion.y = dirY;
	this->velocidad = velocidad;

}

Armas::~Armas()
{
}

sf::FloatRect Armas::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Armas::movimiento()
{
	sprite.move(direccion * velocidad);
}

void Armas::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

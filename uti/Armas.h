#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Armas
{
private:
	float velocidad;

	sf::Sprite sprite;
	sf::Vector2f direccion;
public:
	Armas(sf::Texture* textura, float posX, float posY, float dirX, float dirY, float velocidad);
	~Armas();

	// Accesores
	sf::FloatRect getBounds() const;

	// Funciones
	void movimiento();
	void render(sf::RenderTarget* target);
};


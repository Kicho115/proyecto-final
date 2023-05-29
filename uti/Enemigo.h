#pragma once

#include "Entidad.h"

class Enemigo : private Entidad 
{
private:
	int tipo;

	sf::Texture textura;
	sf::Sprite sprite;

	// Funciones init
	void initVariables(int tipo);
	void initTexture(int tipo);
	void initSprite();
public:
	Enemigo(int tipo);
	~Enemigo();

	// Accesores
	const sf::FloatRect getBounds() const;
	const int& getPuntos() const;
	const int& getAtaque() const;

	// Funcions
	void movimiento();
	void render(sf::RenderTarget* target);
};


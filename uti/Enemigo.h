#pragma once

#include "Entidad.h"
#include "submarino.hpp"

class Enemigo : private Entidad 
{
private:
	int tipo;
	float tiempoSpawnEnemigoMax;
	float tiempoSpawnEnemigo;

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
	const sf::Vector2f& getPos() const;
	const int& getPuntos() const;
	const int& getAtaque() const;

	// Funcions
	void movimiento(Submarino& submarino);
	void render(sf::RenderTarget* target);
};


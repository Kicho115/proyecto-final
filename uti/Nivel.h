#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Nivel
{
private:
	int nivel;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Music music;

	// Funciones init
	void initVariables(int nivel);
	void initNivel();
public:
	// Constructor / Destructor
	Nivel(int nivel);
	~Nivel();

	// Accesores
	int getNivel() const;

	// Mutadores
	void setNivel(int nivel);

	// Funciones
	void render(sf::RenderTarget& target);
};


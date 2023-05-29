#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Nivel
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Music music;

	// Funciones init
	void initNivel(int nivel);
public:
	// Constructor / Destructor
	Nivel(int nivel);
	~Nivel();

	void render(sf::RenderTarget& target);
};

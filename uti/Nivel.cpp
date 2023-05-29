#include "Nivel.h"

// Inicializa la textura del background y musica en funcion del nivel en el que se encuentre el juego
void Nivel::initNivel(int nivel)
{
	if (nivel == 0)
	{
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo0.png"))
			std::cout << "Error: No se pudo cargar el background del nivel 0.\n";
		// Inicializa la musica
		if (!music.openFromFile("recursos/audio/musicMenu/png"))
			std::cout << "Error: No se pudo cargar la musica del nivel 0.\n";
	}
	else if (nivel == 1)
	{
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile(""))
			std::cout << "Error: No se pudo cargar el background del nivel 1\n";
		// Inicializa la musica
		if (!music.openFromFile("recursos/audio/musicMenu"))
			std::cout << "Error: No se pudo cargar la musica del nivel 1.\n";
	}
	else if (nivel == 2)
	{
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile(""))
			std::cout << "Error: No se pudo cargar el background del nivel 2.\n";
		// Inicializa la musica
		if (!music.openFromFile("recursos/audio/musicMenu"))
			std::cout << "Error: No se pudo cargar la musica del nivel 2.\n";
	}

	// Asigna la textura al sprite
	backgroundSprite.setTexture(backgroundTexture);
}


Nivel::Nivel(int nivel)
{
	initNivel(nivel);
}

Nivel::~Nivel()
{
}

void Nivel::render(sf::RenderTarget& target)
{
	target.draw(backgroundSprite);
}

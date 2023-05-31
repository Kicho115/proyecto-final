#include "Nivel.h"

void Nivel::initVariables(int nivel)
{
	this->nivel = nivel;
}

// Inicializa la textura del background y musica en funcion del nivel en el que se encuentre el juego
void Nivel::initNivel(int nivel)
{
	switch (nivel)
	{
	case 0:
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo0.png"))
			std::cout << "Error: No se pudo cargar el background del nivel 0.\n";
		// Inicializa la musica
		if (!music.openFromFile("recursos/audio/musicMenu.wav"))
			std::cout << "Error: No se pudo cargar la musica del nivel 0.\n";
		break;
	case 1:
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo1.png"))
			std::cout << "Error: No se pudo cargar el background del nivel 1.\n";
		// Inicializa la musica
		if (!music.openFromFile("recursos/audio/musicMenu.wav"))
			std::cout << "Error: No se pudo cargar la musica del nivel 0.\n";
		break;
	case 2:
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo2.png"))
			std::cout << "Error: No se pudo cargar el background del nivel 0.\n";
		break;
	default:
		break;
	}

	// Asigna la textura al sprite
	backgroundSprite.setTexture(backgroundTexture);

	// Reproducir la musica infinitamente
	music.play();
	music.setVolume(30.f);
	music.setLoop(true);
}


Nivel::Nivel(int nivel)
{
	initVariables(nivel);
	initNivel(nivel);
}

Nivel::~Nivel()
{
}

int Nivel::getNivel() const
{
	return nivel;
}

void Nivel::setNivel(int nivel)
{
	this->nivel = nivel;
}

void Nivel::render(sf::RenderTarget& target)
{
	target.draw(backgroundSprite);
}

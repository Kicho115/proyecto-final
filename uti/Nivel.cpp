#include "Nivel.h"

void Nivel::initVariables(int nivel)
{
	this->nivel = nivel;
}

// Inicializa la textura del background y musica en funcion del nivel en el que se encuentre el juego
void Nivel::initNivel()
{
	if (nivel == 0)
	{
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo0.png"))
			std::cout << "Error: No se pudo cargar el background del nivel 0.\n";
		// Inicializa la musica
		if (!music.openFromFile("recursos/audio/musicMenu.wav"))
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

	// Reproducir la musica infinitamente
	music.play();
	music.setLoop(true);
}


Nivel::Nivel(int nivel)
{
	initVariables(nivel);
	initNivel();
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

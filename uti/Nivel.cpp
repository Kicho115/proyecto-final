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
<<<<<<< HEAD
		if (!music.openFromFile("recursos/audio/Decoherence.wav"))
			std::cout << "Error: No se pudo cargar la musica del nivel 1.\n";
		music.setPlayingOffset(sf::seconds(300.f)); // Avanzar 20 segundos
=======
		if (!music.openFromFile("recursos/audio/musicMenu.wav"))
			std::cout << "Error: No se pudo cargar la musica del nivel 0.\n";
>>>>>>> parent of d815e26 (Cambios)
		break;
	case 2:
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo2.png"))
<<<<<<< HEAD
			std::cout << "Error: No se pudo cargar el background del nivel 2.\n";
		if (!music.openFromFile("recursos/audio/Decoherence.wav"))
			std::cout << "Error: No se pudo cargar la musica del nivel 1.\n";
		break;
	case 3:
		// Inicializa la textura del background
		if (!backgroundTexture.loadFromFile("recursos/imagenes/fondo3.png"))
			std::cout << "Error: No se pudo cargar el background del nivel 3.\n";
		if (!music.openFromFile("recursos/audio/musicLevel3.wav"))
			std::cout << "Error: No se pudo cargar la musica del nivel 3.\n";
		music.setPlayingOffset(sf::seconds(600.f)); // Avanzar 20 segundos
		break;
	case 4:
		music.stop();
=======
			std::cout << "Error: No se pudo cargar el background del nivel 0.\n";
>>>>>>> parent of d815e26 (Cambios)
		break;
	default:
		break;
	}

	// Asigna la textura al sprite
	backgroundSprite.setTexture(backgroundTexture);

	// Reproducir la musica infinitamente
	music.play();
	music.setVolume(30.f);
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

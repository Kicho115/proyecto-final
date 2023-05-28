#include "Juego.h"

void Juego::initWindow()
{
}

void Juego::initGUI()
{
}

void Juego::initSubmarino()
{
}

Juego::Juego()
{
}

Juego::~Juego()
{
}

void Juego::run()
{
	while (window->isOpen()) {

	}
}

// Comprueba si se quiere cerrar la ventana.
void Juego::actualizarPollEvent()
{
	sf::Event e;

	while (window->pollEvent(e))
	{
		// Cerrar ventana al presionar X en la esquina
		if (e.sf::Event::type == sf::Event::Closed)
			window->close();
		// Cerrar ventana al presionar tecla escape
		if (e.sf::Event::KeyPressed && e.sf::Event::key.code == sf::Keyboard::Escape)
			window->close();
	}
}

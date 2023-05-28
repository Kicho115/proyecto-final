#include "Juego.h"

void Juego::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Los panitas espaciales", sf::Style::Close | sf::Style::Fullscreen);
	window->setFramerateLimit(60); // Limita los fps
	window->setVerticalSyncEnabled(false); 	// Desactiva VSync para mejor rendimiento;
}

void Juego::initGUI()
{
}

void Juego::initSubmarino()
{
	submarino = new Submarino;
}

Juego::Juego()
{
	initWindow();
	initGUI();
}

Juego::~Juego()
{
	delete window;
	delete submarino;

	/*for (auto* i : enemigos)
	{
		delete i;
	}*/
}

void Juego::run()
{
	while (window->isOpen())
	{
		// Funcion parra cerrar ventana
		actualizarPollEvent();
		
		// Actualizar el juego si el jugador sigue con vida
		if (submarino->getVida() > 0)
			actualizarJuego();

		// Funcion que dibuja en la ventana
		render();
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

// Actualiza el juego
void Juego::actualizarJuego()
{
}

// Funcion que dibuja en la ventana
void Juego::render()
{
	window->display();
}

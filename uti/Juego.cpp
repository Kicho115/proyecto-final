#include "Juego.h"

void Juego::initVariablesEnemigos()
{
	tiempoSpawnEnemigoMax = 50.f;
	tiempoSpawnEnemigo = tiempoSpawnEnemigoMax;
}


void Juego::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Los panitas espaciales", sf::Style::Close | sf::Style::Fullscreen);
	window->setFramerateLimit(60); // Limita los fps
	window->setVerticalSyncEnabled(false); 	// Desactiva VSync para mejor rendimiento;
}

void Juego::initGUI()
{
	// Cargar fuente
	if(!fuente.loadFromFile("recursos/fuentes/fuente.otf"))
		std::cout << "Error: No se ha cargado la fuente del texto en clase juego";

	// Inicializar texto de los puntos del submarino
	puntos.setFont(fuente);
	puntos.setCharacterSize(40);
	puntos.setFillColor(sf::Color::White);

	// Inicializar texto de game over
	gameOver.setFont(fuente);
	gameOver.setCharacterSize(100);
	gameOver.setFillColor(sf::Color::Red);
	gameOver.setString("Game Over");

	// Posicion de texto de game over
	int x = window->getSize().x / 2.f - gameOver.getGlobalBounds().width / 2;
	int y = window->getSize().y / 2.f - gameOver.getGlobalBounds().height / 2;
	gameOver.setPosition(x, y);

	// Inicializar barra de vida de submarino
	barraVida.setSize(sf::Vector2f(300.f, 25.f));
	barraVida.setFillColor(sf::Color::Red);
	barraVida.setPosition(sf::Vector2f(50.f, 65.f));

	barraPerderVida = barraVida;
	barraPerderVida.setFillColor(sf::Color(25, 25, 25, 200));
}

void Juego::initSonido()
{
	if (!golpeBuffer.loadFromFile("recursos/audio/golpeSubmarino.wav"))
		std::cout << "Error: No se ha cargado el audio para los golpes al submarino.\n";
	golpeSonido.setBuffer(golpeBuffer);

	if (!enemigoMuertoBuffer.loadFromFile("recursos/audio/golpeEnemigo.wav"))
		std::cout << "Error: No se ha cargado el audio para los golpes al enemigo.\n";
	enemigoMuertoSonido.setBuffer(enemigoMuertoBuffer);
}

void Juego::initNivel()
{
	nivel = new Nivel(0);
}

void Juego::initSubmarino()
{
	submarino = new Submarino;
}

Juego::Juego()
{
	initVariablesEnemigos();
	initWindow();
	initGUI();
	initSonido();
	initNivel();
	initSubmarino();
}

Juego::~Juego()
{
	delete window;
	delete submarino;
	delete nivel;
	
	// Borrar enemigos en vector
	for (auto* i : enemigos)
	{
		delete i;
	}
}

void Juego::run()
{
	while (window->isOpen())
	{
		// Funcion parra cerrar ventana
		actualizarPollEvent();

		// Actualizar el juego si el jugador sigue con vida
		if (this->submarino->getVida() > 0)
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
		// Cerrar ventana al presionar X en la esquina en modo ventana
		if (e.Event::type == sf::Event::Closed)
			window->close();
		// Cerrar ventana al presionar tecla escape
		if (e.Event::KeyPressed && e.sf::Event::key.code == sf::Keyboard::Escape)
			window->close();
	}
}

void Juego::actualizarNivel()
{
	if (nivel->getNivel() == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		nivel->setNivel(1);
		nivel->actualizar();
	}
}

void Juego::actualizarEnemigos()
{
	// Spawnear enemigo si el cooldown es mayor al cooldown maximo
	tiempoSpawnEnemigo += 0.5f;
	if (tiempoSpawnEnemigo >= tiempoSpawnEnemigoMax)
	{
		enemigos.push_back(new Enemigo(1, static_cast<float>(rand() % 1920), static_cast<float>(rand() % 1920)));
		tiempoSpawnEnemigo = 0.f;
	}

	// Eliminar enemigos
	unsigned cont = 0;
	for (auto* enemigo : enemigos)
	{

		enemigo->movimiento(submarino);


		if (enemigo->getBounds().intersects(submarino->getBounds()))
		{
			//Reproducir sonido de golpe
			golpeSonido.play();

			// Perder vida en funcion del ataque del enemigo
			submarino->perderVida(enemigos.at(cont)->getAtaque());

			// Delete enemigo si toca el submarino
			delete enemigos.at(cont);
			enemigos.erase(enemigos.begin() + cont);
	
			std::cout << enemigos.size() << "\n";
		}
		
			// Eliminar enemigo y bala si intersectan
			for (int i = 0; i < enemigos.size(); i++)
			{
				bool enemigoMuerto = false;

				for (size_t j = 0; j < submarino->getBalasVector().size() && !enemigoMuerto; j++)
				{
					if (enemigos[i]->getBounds().intersects(submarino->getBalasVector()[j]->getBounds()))
					{
						enemigoMuertoSonido.play();
						submarino->setPuntos(enemigos[i]->getPuntos());

						delete enemigos[i];
						enemigos.erase(enemigos.begin() + i);
						//std::cout << "Enemigo eliminado\n";

						submarino->setBalasVector(j); // Eliminar balas
						//std::cout << "Sub eliminado\n";
						enemigoMuerto = true;
					}
				}
			}
		++cont;
	}

}

void Juego::actualizarGUI()
{
	std::stringstream ss;
	// Actualizar string de puntos
	ss << "Points: " << submarino->getPuntos()
		<< "\nHp: ";

	// Mostrar puntos en pantalla
	puntos.setString(ss.str());

	// Actualizar Barra de vida
	float hpPercent = static_cast<float>(submarino->getVida()) / submarino->getVidaMax();
	barraVida.setSize(sf::Vector2f(300.f * hpPercent, barraVida.getSize().y));

	// Hacer que la barra de vida siga al jugador
	//int x = submarino->getPos().x - submarino->getBounds().width;
	//int y = submarino->getPos().y - submarino->getBounds().height;

	//barraVida.setPosition(x, y);
	//barraPerderVida.setPosition(barraVida.getPosition());
}

// Actualiza el juego
void Juego::actualizarJuego()
{
	// Comprueba si se ha avanzado de nivel
	actualizarNivel();
	if (nivel->getNivel() != 0)
	{
		submarino->actualizar();
		actualizarGUI();
		actualizarEnemigos();
	}
}

void Juego::renderGUI()
{
	window->draw(puntos);
	window->draw(barraPerderVida);
	window->draw(barraVida);
}

// Funcion que dibuja en la ventana
void Juego::render()
{
	// Limpiar el fotograma anterior
	window->clear();

	// Mostrar background
	nivel->render(*window);

	// Mostrar submarino
	if (nivel->getNivel() != 0)
	{
		renderGUI();

		submarino->render(*window);
		
		for (auto* enemigo : enemigos)
		{
			enemigo->render(window);
		}

		submarino->renderBala(window);
	}

	// Mostrar el fotograma actual
	window->display();
}
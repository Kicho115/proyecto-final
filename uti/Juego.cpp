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
	pecesAsesinados = 0;
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
		nivel->initNivel(1);
	}
	else if (nivel->getNivel() == 1 && pecesAsesinados == 20)
	{
		nivel->setNivel(2);
		nivel->initNivel(2);

		enemigos.clear();
		submarino->setVida(100);

	}
	else if (nivel->getNivel() == 2 && pecesAsesinados == 50)
	{
		nivel->setNivel(3);
		nivel->initNivel(3);

		enemigos.clear();
		submarino->setVida(100);
	}

}

void Juego::actualizarEnemigos()
{
	// Spawnear enemigo si el cooldown es mayor al cooldown maximo
	tiempoSpawnEnemigo += 0.5f;
	if (tiempoSpawnEnemigo >= tiempoSpawnEnemigoMax)
	{
		enemigos.push_back(new Enemigo(nivel->getNivel(), 1920 + static_cast<float>(rand() % 100), 1080 + static_cast<float>(rand() % 540)));
		enemigos.push_back(new Enemigo(nivel->getNivel(), 0 - static_cast<float>(rand() % 900), 0 - static_cast<float>(rand() % 100)));
		enemigos.push_back(new Enemigo(nivel->getNivel(), 1920 + static_cast<float>(rand() % 100), 1080 - static_cast<float>(rand() % 540)));
		enemigos.push_back(new Enemigo(nivel->getNivel(), 0 - static_cast<float>(rand() % 900), 0 + static_cast<float>(rand() % 100)));

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
						pecesAsesinados++;
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
		<< "\nHp: " << "\nPeces cazados: " << pecesAsesinados << " / " << "20";

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
		submarino->colision();
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

/// Funcion que dibuja en la ventana
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

	// Mostrar game over si se muere
	if (submarino->getVida() <= 0)
	{
		window->draw(gameOver);
	}

	// Mostrar el fotograma actual
	window->display();
<<<<<<< HEAD
}

void Juego::ending()
{

		sf::RenderWindow window(sf::VideoMode(1920, 1080), "Image Fade", sf::Style::Fullscreen);

		sf::Music music;
		if (!music.openFromFile("recursos/audio/EndingTheme.wav"))
		{
			// Por si no carga el archivo de sonido
			return;
		}
		music.play();

		sf::Texture texture1;
		if (!texture1.loadFromFile("recursos/imagenes/Ending1.png"))
		{
			return;
		}

		sf::Texture texture2;
		if (!texture2.loadFromFile("recursos/imagenes/Ending2.png"))
		{
			return;
		}

		sf::Sprite sprite(texture1);

		sf::Clock clock;
		float fadeDuration = 7.0f; // Duración total de fundido en segundos
		float fadeInDuration = 7.0f; // Duración de fundido de entrada en segundos
		float fadeTimer = 0.0f;
		float fadeSpeed = 255.0f / fadeInDuration;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

			// Cerrar ventana al presionar tecla escape
			if (event.Event::KeyPressed && event.sf::Event::key.code == sf::Keyboard::Escape)
					window.close();
			}

			// Actualizar el temporizador de fundido
			float deltaTime = clock.restart().asSeconds();
			fadeTimer += deltaTime;

			// Calcular el valor actual de alpha en función del temporizador de fundido y la velocidad
			float alpha = 0.0f;
			if (fadeTimer <= fadeInDuration)
			{
				alpha = fadeTimer * fadeSpeed;
			}
			else if (fadeTimer <= fadeDuration)
			{
				alpha = 255.0f;
			}
			else
			{
				alpha = 255.0f - ((fadeTimer - fadeDuration) * fadeSpeed);
			}

			// Acotar el valor de alpha entre 0 y 255
			alpha = std::max(0.0f, std::min(alpha, 255.0f));

			// Establecer el valor de alpha en el color del sprite
			sf::Color spriteColor = sprite.getColor();
			spriteColor.a = static_cast<sf::Uint8>(alpha);
			sprite.setColor(spriteColor);

			// Comprobar si el fundido ha terminado
			if (fadeTimer >= fadeDuration + fadeInDuration)
			{
				sprite.setTexture(texture2); // Cambiar la textura del sprite a la segunda imagen
				sprite.setColor(sf::Color(255, 255, 255, 255)); // Restaurar la opacidad completa
				fadeTimer = 0.0f; // Reiniciar el temporizador para la segunda imagen
			}

			window.clear();
			window.draw(sprite);
			window.display();
		}
	}

void Juego::cine2()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Cambio de imágenes");

	// Cargar las texturas de las imágenes
	sf::Texture image1Texture;
	if (!image1Texture.loadFromFile("recursos/imagenes/Lore1.png"))
	{
		std::cout << "Error al cargar Lore1.png" << std::endl;
		return;
	}

	sf::Texture image2Texture;
	if (!image2Texture.loadFromFile("recursos/imagenes/Lore2.png"))
	{
		std::cout << "Error al cargar Lore2.png" << std::endl;
		return;
	}

	sf::Texture image3Texture;
	if (!image3Texture.loadFromFile("recursos/imagenes/Lore3.png"))
	{
		std::cout << "Error al cargar Lore3.png" << std::endl;
		return;
	}

	sf::Texture image4Texture;
	if (!image4Texture.loadFromFile("recursos/imagenes/Lore4.png"))
	{
		std::cout << "Error al cargar black.png" << std::endl;
		return;
	}

	// Cargar las texturas de las imágenes adicionales
	sf::Texture image5Texture;
	if (!image5Texture.loadFromFile("recursos/imagenes/Lore5.png"))
	{
		std::cout << "Error al cargar image5.png" << std::endl;
		return;
	}

	sf::Texture image6Texture;
	if (!image6Texture.loadFromFile("recursos/imagenes/Lore6.png"))
	{
		std::cout << "Error al cargar image6.png" << std::endl;
		return;
	}

	sf::Texture image7Texture;
	if (!image7Texture.loadFromFile("recursos/imagenes/Lore7.png"))
	{
		std::cout << "Error al cargar image7.png" << std::endl;
		return;
	}

	sf::Texture image8Texture;
	if (!image8Texture.loadFromFile("recursos/imagenes/Lore8.png"))
	{
		std::cout << "Error al cargar image8.png" << std::endl;
		return;
	}

	sf::Texture image9Texture;
	if (!image9Texture.loadFromFile("recursos/imagenes/Lore9.png"))
	{
		std::cout << "Error al cargar image9.png" << std::endl;
		return;
	}

	// Crear el sprite inicial con la imagen1
	sf::Sprite sprite(image1Texture);

	// Arreglo de texturas
	sf::Texture textures[] = { image1Texture, image2Texture, image3Texture, image4Texture,
							   image5Texture, image6Texture, image7Texture, image8Texture, image9Texture };
	int currentTextureIndex = 0;

	// Variables para controlar el tiempo
	sf::Clock clock;
	float elapsedTime = 0.0f;
	float changeTime = 10.0f; // Cambiar la imagen después de x segundos

	// Bucle principal
	while (window.isOpen())
	{
		// Manejo de eventos
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			// Cerrar ventana al presionar tecla escape
			if (event.Event::KeyPressed && event.sf::Event::key.code == sf::Keyboard::Space)
				window.close();
		}


		// Actualizar el tiempo transcurrido
		elapsedTime += clock.restart().asSeconds();

		// Verificar si ha pasado el tiempo suficiente para cambiar la imagen
		if (elapsedTime >= changeTime)
		{
			// Cambiar la imagen al siguiente índice del arreglo de texturas
			currentTextureIndex = (currentTextureIndex + 1) % 9;
			sprite.setTexture(textures[currentTextureIndex]);

			// Reiniciar el tiempo transcurrido
			elapsedTime = 0.0f;
		}

		// Limpiar la ventana
		window.clear();

		// Dibujar el sprite en la ventana
		window.draw(sprite);

		// Mostrar la ventana
		window.display();
	}
}

void Juego::donkey()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Image Fade");

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("recursos/audio/IntroTheme.wav"))
	{
		// Por si no carga el archivo de sonido
	}

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	sf::Texture texture1;
	if (!texture1.loadFromFile("recursos/imagenes/Donkey logo.png"))
	{
		return;
	}

	sf::Texture texture2;
	
	texture2.loadFromFile("recursos/imagenes/Tocho.png");

	sf::Sprite sprite(texture1);

	sf::Clock clock;
	float fadeDuration = 7.0f; // Duración total de fundido en segundos
	float fadeInDuration = 7.0f; // Duración de fundido de entrada en segundos
	float fadeTimer = 0.0f;
	float fadeSpeed = 255.0f / fadeInDuration;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			// Cerrar ventana al presionar tecla escape
			if (event.Event::KeyPressed && event.sf::Event::key.code == sf::Keyboard::Enter)
				window.close();
		}

		// Actualizar el temporizador de fundido
		float deltaTime = clock.restart().asSeconds();
		fadeTimer += deltaTime;

		// Calcular el valor actual de alpha en función del temporizador de fundido y la velocidad
		float alpha = 0.0f;
		if (fadeTimer <= fadeInDuration)
		{
			alpha = fadeTimer * fadeSpeed;
		}
		else if (fadeTimer <= fadeDuration)
		{
			alpha = 255.0f;
		}
		else
		{
			alpha = 255.0f - ((fadeTimer - fadeDuration) * fadeSpeed);
		}

		// Acotar el valor de alpha entre 0 y 255
		alpha = std::max(0.0f, std::min(alpha, 255.0f));

		// Establecer el valor de alpha en el color del sprite
		sf::Color spriteColor = sprite.getColor();
		spriteColor.a = static_cast<sf::Uint8>(alpha);
		sprite.setColor(spriteColor);

		// Comprobar si el fundido ha terminado
		if (fadeTimer >= fadeDuration + fadeInDuration)
		{
			sprite.setTexture(texture2); // Cambiar la textura del sprite a la segunda imagen
			sprite.setColor(sf::Color(255, 255, 255, 255)); // Restaurar la opacidad completa
			fadeTimer = 0.0f; // Reiniciar el temporizador para la segunda imagen
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}


=======
}
>>>>>>> parent of d815e26 (Cambios)

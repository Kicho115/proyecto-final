#pragma once

#include "Nivel.h"
#include "Enemigo.h"

#include <vector>
#include <sstream>

/*
	Clase que actua como motor de juego.
	- Aqui se actualiza y renderiza todo.
*/

class Juego
{
private:
	// Ventana de juego
	sf::RenderWindow* window;

	// Objeto submarino (jugador)
	Submarino* submarino;

	// Nivel
	Nivel* nivel;

	int pecesAsesinados;
	int pecesMeta;

	// Enemigos
	float tiempoSpawnEnemigoMax;
	float tiempoSpawnEnemigo;
	std::vector<Enemigo*> enemigos;

	// Interfaz de usuario (GUI)
	sf::RectangleShape barraVida;
	sf::RectangleShape barraPerderVida;

	sf::Font fuente;
	sf::Text puntos;
	sf::Text peces;
	sf::Text gameOver;

	// Efectos de sonido
	sf::SoundBuffer golpeBuffer;
	sf::Sound golpeSonido;

	sf::SoundBuffer enemigoMuertoBuffer;
	sf::Sound enemigoMuertoSonido;

	// Ayuda para intro
	int i;

	// Funciones Init
	void initVariablesEnemigos();
	void initWindow();
	void initGUI();
	void initSonido();

	void initNivel();
	void initSubmarino();
public:
	Juego();
	~Juego();

	// Funciones
	void run();
	void actualizarPollEvent();
	void actualizarNivel();
	void actualizarEnemigos();
	void actualizarGUI();
	void actualizarJuego();

	void renderGUI();
	void render();

	// Sebas
	void ending();
	void cine2();
	void donkey();
};
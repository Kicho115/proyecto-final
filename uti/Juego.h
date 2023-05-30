#pragma once

#include "Nivel.h"
#include "submarino.hpp"
#include "Enemigo.h"

#include <vector>

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

	// Objeto Nivel
	Nivel* nivel;

	// Enemigos
	float tiempoSpawnEnemigoMax;
	float tiempoSpawnEnemigo;
	std::vector<Enemigo*> enemigos;

	// Interfaz de usuario (GUI)
	sf::RectangleShape barraVidaMax;
	sf::RectangleShape barraVida;

	sf::Font fuente;
	sf::Text puntos;
	sf::Text gameOver;

	// Funciones Init
	void initVariablesEnemigos();
	void initWindow();
	void initGUI();

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
	void actualizarJuego();
	void render();
};


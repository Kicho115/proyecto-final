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
	// Nivel en el que se encuentra
	int nivel;

	// Ventana de juego
	sf::RenderWindow* window;

	// Objeto submarino (jugador)
	Submarino* submarino;

	// Objeto Nivel
	Nivel* menu;

	// Enemigos
	std::vector<Enemigo> enemigos;

	// Interfaz de usuario (GUI)
	sf::RectangleShape barraVidaMax;
	sf::RectangleShape barraVida;

	sf::Font fuente;
	sf::Text puntos;
	sf::Text gameOver;

	// Funciones Init
	void initVariables();
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
	void actualizarJuego();
	void render();
};


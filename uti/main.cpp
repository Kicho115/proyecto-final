/*
	autores: Oscar Angulo, Ricardo Campos, Sebastian Soto y Gael Oceguera
	proyecto: final
*/

#include "Juego.h"

int main()
{

	// Inicializar semilla para numero aleatorio
	srand(static_cast<unsigned int>(time(0)));

	Juego juego;

	juego.run();

    return 0;
}
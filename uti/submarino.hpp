#include "Entidad.h"

class Submarino : private Entidad
{
private:
	float ataqueCooldown;
	float ataqueCooldownMax;

	sf::Texture textura;
	sf::Sprite sprite;

	// Funciones init
	void initVariables();
	void initTextura();
	void initSprite();

public:
	// Constructor / Destructor
	Submarino();
	virtual ~Submarino();

	// Accesores
	int getVida();
	int getVidaMax();

	// Mutadores
	void setVida(const int vida);
	void perderVida(const int daño); // Resta vida, se llama al recibir daño

	// Funciones
	void setPosicion(const float x, const float y);
	void movimiento(const float dirX, const float dirY); // Mover al jugador
	bool puedeAtacar(); // Revisa si no hay cooldown para atacar

};

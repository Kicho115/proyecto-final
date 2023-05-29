#include "Entidad.h"

/*
	Clase que controla el movimiento del jugador
	y sus atributos.
*/

class Submarino : private Entidad
{
private:
	float ataqueCooldown;
	float ataqueCooldownMax;

	sf::Texture textura;
	sf::Sprite sprite;
	// variable para detectar si el sprite esta invertido
	bool spriteInvertido = false;

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
	const sf::FloatRect getBounds() const; // Mustra el espacio que abarca el submarino
	const sf::Vector2f getPos() const; // Muestra la posicion del submarino

	// Mutadores
	void setVida(const int vida);
	void perderVida(const int daño); // Resta vida, se llama al recibir daño

	// Funciones
	void setPosicion(const float x, const float y);
	void movimiento(); // Mover al jugador
	bool puedeAtacar(); // Revisa si no hay cooldown para atacar


	void actualizarAtaque(); // Añade cooldown al ataque
	void actualizar(); // Actualiza todo lo relacionado al jugador en el loop del juego

	void render(sf::RenderTarget& target); // Renderiza el sprite
};

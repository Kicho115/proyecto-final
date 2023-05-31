#include "Entidad.h"
#include "Armas.h"

#include <SFML/Audio.hpp>

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
	

	// Armas (balas)
	std::map<std::string, sf::Texture*> texturaBalas;
	std::vector<Armas*> balas;

	// Sonido de armas
	sf::SoundBuffer balaBuffer;
	sf::Sound balaSonido;

	// Funciones init
	void initVariables();
	void initTextura();
	void initTexturaBalas();
	void initSonido();
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
	void acciones(); // Mover al jugador
	bool puedeAtacar(); // Revisa si no hay cooldown para atacar
	
	void actualizarBala(); // Mueve a la bala a traves de la pantalla y la elimina al salir de ella
	void actualizarAtaque(); // Añade cooldown al ataque
	void actualizar(); // Actualiza todo lo relacionado al jugador en el loop del juego

	void renderBala(sf::RenderTarget* target); // Renderiza la bala
	void render(sf::RenderTarget& target); // Renderiza el sprite
};
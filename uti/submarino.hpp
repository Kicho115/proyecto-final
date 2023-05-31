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
	int getPuntos();
	std::vector<Armas*> getBalasVector(); // Regresa el vector de balas
	const sf::FloatRect getBounds() const; // Regresa el espacio que abarca el submarino
	const sf::Vector2f getPos() const; // Regresa la posicion del submarino en la ventana
	const bool getSpriteSentido() const;

	// Mutadores
	void setVida(const int vida);
	void setPuntos(int puntos);
	void perderVida(const int daño); // Resta vida, se llama al recibir daño
	void setBalasVector(int i); // Eliminar elementos del vector

	// Funciones
	void setPosicion(const float x, const float y);
	void acciones(); // Mover al jugador
	bool puedeAtacar(); // Revisa si no hay cooldown para atacar
	
	void actualizarBala(); // Mueve a la bala a traves de la pantalla y la elimina al salir de ella
	void actualizarAtaque(); // Añade cooldown al ataque
	void colision(); // Revisa colisiones con los bordes de la ventana
	void actualizar(); // Actualiza todo lo relacionado al jugador en el loop del juego

	void renderBala(sf::RenderTarget* target); // Renderiza la bala
	void render(sf::RenderTarget& target); // Renderiza el sprite
};
#include "submarino.hpp"

void Submarino::initVariables()
{
	vidaMax = 100;
	vida = vidaMax;
	ataqueCooldownMax = 10.f;
	ataqueCooldown = ataqueCooldownMax;
	ataque = 10;
	puntos = 0;
	velocidad = 10.0f;
	spriteInvertido = false;
}

void Submarino::initTextura()
{
	// Carga la textura desde un archivo
	if (!textura.loadFromFile("recursos/imagenes/submarino.png"))
		std::cout << "Error: No se pudo cargar la textura de Jugador.\n";
}

void Submarino::initTexturaBalas()
{
	// Valor de la key sera una textura
	texturaBalas["bala"] = new sf::Texture;
	// Carga la textura
	texturaBalas["bala"]->loadFromFile("recursos/imagenes/bala.png");
}

void Submarino::initSonido()
{
	if (!balaBuffer.loadFromFile("recursos/audio/bala.wav"))
		std::cout << "Error: No se ha podido cargar el audio de las balas en clase submarino.\n";
	balaSonido.setBuffer(balaBuffer);
}

void Submarino::initSprite()
{
	// Asignar textura a sprite
	sprite.setTexture(textura);

	// Escalar el sprite al tamaño deseado
	sprite.scale(1.5f, 1.5f);

	sprite.setPosition(960.f - sprite.getGlobalBounds().height / 2, 540.f);
}

Submarino::Submarino()
{
	initVariables();
	initTextura();
	initTexturaBalas();
	initSonido();
	initSprite();
}

Submarino::~Submarino()
{
	// Eliminar textura de balas en map
	for (auto& i : texturaBalas)
	{
		delete i.second;
	}
	// Eliminar objeto arma en vector
	for (auto* i : balas)
	{
		delete i;
	}
}

int Submarino::getVida()
{
	return vida;
}

int Submarino::getVidaMax()
{
	return vidaMax;
}

int Submarino::getPuntos()
{
	return puntos;
}

std::vector<Armas*> Submarino::getBalasVector()
{
	return balas;
}

const sf::FloatRect Submarino::getBounds() const
{
	return sprite.getGlobalBounds();
}

const sf::Vector2f Submarino::getPos() const
{
	return sprite.getPosition();
}

const bool Submarino::getSpriteSentido() const
{
	return spriteInvertido;
}

void Submarino::setVida(const int vida)
{
	this->vida = vida;
}

void Submarino::setPuntos(int puntos)
{
	this->puntos += puntos;
}

void Submarino::perderVida(const int daño)
{
	// Se pierde vida en funcion a la cantidad de daño que se recibe
	vida -= daño;
	if (vida < 0)
		vida = 0;
}

void Submarino::setBalasVector(int i)
{
	delete balas[i];
	balas.erase(balas.begin() + i);

}

void Submarino::setPosicion(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Submarino::acciones()
{
	// Mueve al jugador en funcion de la tecla presionada
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sprite.move(0.f, -1.f * velocidad);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sprite.move(0.f, 1.f * velocidad);

	// Cambia la la direccion del sprite en funcion de la direccion a la que se mueve
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (!spriteInvertido)
		{
			sprite.scale(-1.f, 1.f);
			spriteInvertido = true;
		}
		sprite.move(-1.f * velocidad, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (spriteInvertido)
		{
			sprite.scale(-1.f, 1.f);
			spriteInvertido = false;
		}
		sprite.move(1.f * velocidad, 0.f);
	}

	// Crea balas
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && puedeAtacar())
	{
		int y = getPos().y + getBounds().height / 2.f;

		balaSonido.setVolume(30.f);
		balaSonido.play();

		if (!spriteInvertido)
		{
			int x = getPos().x + getBounds().width;
			balas.push_back(new Armas(texturaBalas["bala"], x, y, 1.f, 0.f, 15.f));
		}
		else
		{
			int x = getPos().x - getBounds().width;
			balas.push_back(new Armas(texturaBalas["bala"], x, y, -1.f, 0.f, 15.f));
		}
	}

}

bool Submarino::puedeAtacar()
{
	// Si el cooldown de ataque ha superado el cooldown max, se permite atacar de nuevo
	if (ataqueCooldown >= ataqueCooldownMax)
	{
		ataqueCooldown = 0.f;
		return true;
	}
	return false;
}

void Submarino::actualizarBala()
{
	for (auto* bala : balas)
	{
		unsigned cont = 0;

		bala->movimiento();

		// Si la bala se sale de los limites de la ventana
		if (bala->getBounds().left >  1920.f || bala->getBounds().left + bala->getBounds().width < 0.f)
		{
			// Elimina la bala en la posicion cont del vector
			delete balas.at(cont); 
			balas.erase(balas.begin() + cont);
			--cont;

			std::cout << "balas: " << balas.size() << "\n";
		}
		++cont;
	}
}

void Submarino::actualizarAtaque()
{
	if (ataqueCooldown < ataqueCooldownMax)
		ataqueCooldown += 0.5f;
}

// Actualiza todo lo relacionado al jugador en el loop del juego
void Submarino::actualizar()
{
	acciones();
	actualizarAtaque();
	actualizarBala();
}

void Submarino::renderBala(sf::RenderTarget* target)
{
	for (auto* bala : balas)
	{
		bala->render(target);
	}
}

void Submarino::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
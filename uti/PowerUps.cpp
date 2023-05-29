#include "PowerUps.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
/*
class Menu
{
public:
    void run()
    {
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "Image Fade");

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("IntroTheme.wav"))
        {
            // Por si no carga el archivo de sonido
            return;
        }

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();

        sf::Texture texture1;
        if (!texture1.loadFromFile("Donkey logo.png"))
        {
            return;
        }

        sf::Texture texture2;
        if (!texture2.loadFromFile("Under.png"))
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
};

int main()
{
    Menu menu;
    menu.run();

    return 0;
}
*/

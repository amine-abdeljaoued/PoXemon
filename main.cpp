
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window", sf::Style::Fullscreen);
    
    
    sf::Vector2u WindowSize;
    WindowSize = window.getSize();
    
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture background;
    if (!background.loadFromFile(resourcePath() + "screen_menu.jpg")) {
        return EXIT_FAILURE;
    }
    
    sf::Sprite background_sprite(background);
    background_sprite.setScale(12, 12);
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "Pt_bag.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite backpack(texture);
    backpack.setPosition(WindowSize.x/6, WindowSize.y/3);
    backpack.setScale(8,8);

    // Create Title
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text title("Backpack", font, 150);
    title.setFillColor(sf::Color::White);
    title.setPosition((WindowSize.x/2)-350, 10);
    
    //Number of item
    sf::Text item("Items: 100/100", font, 40);
    item.setPosition((WindowSize.x/6)+130, 2*(WindowSize.y/3));

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(background_sprite);
        window.draw(backpack);
        
        
        // Draw the string
        window.draw(title);
        window.draw(item);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

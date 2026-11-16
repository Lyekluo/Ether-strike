/*
 * hello_sfml.cpp
 *
 * Step 1 checkpoint: if this program compiles, opens a window, and shows a
 * green circle, your SFML setup is working.
 *
 * Example compile command (you may need extra flags for your setup):
 *   g++ -std=c++20 hello_sfml.cpp -o hello_sfml -lsfml-graphics -lsfml-window -lsfml-system
 */

#include <SFML/Graphics.hpp>
#include <iostream>

// The starter code for Step 2 is written for SFML 3. If this line fails to
// compile, you have SFML 2 installed and need to upgrade.
static_assert(SFML_VERSION_MAJOR >= 3, "This project requires SFML 3.x");

int main() {
    std::cout << "Hello from SFML " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "."
              << SFML_VERSION_PATCH << "!" << std::endl;

    // Open an 800x600 window with a title.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hello, SFML!");
    window.setFramerateLimit(60);

    // A circle with a radius of 100 pixels, filled green.
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({300.f, 200.f});

    // The main loop: runs once per frame until the window is closed.
    while (window.isOpen()) {
        // Handle every event (key presses, mouse clicks, ...) since last frame.
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Every frame: clear the screen, draw everything, then show it.
        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}

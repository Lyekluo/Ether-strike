/*
 * Starter 1: Mini Game
 *
 * A circle that you can move left and right with the arrow keys.
 *
 * Your two TODOs:
 *   TODO 1: Make the circle also move UP and DOWN with the Up/Down arrow keys.
 *   TODO 2: Make the circle change to a different color when you press Space.
 *
 * Compile (you may need extra flags for your setup, as in Step 1):
 *   g++ -std=c++20 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
 */

#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Mini Game");
    window.setFramerateLimit(60);

    // The "player": a circle of radius 30.
    sf::CircleShape player(30.f);
    player.setFillColor(sf::Color::Cyan);
    player.setPosition({370.f, 270.f});

    // How fast the player moves, in pixels per second.
    const float speed = 300.f;

    // A clock lets us measure how much time passed between frames, so the
    // player moves at the same speed no matter how fast your computer is.
    sf::Clock clock;

    while (window.isOpen()) {
        // ---- 1. Handle events -------------------------------------------
        // Events are things that happen ONCE: a key is pressed, the window
        // is closed, the mouse is clicked, etc.
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                // `key` describes which key was just pressed.
                if (key->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }

                // TODO 2: When the Space key is pressed, change the player's
                // fill color to a different color.
                //   Done when: pressing Space visibly changes the circle's color.
            }
        }

        // ---- 2. Update the game state -----------------------------------
        // `dt` is the number of seconds since the last frame (e.g. 0.016).
        float dt = clock.restart().asSeconds();

        // isKeyPressed checks whether a key is being HELD DOWN right now.
        // This is different from the KeyPressed event above, which only
        // fires once when the key first goes down.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.move({-speed * dt, 0.f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.move({speed * dt, 0.f});
        }

        // TODO 1: Make the player move up while the Up arrow key is held, and
        // down while the Down arrow key is held. (Hint: in SFML, the y axis
        // points DOWN, so moving up means a negative y.)
        //   Done when: holding Up/Down smoothly moves the circle up/down.

        // ---- 3. Draw ----------------------------------------------------
        window.clear(sf::Color(30, 30, 40));  // dark blue-gray background
        window.draw(player);
        window.display();
    }

    return 0;
}

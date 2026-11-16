/*
 * Starter 3: Drawing Program
 *
 * Left-click anywhere in the window to stamp a circle there.
 *
 * Your two TODOs:
 *   TODO 1: Right-clicking should stamp a square where you clicked.
 *   TODO 2: Pressing the C key should clear the canvas.
 *
 * Compile (you may need extra flags for your setup, as in Step 1):
 *   g++ -std=c++20 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
 */

#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Drawing Program");
    window.setFramerateLimit(60);

    // Everything the user has drawn so far.
    std::vector<sf::CircleShape> circles;
    std::vector<sf::RectangleShape> squares;

    const float radius = 20.f;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                // `click->position` is where the mouse was, in pixels from the
                // top-left of the window. It's a sf::Vector2i (integers), so
                // we convert it to sf::Vector2f (floats) for positioning shapes.
                sf::Vector2f where(click->position);

                if (click->button == sf::Mouse::Button::Left) {
                    sf::CircleShape circle(radius);
                    circle.setFillColor(sf::Color(255, 120, 80));
                    // Center the circle on the click instead of putting its
                    // top-left corner there.
                    circle.setOrigin({radius, radius});
                    circle.setPosition(where);
                    circles.push_back(circle);
                }

                // TODO 1: If the RIGHT mouse button was pressed, create a
                // sf::RectangleShape square, center it on `where`, and add it
                // to the `squares` vector. (It's already drawn below.)
                //   Done when: right-clicking stamps a square centered on the cursor.
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }

                // TODO 2: If the C key was pressed, erase everything that has
                // been drawn.
                //   Done when: pressing C leaves the window blank, and you can
                //   start drawing again afterward.
            }
        }

        window.clear(sf::Color(245, 240, 230));  // off-white "paper"
        for (const auto& circle : circles) {
            window.draw(circle);
        }
        for (const auto& square : squares) {
            window.draw(square);
        }
        window.display();
    }

    return 0;
}

/*
 * Starter 2: Generative Art
 *
 * Draws a grid of colorful squares whose colors depend on where they are.
 *
 * Your two TODOs:
 *   TODO 1: Give every square an outline.
 *   TODO 2: Rotate each square by an angle that depends on its column.
 *
 * Compile (you may need extra flags for your setup, as in Step 1):
 *   g++ -std=c++20 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
 */

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Generative Art");
    window.setFramerateLimit(60);

    // The grid has `count` x `count` cells, each `cellSize` pixels wide.
    const int count = 10;
    const float cellSize = 80.f;
    const float squareSize = 50.f;

    // Build all of the squares once, up front, and store them in a vector.
    std::vector<sf::RectangleShape> squares;
    for (int row = 0; row < count; row++) {
        for (int col = 0; col < count; col++) {
            sf::RectangleShape square({squareSize, squareSize});

            // Move the square's origin (the point it is positioned and
            // rotated around) from its top-left corner to its center.
            square.setOrigin({squareSize / 2.f, squareSize / 2.f});

            // Place the square at the center of its grid cell.
            square.setPosition({col * cellSize + cellSize / 2.f, row * cellSize + cellSize / 2.f});

            // Pick a color based on the square's position: red increases
            // to the right, blue increases downward. Each channel is 0-255.
            auto red = static_cast<std::uint8_t>(255 * col / (count - 1));
            auto blue = static_cast<std::uint8_t>(255 * row / (count - 1));
            square.setFillColor(sf::Color(red, 100, blue));

            // TODO 1: Give the square an outline that is a few pixels thick
            // and a different color than its fill.
            //   Done when: every square has a clearly visible outline.

            // TODO 2: Rotate the square by an angle that depends on `col`, so
            // that squares further to the right are rotated more. (For
            // example, column 0 is not rotated and each column after that is
            // rotated a few more degrees than the last.)
            //   Done when: the squares visibly tilt more from left to right.

            squares.push_back(square);
        }
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (const auto& square : squares) {
            window.draw(square);
        }
        window.display();
    }

    return 0;
}

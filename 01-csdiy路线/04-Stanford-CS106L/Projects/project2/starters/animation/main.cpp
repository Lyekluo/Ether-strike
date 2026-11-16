/*
 * Starter 4: Animation
 *
 * A ball slides back and forth, bouncing off the left and right walls.
 *
 * Your two TODOs:
 *   TODO 1: Make the ball also move vertically and bounce off the top and
 *           bottom walls.
 *   TODO 2: Make the square in the middle of the window spin continuously.
 *
 * Compile (you may need extra flags for your setup, as in Step 1):
 *   g++ -std=c++20 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
 */

#include <SFML/Graphics.hpp>

int main() {
    const float width = 800.f;
    const float height = 600.f;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Animation");
    window.setFramerateLimit(60);

    // The bouncing ball. Its origin is its center, so getPosition() returns
    // the center of the ball.
    const float radius = 25.f;
    sf::CircleShape ball(radius);
    ball.setFillColor(sf::Color(255, 200, 0));
    ball.setOrigin({radius, radius});
    ball.setPosition({width / 2.f, height / 4.f});

    // The ball's velocity in pixels per second. Right now it only moves
    // horizontally (the y part is 0).
    sf::Vector2f velocity(250.f, 0.f);

    // A square sitting in the middle of the window, centered on its origin.
    sf::RectangleShape square({80.f, 80.f});
    square.setFillColor(sf::Color(80, 160, 255));
    square.setOrigin({40.f, 40.f});
    square.setPosition({width / 2.f, height / 2.f});

    // Measures the time between frames so motion is smooth and consistent.
    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Seconds since the last frame (usually about 1/60).
        float dt = clock.restart().asSeconds();

        // Move the ball: distance = velocity * time.
        ball.move(velocity * dt);

        // Bounce off the left and right walls by flipping the x velocity.
        sf::Vector2f pos = ball.getPosition();
        if (pos.x - radius < 0.f && velocity.x < 0.f) {
            velocity.x = -velocity.x;
        }
        if (pos.x + radius > width && velocity.x > 0.f) {
            velocity.x = -velocity.x;
        }

        // TODO 1: Give the ball a nonzero vertical velocity, and make it
        // bounce off the top and bottom walls the same way it bounces off
        // the left and right walls.
        //   Done when: the ball moves diagonally and stays inside the window,
        //   bouncing off all four walls.

        // TODO 2: Make `square` rotate a little bit every frame so that it
        // spins continuously. Use `dt` so the spin speed doesn't depend on
        // your frame rate.
        //   Done when: the square in the middle spins smoothly and never stops.

        window.clear(sf::Color(20, 20, 30));
        window.draw(square);
        window.draw(ball);
        window.display();
    }

    return 0;
}

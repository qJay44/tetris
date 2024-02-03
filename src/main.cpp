#include "Grid.hpp"

int main() {
  sf::RenderWindow window;
  sf::Font font;
  sf::Clock clock;

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Template text", sf::Style::Close);
  window.setFramerateLimit(90);

  // Font for some test text
  font.loadFromFile("../../src/fonts/Minecraft rus.ttf");

  Block block(L_BLOCK);
  Grid grid(&block);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyReleased)
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          default:
            break;
        }
    }

    grid.update(clock.restart().asSeconds());

    window.clear({20, 20, 20});
    window.draw(grid);
    window.draw(block);
    window.display();
  }

  return 0;
}

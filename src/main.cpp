#include "Block.hpp"

int main() {
  sf::RenderWindow window;
  sf::Font font;
  sf::Clock clock;

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Template text", sf::Style::Close);
  window.setFramerateLimit(90);

  // Font for some test text
  font.loadFromFile("../../src/fonts/Minecraft rus.ttf");

  srand((unsigned)time(NULL));

  Shape shapes[2] = {L_BLOCK, O_BLOCK};
  Block* block = new Block(L_BLOCK);
  Grid grid;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed)
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          case sf::Keyboard::A:
            block->move(grid, {-1, 0});
            break;
          case sf::Keyboard::S:
            block->move(grid, {0, 1});
            break;
          case sf::Keyboard::D:
            block->move(grid, {1, 0});
            break;
          default:
            break;
        }
    }

    if (!block->fall(grid, clock.restart().asSeconds()))
      if (block->getRectangles().front().getPosition().y != 0) {
        grid.update(block->getRectangles());
        delete block; block = new Block(shapes[rand() % 2]);
      }

    window.clear({20, 20, 20});
    window.draw(grid);
    window.draw(*block);
    window.display();
  }

  return 0;
}

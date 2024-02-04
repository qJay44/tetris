#include "Block.hpp"

int main() {
  sf::RenderWindow window;
  sf::Font font;
  sf::Clock clock;
  sf::Clock inputDelay;

  // Setup main window
  window.create(sf::VideoMode(WIDTH, HEIGHT), "Template text", sf::Style::Close);
  window.setFramerateLimit(90);

  // Font for some test text
  font.loadFromFile("../../src/fonts/Minecraft rus.ttf");

  srand((unsigned)time(NULL));

  sf::RectangleShape emptyRect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
  emptyRect.setFillColor(sf::Color::Transparent);
  emptyRect.setOutlineColor({40, 40, 40});
  emptyRect.setOutlineThickness(1.f);

  Shape shapes[2] = {L_BLOCK, O_BLOCK};
  Block* block = new Block(O_BLOCK);
  Grid grid(emptyRect);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
          case sf::Keyboard::Q:
            window.close();
            break;
          default:
            break;
        }
      }
    }
    int d = inputDelay.getElapsedTime().asMilliseconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && d >= 100) {block->move(grid, {-1, 0}); inputDelay.restart();}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && d >= 100) {block->move(grid, {0, 1}); inputDelay.restart();}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && d >= 100) {block->move(grid, {1, 0}); inputDelay.restart();}

    if (!block->fall(grid, clock.restart().asSeconds()))
      if (block->getRectangles().front().getPosition().y != 0) {
        grid.update(block->getRectangles());
        delete block; block = new Block(shapes[1]);
      }

    window.clear({20, 20, 20});
    window.draw(grid);
    window.draw(*block);
    window.display();
  }

  return 0;
}

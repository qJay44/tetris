#include "Block.hpp"

constexpr char inputDelay = 100;

int main() {
  sf::RenderWindow window;
  sf::Font font;
  sf::Clock clock;
  sf::Clock inputDelayClock;

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

  Block* block = new Block();
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
          case sf::Keyboard::R:
            grid.reset();
            delete block; block = new Block();
            break;
          default:
            break;
        }
      }
    }

    int d = inputDelayClock.getElapsedTime().asMilliseconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && d >= inputDelay) {block->move(grid, {-1, 0}); inputDelayClock.restart();}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && d >= inputDelay) {block->move(grid, {0, 1}); inputDelayClock.restart();}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && d >= inputDelay) {block->move(grid, {1, 0}); inputDelayClock.restart();}

    if (!block->fall(grid, clock.restart().asSeconds())) {
      // If fell and it is not the same place as spawned
      if (block->getRectangles().front().getPosition().y != 0) {
        grid.update(block->getRectangles());
        delete block; block = new Block();
      } else {
        grid.reset();
        delete block; block = new Block();
      }
    }

    window.clear({20, 20, 20});
    window.draw(grid);
    window.draw(*block);
    window.display();
  }

  return 0;
}

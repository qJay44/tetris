#include "Grid.hpp"

#define IX(x, y) ((x) + (y) * (COLUMNS))

Grid::Grid(Block* blockPtr) : blockPtr(blockPtr) {
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      rect.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineColor({40, 40, 40});
      rect.setOutlineThickness(1.f);
      rects.push_back(rect);
    }
  }
  rects.reserve(ROWS * COLUMNS);

  matrix.resize(ROWS * COLUMNS);
  matrix.reserve(ROWS * COLUMNS);
}

void Grid::update(float dt) {
  blockPtr->fall(dt);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const sf::RectangleShape r : rects)
    target.draw(r);
}


#include "Grid.hpp"

#define IX(x, y) ((x) + (y) * (COLUMNS))

Grid::Grid() {
  grid.resize(ROWS * COLUMNS);
  grid.reserve(ROWS * COLUMNS);
  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      rect.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineColor({40, 40, 40});
      rect.setOutlineThickness(1.f);
      grid[IX(x, y)] = rect;
    }
  }
}

bool Grid::hasBlockAt(sf::Vector2i pos) const {
  if (pos.x < 0 || pos.x > WIDTH - CELL_SIZE)
    return true;

  if (pos.y < 0 || pos.y > HEIGHT - CELL_SIZE)
    return true;

  pos /= CELL_SIZE;

  return grid[IX(pos.x, pos.y)].getFillColor().toInteger();
}

void Grid::update(const std::list<sf::RectangleShape>& blocks) {
  for (const sf::RectangleShape& rect : blocks) {
    sf::Vector2i pos(rect.getPosition());
    pos.x = pos.x / CELL_SIZE;
    pos.y = pos.y / CELL_SIZE;
    grid[IX(pos.x, pos.y)] = rect;
  }

  for (int i = 0; i < ROWS; i++) {
    std::list<sf::RectangleShape*> rowRects;
    for (int j = 0; j < COLUMNS; j++) {
      // Add row rectangles as long as they colored
      if (grid[IX(j, i)].getFillColor().toInteger())
        rowRects.push_back(&grid[IX(j, i)]);
      else {
        rowRects.clear();
        i++;
        break;
      }
    }
    for (sf::RectangleShape* r : rowRects)
      r->setFillColor(sf::Color::Transparent);
  }

  // TODO: Move block down
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const sf::RectangleShape r : grid)
    target.draw(r);
}


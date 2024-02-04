#include "Grid.hpp"
#include <algorithm>

#define IX(x, y) ((x) + (y) * (COLUMNS))

Grid::Grid(const sf::RectangleShape& emptyRectTemplate) : emptyRectTemplate(emptyRectTemplate) {
  grid.resize(ROWS * COLUMNS);
  grid.reserve(ROWS * COLUMNS);

  for (int x = 0; x < COLUMNS; x++) {
    for (int y = 0; y < ROWS; y++) {
      sf::RectangleShape rect(emptyRectTemplate);
      rect.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
      grid[IX(x, y)] = rect;
    }
  }
}

sf::RectangleShape Grid::createEmptyRect(const sf::Vector2f& pos) {
  sf::RectangleShape r(emptyRectTemplate);
  r.setPosition(pos);

  return r;
}

// Takes cols and rows
bool Grid::hasBlockAt(sf::Vector2i pos) const {
  return grid[IX(pos.x, pos.y)].getFillColor().toInteger();
}

bool Grid::hasBlockAt(int index) const {
  return grid[index].getFillColor().toInteger();
}

void Grid::update(const std::list<sf::RectangleShape>& blocks) {
  for (const sf::RectangleShape& rect : blocks) {
    sf::Vector2i pos(rect.getPosition());
    pos.x = pos.x / CELL_SIZE;
    pos.y = pos.y / CELL_SIZE;
    grid[IX(pos.x, pos.y)] = rect;
  }

  for (int row = 0; row < ROWS; row++) {
    bool clearRow = false;
    for (int col = 0; col < COLUMNS; col++) {
      if (hasBlockAt({col, row})) {
        // Will add only if all rectangles on the row are colored
        clearRow = true;
      } else {
        clearRow = false;
        break;
      }
    }

    if (clearRow) {
      for (int col = 0; col < COLUMNS; col++) {
        grid[IX(col, row)] = createEmptyRect(grid[IX(col, row)].getPosition());
      }

      for (int rowToMove = row; rowToMove > 0; rowToMove--) {
        for (int col = 0; col < COLUMNS; col++) {
          int currRowIndex = IX(col, rowToMove);
          int prevRowIndex = IX(col, rowToMove - 1);
          if (!hasBlockAt(currRowIndex) && hasBlockAt(prevRowIndex)) {
            grid[currRowIndex].setFillColor(grid[prevRowIndex].getFillColor());
            grid[currRowIndex].setOutlineColor(grid[prevRowIndex].getOutlineColor());
            grid[prevRowIndex] = createEmptyRect(grid[prevRowIndex].getPosition());
          }
        }
      }
    }
  }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const sf::RectangleShape r : grid)
    target.draw(r);
}


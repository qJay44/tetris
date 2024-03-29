#include "Grid.hpp"
#include <algorithm>

#define IX(x, y) ((x) + (y) * (COLUMNS))

Grid::Grid(const sf::RectangleShape& emptyRectTemplate) : emptyRectTemplate(emptyRectTemplate) {
  grid.resize(ROWS * COLUMNS);
  grid.reserve(ROWS * COLUMNS);
  sf::Color lineColor(40, 40, 40);

  // Create empty rectangles
  for (int x = 0; x < COLUMNS; x++)
    for (int y = 0; y < ROWS; y++)
      grid[IX(x, y)] = createEmptyRect(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));

  // Create row lines
  for (float y = 1; y < ROWS; y++) {
    lines.append(sf::Vertex({0, y * CELL_SIZE}, lineColor));
    lines.append(sf::Vertex({WIDTH, y * CELL_SIZE}, lineColor));
  }

  // Create column lines
  for (float x = 1; x < COLUMNS; x++) {
    lines.append(sf::Vertex({x * CELL_SIZE, 0}, lineColor));
    lines.append(sf::Vertex({x * CELL_SIZE, HEIGHT}, lineColor));
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

void Grid::update(const std::list<sf::RectangleShape>& block) {
  // Merge the block with grid
  for (const sf::RectangleShape& rect : block) {
    sf::Vector2i pos(rect.getPosition());
    pos.x = pos.x / CELL_SIZE;
    pos.y = pos.y / CELL_SIZE;
    grid[IX(pos.x, pos.y)] = rect;
  }

  for (int row = 0; row < ROWS; row++) {
    // Clear the row only if all columns are colored
    bool clearRow = true;
    for (int col = 0; col < COLUMNS && clearRow; col++)
      clearRow = hasBlockAt({col, row});

    if (clearRow) {
      for (int col = 0; col < COLUMNS; col++)
        grid[IX(col, row)] = createEmptyRect(grid[IX(col, row)].getPosition());

      // After clearing the row make all rectangles above to move down
      for (int rowToMove = row; rowToMove > 0; rowToMove--) {
        for (int col = 0; col < COLUMNS; col++) {
          // Swap the rects //
          sf::RectangleShape& currRect = grid[IX(col, rowToMove)];
          sf::RectangleShape& prevRect = grid[IX(col, rowToMove - 1)];

          currRect.setFillColor(prevRect.getFillColor());
          prevRect = createEmptyRect(prevRect.getPosition());
        }
      }
    }
  }
}

void Grid::reset() {
  for (sf::RectangleShape& rect : grid)
    rect = createEmptyRect(rect.getPosition());
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const sf::RectangleShape r : grid)
    target.draw(r);
  target.draw(lines);
}


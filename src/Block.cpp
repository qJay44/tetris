#include "Block.hpp"

Block::Block() {
  sf::Color color = sf::Color(shape.getColor());
  const int* mat = shape.getMatrix();

  for (int i = 0; i < 16; i++) {
    if (mat[i]) {
      sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      rect.setPosition(sf::Vector2f(initPosition.x + (i % 4) * CELL_SIZE, initPosition.y + (i >> 2) * CELL_SIZE));
      rect.setFillColor(color);
      rects.push_back(rect);
    }
  }
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const sf::RectangleShape& r : rects)
    target.draw(r);
}

void Block::move(const Grid& grid, sf::Vector2i dir) {
  std::list<sf::RectangleShape> nextPosRects;

  // To update block position make sure all rectangles have an empty cell on the next position
  for (sf::RectangleShape rect : rects) {
    sf::Vector2i pos(rect.getPosition());

    pos.x += CELL_SIZE * dir.x;
    if (pos.x < 0 || pos.x >= WIDTH || grid.hasBlockAt(pos / CELL_SIZE))
      return;

    pos.y += CELL_SIZE * dir.y;
    if (pos.y < 0 || pos.y >= HEIGHT|| grid.hasBlockAt(pos / CELL_SIZE))
      return;

    rect.setPosition(sf::Vector2f(pos));
    nextPosRects.push_back(rect);
  }
  rects = nextPosRects;
}

// Only trying to rotate it once
void Block::rotate(const Grid& grid, bool clockwise) {
  // Copy this block properties
  Block nextBlock = *this;
  Shape nextShape = shape;
  const sf::Color& color = rects.front().getFillColor();
  const sf::Vector2f& nextPos = rects.front().getPosition();

  nextBlock.rects.clear();
  nextShape.rotate(clockwise);

  // Create rectangles by the new matrix shape
  const int* mat = nextShape.getMatrix();
  for (int i = 0; i < 16; i++) {
    if (mat[i]) {
      sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      rect.setPosition(sf::Vector2f(nextPos.x + (i % 4) * CELL_SIZE, nextPos.y + (i >> 2) * CELL_SIZE));
      rect.setFillColor(color);
      nextBlock.rects.push_back(rect);
    }
  }

  // Check if new rectangles overlap other rectangles or goes off the screen
  for (const sf::RectangleShape& rect : nextBlock.rects) {
    sf::Vector2i pos(rect.getPosition());
    if (pos.x < 0 || pos.x >= WIDTH  ||
        pos.y < 0 || pos.y >= HEIGHT ||
        grid.hasBlockAt(pos / CELL_SIZE)) return;
  }

  // Apply new propeties to this block
  rects = nextBlock.rects;
  shape.setMatrix(nextShape);
}

bool Block::fall(const Grid& grid, float dt) {
  std::list<sf::RectangleShape> nextPosRects;

  // To update block position make sure all rectangles may fall
  for (sf::RectangleShape rect : rects) {
    sf::Vector2i pos(rect.getPosition());
    pos.y = (pos.y + CELL_SIZE * static_cast<int>(accumulation));

    if (pos.y >= HEIGHT || grid.hasBlockAt(pos / CELL_SIZE))
      return false;

    rect.setPosition(sf::Vector2f(pos));
    nextPosRects.push_back(rect);
  }
  rects = nextPosRects;
  accumulation = accumulation > 1.f ? 0.f : accumulation + dt * SPEED;

  return true;
}

const std::list<sf::RectangleShape>& Block::getRectangles() const {
  return rects;
}


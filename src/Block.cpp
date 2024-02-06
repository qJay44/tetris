#include "Block.hpp"

Block::Block() {
  sf::Color color = sf::Color(shape.getColor());
  const int* mat = shape.getMatrix();

  for (int i = 0; i < 16; i++) {
    if (mat[i]) {
      sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      rect.setPosition(sf::Vector2f(initPosition.x + (i % 4) * CELL_SIZE, initPosition.y + (i >> 2) * CELL_SIZE));
      rect.setFillColor(color);
      rect.setOutlineColor({40, 40, 40});
      rect.setOutlineThickness(1.f);
      rects.push_back(rect);
    }
  }
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
  for (const sf::RectangleShape r : rects)
    target.draw(r);
}

void Block::move(const Grid& grid, sf::Vector2i dir) {
  std::list<sf::RectangleShape> nextPosRects;

  // To update block position make sure all rectangles have an empty cell on the next position
  for (sf::RectangleShape rect : rects) {
    sf::Vector2i pos(rect.getPosition());
    pos.x = pos.x + CELL_SIZE * dir.x;

    if (pos.x < 0 || pos.x > WIDTH - CELL_SIZE || grid.hasBlockAt(pos / CELL_SIZE))
      return;

    pos.y = pos.y + CELL_SIZE * dir.y;

    if (pos.y < 0 || pos.y > HEIGHT - CELL_SIZE || grid.hasBlockAt(pos / CELL_SIZE))
      return;

    rect.setPosition(sf::Vector2f(pos));
    nextPosRects.push_back(rect);
  }
  rects = nextPosRects;
}

bool Block::fall(const Grid& grid, float dt) {
  std::list<sf::RectangleShape> nextPosRects;

  // To update block position make sure all rectangles may fall
  for (sf::RectangleShape rect : rects) {
    sf::Vector2i pos(rect.getPosition());
    pos.y = (pos.y + CELL_SIZE * (int)(accumulation));

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


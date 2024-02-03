#include "pch.h"
#include <vector>

enum Shape {
  L_BLOCK,
};

class Block : public sf::Drawable, public sf::Transformable {
  const sf::Vector2i initPosition{WIDTH / 2, 0};

  sf::Color color;
  std::vector<sf::RectangleShape> rects;
  Shape shape;
  float accumulation = 0.f;

public:
  Block(Shape shape) : shape(shape) {
    int* mat;
    switch (shape) {
      case L_BLOCK:
        mat = new int[16] {
          1, 0, 0, 0,
          1, 0, 0, 0,
          1, 1, 0, 0,
          0, 0, 0, 0
        };
        color = sf::Color::Blue;
    }

    for (int i = 0; i < 16; i++) {
      if (mat[i]) {
        sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        rect.setPosition(sf::Vector2f(initPosition.x + (i % 4) * CELL_SIZE, initPosition.y + (i >> 2) * CELL_SIZE));
        rect.setOutlineColor({200, 200, 200});
        rect.setOutlineThickness(1.f); // Hmm...
        rect.setFillColor(color);
        rects.push_back(rect);
      }
    }

    delete mat;
  }

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (const sf::RectangleShape r : rects)
      target.draw(r);
  }

  void move() {
  }

  void fall(float dt) {
    for (sf::RectangleShape& rect : rects) {
      sf::Vector2f pos = rect.getPosition();
      pos.y = (pos.y + CELL_SIZE * (int)(accumulation));
      rect.setPosition(pos);
    }

    accumulation = accumulation > 1.f ? 0.f : accumulation + dt;
  }
};


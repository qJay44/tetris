#include "pch.h"
#include "Grid.hpp"
#include "Shape.hpp"

class Block : public sf::Drawable, public sf::Transformable {
  const sf::Vector2i initPosition{WIDTH / 2, 0};

  std::list<sf::RectangleShape> rects;
  Shape shape;
  float accumulation = 0.f;

public:
  Block();

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  void move(const Grid& grid, sf::Vector2i dir);

  bool fall(const Grid& grid, float dt);
  const std::list<sf::RectangleShape>& getRectangles() const;
};


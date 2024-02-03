#include "pch.h"
#include <vector>
#include <list>

class Grid : public sf::Drawable, public sf::Transformable {
  std::vector<sf::RectangleShape> grid;

public:
  Grid();

  bool hasBlockAt(sf::Vector2i coords) const;

  void update(const std::list<sf::RectangleShape>& blocks);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


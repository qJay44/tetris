#include "pch.h"
#include <vector>
#include <list>

class Grid : public sf::Drawable, public sf::Transformable {
  const sf::RectangleShape emptyRectTemplate;
  std::vector<sf::RectangleShape> grid;
  sf::VertexArray lines{sf::Lines};

  sf::RectangleShape createEmptyRect(const sf::Vector2f& pos);

public:
  Grid(const sf::RectangleShape& emptyRectTemplate);

  bool hasBlockAt(sf::Vector2i coords) const;

  void update(const std::list<sf::RectangleShape>& block);
  void reset();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#include "Block.hpp"

class Grid : public sf::Drawable, public sf::Transformable {
  std::vector<int> matrix;
  std::vector<sf::RectangleShape> rects;
  Block* blockPtr = nullptr;

public:
  Grid(Block* blockPtr);
  void update(float dt);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


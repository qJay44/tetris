#include "pch.h"
#include <map>
#include <array>

constexpr char matrixSize = 16;

class Shape {
  static const std::map<sf::Uint32, std::array<bool, matrixSize>> matrices;

  const sf::Uint32 shapeIndexColor;
  std::array<bool, matrixSize> matrix;

public:
  Shape();

  void rotate(bool clockwise);
  void setMatrix(const Shape& rhs);

  const sf::Uint32& getColor() const;
  const bool* getMatrix() const;
};


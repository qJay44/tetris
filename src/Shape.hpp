#include "pch.h"
#include <map>

class Shape {
  struct Matrix {
    int m[16];
    void rotate(bool clockwise);
  };

  static const std::map<sf::Uint32, Matrix> matrices;

  const sf::Uint32 shapeIndexColor;
  Matrix matrix;

public:
  Shape();

  void rotate(bool clockwise);
  void setMatrix(const Shape& rhs);

  const sf::Uint32& getColor() const;
  const int* getMatrix() const;
};


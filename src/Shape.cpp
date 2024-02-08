#include "Shape.hpp"
#include <algorithm>
#include <stdio.h>

// Names with a color value
enum Name : sf::Uint32 {
  O_BLOCK = 0xfef84cff,
  I_BLOCK = 0x51e1fcff,
  S_BLOCK = 0xe93d1eff,
  Z_BLOCK = 0x79ae3dff,
  L_BLOCK = 0xf69230ff,
  J_BLOCK = 0xf16eb9ff,
  T_BLOCK = 0x943692ff
};

constexpr sf::Uint32 shapes[7] {
  O_BLOCK,
  I_BLOCK,
  S_BLOCK,
  Z_BLOCK,
  L_BLOCK,
  J_BLOCK,
  T_BLOCK
};

void Shape::setMatrix(const Shape &rhs) {
  matrix = rhs.matrix;
}

const std::map<sf::Uint32, std::array<bool, matrixSize>> Shape::matrices {
  {O_BLOCK, {
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  }},
  {I_BLOCK, {
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0
  }},
  {S_BLOCK, {
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  }},
  {Z_BLOCK, {
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  }},
  {L_BLOCK, {
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0
  }},
  {J_BLOCK, {
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0
  }},
  {T_BLOCK, {
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  }},
};

Shape::Shape() : shapeIndexColor(shapes[rand() % 7]), matrix(matrices.at(shapeIndexColor)) {}

void Shape::rotate(bool clockwise) {
  bool nextMat[matrixSize]{0};
  int farestRect = 0;

  // Matrix transpose
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      nextMat[i * 4 + j] = matrix[j * 4 + i];
      if (nextMat[i * 4 + j])
        farestRect = std::max(farestRect, clockwise ? j : i);
    }
  }

  // Swap first and last sides (columns or rows)
  for (int z = 0; z < 4; z++) {
    int aIndex = clockwise ? z * 4 : z;
    int bIndex = clockwise ? z * 4 + farestRect : farestRect * 4 + z;

    bool a = nextMat[aIndex];
    bool b = nextMat[bIndex];

    nextMat[aIndex] = b;
    nextMat[bIndex] = a;
  }

  // Write result to the matrix
  for (int i = 0; i < matrixSize; i++)
    matrix[i] = nextMat[i];
}

const sf::Uint32& Shape::getColor() const {
  return shapeIndexColor;
}

const bool* Shape::getMatrix() const {
  return matrix.data();
}


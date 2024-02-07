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

void Shape::Matrix::rotate(bool clockwise) {
  bool newMat[16]{0};
  int farestRect = 0;

  if (clockwise) {
    // Matrix transpose
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        newMat[i * 4 + j] = m[j * 4 + i];
        if (newMat[i * 4 + j])
          farestRect = std::max(farestRect, j);
      }
    }
    // Swap first and last columns
    for (int i = 0; i < 4; i++) {
      int left = newMat[i * 4 + 0];
      int right = newMat[i * 4 + farestRect];
      newMat[i * 4 + 0] = right;
      newMat[i * 4 + farestRect] = left;
    }
  } else {
    // TODO:
    // Matrix transpose
    /* for (int i = 0; i < 4; i++) { */
    /*   for (int j = 0; j < 4; j++) { */
    /*     newMat[i * 4 + j] = m[j * 4 + i]; */
    /*     if (newMat[i * 4 + j]) */
    /*       farestRect = std::max(farestRect, i); */
    /*   } */
    /* } */
    /* printf("fRect: %d", farestRect); */

    // Swap first and last rows
    /* for (int j = 0; j < 4; j++) { */
    /*   int above = newMat[0 + j]; */
    /*   int under = newMat[farestRect + j]; */
    /*   newMat[0 + j] = under; */
    /*   newMat[farestRect + j] = under; */
    /* } */

    /* for (int i = 0; i < 4; i++) { */
    /*   for (int j = 0; j < 4; j++) { */
    /*     printf("%d", newMat[i * 4 + j]); */
    /*   } */
    /*   printf("\n"); */
    /* } */
    /* printf("\n"); */
    return;
  }

  // Write result to the matrix
  for (int i = 0; i < 16; i++)
    m[i] = newMat[i];
}

void Shape::setMatrix(const Shape &rhs) {
  matrix = rhs.matrix;
}

const std::map<sf::Uint32, Shape::Matrix> Shape::matrices {
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
  matrix.rotate(clockwise);
}

const sf::Uint32& Shape::getColor() const {
  return shapeIndexColor;
}

const int* Shape::getMatrix() const {
  return matrix.m;
}


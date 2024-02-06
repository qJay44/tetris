#include "Shape.hpp"

const Shape::Name Shape::shapes[7] {
  O_BLOCK,
  I_BLOCK,
  S_BLOCK,
  Z_BLOCK,
  L_BLOCK,
  J_BLOCK,
  T_BLOCK
};

const std::map<Shape::Name, Shape::Matrix> Shape::matrices {
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

Shape::Shape() : shape(shapes[rand() % 7]) {}

sf::Uint32 Shape::getColor() const {
  return shape;
}

const int* Shape::getMatrix() const {
  return matrices.at(shape).m;
}


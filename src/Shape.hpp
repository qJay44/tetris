#include "pch.h"
#include <map>

class Shape {
  // Names with a color value
  enum Name {
    O_BLOCK = 0xfef84cff,
    I_BLOCK = 0x51e1fcff,
    S_BLOCK = 0xe93d1eff,
    Z_BLOCK = 0x79ae3dff,
    L_BLOCK = 0xf69230ff,
    J_BLOCK = 0xf16eb9ff,
    T_BLOCK = 0x943692ff
  };

  struct Matrix {
    int m[16];
  };

  static const Name shapes[7];
  static const std::map<Name, Matrix> matrices;

  const Name shape;

public:
  Shape();

  sf::Uint32 getColor() const; // Return const reference to enum value?
  const int* getMatrix() const;
};


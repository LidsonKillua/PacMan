#include "globals.hpp"

bool operator==(const Position &a, const Position &b)
{
  return a.x == b.x && a.y == b.y;
}
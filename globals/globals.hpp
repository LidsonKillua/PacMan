#pragma once

#define ROWS 16
#define COLS 26

enum Direction
{
  Left,
  Right,
  Up,
  Down,
  Idle
};

struct Position
{
  int x;
  int y;
};

bool operator==(const Position &lhs, const Position &rhs);

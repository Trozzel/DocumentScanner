//
// Created by George Ford on 8/29/21.
//
#include "CVPointMover.h"

using namespace std;

string pointLocToString(PointLoc pl)
{
  string orientation{};
  switch (pl)
  {
  case UPPER_LEFT:
    orientation = "Upper left";
    break;
  case UPPER_RIGHT:
    orientation = "Upper right";
    break;
  case LOWER_RIGHT:
    orientation = "Lower right";
    break;
  case LOWER_LEFT:
    orientation = "Lower left";
    break;
  default:
    break;
  }
  return  orientation;
}
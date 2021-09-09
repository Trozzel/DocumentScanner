//
// Created by George Ford on 9/2/21.
//

#ifndef DOCUMENTSCANNER_CVANCILLARY_H
#define DOCUMENTSCANNER_CVANCILLARY_H

#include "CVPointMover.h"

void on_move(int event, int x, int y, int flags, void* data)
{
  auto* cvpm = static_cast<CVPointMover*>(data);
  cvpm->mouseEventHandler(event,x,y,flags, nullptr);
}

#endif //DOCUMENTSCANNER_CVANCILLARY_H

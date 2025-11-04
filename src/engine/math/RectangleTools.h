#pragma once

#include "Rectangle.h"

typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;

extern const Rectangle RectangleTools_NegativeOne;

void RectangleTools_Write(Rectangle rectangle, BufferWriter* writer);
void RectangleTools_Read(Rectangle* rectangle, BufferReader* reader);

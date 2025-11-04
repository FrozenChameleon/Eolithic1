#include "RectangleTools.h"

const Rectangle RectangleTools_NegativeOne = { -1, -1, 0, 0 };

void RectangleTools_Write(Rectangle rectangle, BufferWriter* writer)
{
	/*writer->WriteInt32(rectangle.X);
	writer->WriteInt32(rectangle.Y);
	writer->WriteInt32(rectangle.Width);
	writer->WriteInt32(rectangle.Height);*/
}
void RectangleTools_Read(Rectangle* rectangle, BufferReader* reader)
{
	rectangle->X = BufferReader_ReadI32(reader);
	rectangle->Y = BufferReader_ReadI32(reader);
	rectangle->Width = BufferReader_ReadI32(reader);
	rectangle->Height = BufferReader_ReadI32(reader);
}

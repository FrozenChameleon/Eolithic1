#include "ImageData.h"

#include "../math/Vectors.h"
#include "../utils/Utils.h"
#include "../io/BufferReader.h"

void ImageData_Init(ImageData* id)
{
	Utils_memset(id, 0, sizeof(ImageData));

	id->mOrigin = Vectors_NegativeOne;
	id->mDepth = 80;
	id->mScaler = 1;
}

/*void OeImageData_WriteIni(std_shared_ptr<OeIniWriter> writer, std_string text)
{
	writer->WriteString(text + TAG_IMAGE, mImage);
	writer->WriteBoolean(text + TAG_IS_ADDITIVE, mIsAdditive);
	writer->WriteSingle(text + TAG_ORIGIN_X, mOrigin.X);
	writer->WriteSingle(text + TAG_ORIGIN_Y, mOrigin.Y);
	writer->WriteInt32(text + TAG_OFFSET_X, mOffset.X);
	writer->WriteInt32(text + TAG_OFFSET_Y, mOffset.Y);
	writer->WriteInt32(text + TAG_ANIMATION_LOOP_POINT, mAnimationLoopPoint);
	writer->WriteBoolean(text + TAG_CAN_ANIMATE, mCanAnimate);
	writer->WriteBoolean(text + TAG_ANIMATION_STOPS, mAnimationStops);
	writer->WriteBoolean(text + TAG_ANIMATION_BLANKS, mAnimationBlanks);
	writer->WriteInt32(text + TAG_FLIP_SPEED, mFlipSpeed);
	writer->WriteInt32(text + TAG_DEPTH, mDepth);
	writer->WriteSingle(text + TAG_INITIAL_ROTATION, mInitialRotation);
	writer->WriteInt32(text + TAG_SCALER, mScaler);
}*/
void ImageData_Read(ImageData* id, BufferReader* br)
{
	BufferReader_ReadString(br, id->mImage, EE_FILENAME_MAX);
	id->mIsAdditive = BufferReader_ReadBoolean(br);
	id->mOrigin.X = BufferReader_ReadFloat(br);
	id->mOrigin.Y = BufferReader_ReadFloat(br);
	id->mOffset.X = BufferReader_ReadI32(br);
	id->mOffset.Y = BufferReader_ReadI32(br);
	id->mAnimationLoopPoint = BufferReader_ReadI32(br);
	id->mCanAnimate = BufferReader_ReadBoolean(br);
	id->mAnimationStops = BufferReader_ReadBoolean(br);
	id->mAnimationBlanks = BufferReader_ReadBoolean(br);
	id->mFlipSpeed = BufferReader_ReadI32(br);
	id->mDepth = BufferReader_ReadI32(br);
	id->mInitialRotation = BufferReader_ReadFloat(br);
	id->mScaler = BufferReader_ReadI32(br);
}
const char* ImageData_ToString(ImageData* id)
{
	return id->mImage;
}
bool ImageData_IsOriginSet(ImageData* id)
{
	if (Vector2_EqualTo(id->mOrigin, Vectors_NegativeOne))
	{
		return false;
	}
	return true;
}

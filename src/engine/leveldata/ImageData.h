#pragma once

#include "../utils/Macros.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../utils/MString.h"
//#include "../utils/OeIniReader.h"
//#include "../utils/OeIniWriter.h"

typedef struct BufferReader BufferReader;

typedef struct ImageData
{
	bool mIsAdditive;
	Vector2 mOrigin;
	Point mOffset;
	int32_t mAnimationLoopPoint;
	bool mCanAnimate;
	bool mAnimationStops;
	bool mAnimationBlanks;
	int32_t mFlipSpeed;
	int32_t mDepth;
	float mInitialRotation;
	char mImage[EE_FILENAME_MAX];
	int32_t mScaler;
} ImageData;

void ImageData_Init(ImageData* id);

//void ImageData_WriteIni(ImageData* id, std::shared_ptr<OeIniWriter> writer, std::string text);
void ImageData_Read(ImageData* id, BufferReader* reader);
const char* ImageData_ToString(ImageData* id);
bool ImageData_IsOriginSet(ImageData* id);
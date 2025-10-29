#pragma once

#include "../math/Point.h"
#include "../math/Vector2.h"
#include "../math/Matrix.h"
#include "../math/Rectangle.h"

typedef struct Camera
{
	int mHingeGateLeft;
	int mHingeGateRight;
	int mHingeGateTop;
	int mHingeGateBottom;
	int mWorldWidth;
	int mWorldHeight;
	float mWorldZoom;
	float mWorldRotation;
	float mCameraSpeed;
	float mNewShakeMul;
	float mCurrentShakeMul;
	bool mIsHingedCamera;
	bool mHingeDualDirectionX;
	bool mHingeDualDirectionY;
	bool mChangedCameraHingeX;
	bool mChangedCameraHingeY;
	bool mIsUpdateDisabled;
	Point mHingeDirection;
	Point mNewShake;
	Point mCurrentShake;
	Vector2 mLastDifference;
	Vector2 mCurrentPosition;
	Vector2 mLastRenderedPosition; //DO NOT USE FOR LOGIC
	Vector2 mTargetPosition;
	Vector2 mHingeSpeedLimit;
} Camera;

extern const float CAMERA_EXTENDED_CAMERA;

void Camera_UpdateLastRenderPosition(Camera* camera);
bool Camera_IsHorizontalTube(const Camera* camera);
bool Camera_IsCameraAtTargetPosition(const Camera* camera);
Vector2 Camera_GetInterpCameraAsVector2(const Camera* camera, double delta);
Matrix Camera_GetInterpCamera(const Camera* camera, float offsetX, float offsetY, double delta, int scale);
float Camera_GetRenderedInterpolatedX(const Camera* camera, double delta);
float Camera_GetRenderedInterpolatedY(const Camera* camera, double delta);
Matrix Camera_GetTranslation(float x, float y, float rotation, float zoom, float width, float height);
void Camera_Resize(Camera* camera, int width, int height);
bool Camera_MoveCameraSomewhereVector2(Camera* camera, bool immediate, Vector2 target, float speed);
bool Camera_MoveCameraSomewhere(Camera* camera, bool immediate, float targetX, float targetY, float speed);
int Camera_GetWidthMul(const Camera* camera, float mul);
int Camera_GetWidth(const Camera* camera);
float Camera_GetWidthFloatMul(const Camera* camera, float mul);
float Camera_GetWidthFloat(const Camera* camera);
int Camera_GetHeightMul(const Camera* camera, float mul);
int Camera_GetHeight(const Camera* camera);
float Camera_GetHeightFloatMul(const Camera* camera, float mul);
float Camera_GetHeightFloat(const Camera* camera);
int Camera_GetLeftMul(const Camera* camera, float mul);
int Camera_GetLeft(const Camera* camera);
float Camera_GetLeftFloatMul(const Camera* camera, float mul);
float Camera_GetLeftFloat(const Camera* camera);
Vector2 Camera_GetUpperLeft(const Camera* camera);
Vector2 Camera_GetUpperLeftMul(const Camera* camera, float mul);
int Camera_GetTopMul(const Camera* camera, float mul);
int Camera_GetTop(const Camera* camera);
float Camera_GetTopFloatMul(const Camera* camera, float mul);
float Camera_GetTopFloat(const Camera* camera);
int Camera_GetRight(const Camera* camera);
int Camera_GetRightMul(const Camera* camera, float mul);
float Camera_GetRightFloatMul(const Camera* camera, float mul);
float Camera_GetRightFloat(const Camera* camera);
int Camera_GetBottom(const Camera* camera);
int Camera_GetBottomMul(const Camera* camera, float mul);
float Camera_GetBottomFloatMul(const Camera* camera, float mul);
float Camera_GetBottomFloat(const Camera* camera);
float Camera_GetCenterXFloat(const Camera* camera);
int Camera_GetCenterX(const Camera* camera);
float Camera_GetCenterYFloat(const Camera* camera);
int Camera_GetCenterY(const Camera* camera);
int Camera_GetX1Mul(const Camera* camera, float mul);
int Camera_GetX1(const Camera* camera);
int Camera_GetY1Mul(const Camera* camera, float mul);
int Camera_GetY1(const Camera* camera);
int Camera_GetX2Mul(const Camera* camera, int gridSizeX, float mul);
int Camera_GetX2(const Camera* camera, int gridSizeX);
int Camera_GetY2Mul(const Camera* camera, int gridSizeY, float mul);
int Camera_GetY2(const Camera* camera, int gridSizeY);
bool Camera_IntersectsCameraRect(const Camera* camera, const Rectangle* rect);
bool Camera_IntersectsCameraRectMul(const Camera* camera, const Rectangle* rect, float mul);
bool Camera_IntersectsCamera(const Camera* camera, int x, int y, int width, int height, float mul);
Rectangle Camera_GetRectangle(const Camera* camera, float mul);
int Camera_GetScreenWidthInTiles(const Camera* camera);
int Camera_GetScreenHeightInTiles(const Camera* camera);
void Camera_Move(Camera* camera, float x, float y);
void Camera_MoveToVector2(Camera* camera, Vector2 pos);
void Camera_MoveTo(Camera* camera, float x, float y);
void Camera_MoveToX(Camera* camera, float x);
void Camera_MoveToY(Camera* camera, float y);
void Camera_SetPositionPoint(Camera* camera, Point pos);
void Camera_SetPositionVector2(Camera* camera, Vector2 pos);
void Camera_SetPosition(Camera* camera, float x, float y);
void Camera_SetHingeDirectionX(Camera* camera, int hingeDirectionX);
void Camera_SetHingeDirectionY(Camera* camera, int hingeDirectionY);
void Camera_SetHingeDualDirectionX(Camera* camera, bool hingeDualDirectionX);
void Camera_SetHingeDualDirectionY(Camera* camera, bool hingeDualDirectionY);
void Camera_SetIsHingedCamera(Camera* camera, bool isHingedCamera);
void Camera_SetHingeSpeedLimit(Camera* camera, float hingeLimitX, float hingeLimitY);
void Camera_SetHingeGateLeft(Camera* camera, int value);
void Camera_SetHingeGateRight(Camera* camera, int value);
void Camera_SetHingeGateTop(Camera* camera, int value);
void Camera_SetHingeGateBottom(Camera* camera, int value);
void Camera_ShakeCameraMul(Camera* camera, float mul, int minX, int maxX, int minY, int maxY);
void Camera_ShakeCamera(Camera* camera, int minX, int maxX, int minY, int maxY);
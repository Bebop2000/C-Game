#ifndef CAMERA_H
#define CAMERA_H
#include "core.h"

typedef struct CameraData{
	vec3 pos;
	vec3 direction;
	vec3 front;
	vec3 target;
	float pitch;
	float yaw;
	bool useDirection;
}CameraData;

CameraData cameraInit();
void createViewMatrix(CameraData camera, mat4* out);
void updateCameraDirection(CameraData* camera);
void moveCameraForwards(CameraData* camera, float mult);
void moveCameraBackwards(CameraData* camera, float mult);
void strafeCameraRight(CameraData* camera, float mult);
void strafeCameraLeft(CameraData* camera, float mult);
void moveCameraDown(CameraData* camera, float mult);

#endif
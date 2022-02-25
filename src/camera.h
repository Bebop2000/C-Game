#ifndef CAMERA_H
#define CAMERA_H
#include "core.h"
#include "../vendor/cglm/mat4.h"
#include "../vendor/cglm/vec3.h"
#include "../vendor/cglm/vec2.h"
#include "../vendor/cglm/affine.h"
#include "../vendor/cglm/cam.h"

typedef struct CameraData{
	vec3 pos;
	vec3 direction;
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
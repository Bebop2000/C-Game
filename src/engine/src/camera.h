#pragma once
#include "core.h"

typedef struct CameraData {
	vec3 cameraPos;
	vec3 cameraTarget;
	vec3 cameraFront;
	float pitch;
	float yaw;
	int useFront;
}CameraData;

CameraData cameraInit();
void createViewMatrix(CameraData camera, mat4* out);
void updateCameraFront(CameraData* camera);
void moveCameraForwards(CameraData* camera, float mult);
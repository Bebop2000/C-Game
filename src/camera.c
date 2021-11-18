#include "camera.h"

static float rad(float val);

CameraData cameraInit() {
	CameraData temp = { {0.0f, 0.0f, 0.0f,}, {0.0f, 0.0f, 0.0f,}, {0.0f, 0.0f, 0.0f,}, 0.0f, 0.0f, 1 };
	return temp;
}

void createViewMatrix(CameraData camera, mat4* out) {
	if(camera.useFront) {
		vec3 up = { 0.0f, 1.0f, 0.0f };
		vec3 cameraTarget;
		glm_vec3_add(camera.cameraFront, camera.cameraPos, cameraTarget);
		glm_lookat(camera.cameraPos, cameraTarget, up, *out);
	}
	else{
		vec3 up = { 0.0f, 1.0f, 0.0f };
		glm_lookat(camera.cameraPos, camera.cameraTarget, up, *out);
	}
}

static float rad(float val) {
	return (val * (float)(M_PI / 180));
}

void updateCameraFront(CameraData* camera) {
	camera->cameraFront[0] = (float)(cos((rad(camera->yaw))) * cos(rad(camera->pitch)));
	camera->cameraFront[1] = (float)sin(rad(camera->pitch));
	camera->cameraFront[2] = (float)(sin(rad(camera->yaw)) * cos(rad(camera->pitch)));
}

void moveCameraForwards(CameraData* camera, float mult) {
	vec3 cameraFrontMult;
	glm_vec3_scale(camera->cameraFront, mult, cameraFrontMult);
	glm_vec3_add(cameraFrontMult, camera->cameraPos, &(camera->cameraPos));
}

void moveCameraBackwards(CameraData* camera, float mult) {
	vec3 cameraFrontMult;
	glm_vec3_scale(camera->cameraFront, mult, cameraFrontMult);
	glm_vec3_sub(camera->cameraPos,cameraFrontMult, &(camera->cameraPos));
}

void strafeCameraRight(CameraData* camera, float mult) {
	vec3 up = {0.0f, 1.0f, 0.0f};
	vec3 normCross;
	vec3 multiplied;
	glm_vec3_crossn(camera->cameraFront, up, normCross);
	glm_vec3_scale(normCross, mult, multiplied);
	glm_vec3_add(camera->cameraPos, multiplied, &(camera->cameraPos));
}

void strafeCameraLeft(CameraData* camera, float mult) {
	vec3 up = {0.0f, 1.0f, 0.0f};
	vec3 normCross;
	vec3 multiplied;
	glm_vec3_crossn(camera->cameraFront, up, normCross);
	glm_vec3_scale(normCross, mult, multiplied);
	glm_vec3_sub(camera->cameraPos, multiplied, &(camera->cameraPos));
	
}
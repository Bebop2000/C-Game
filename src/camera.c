#include "camera.h"

static float rad(float val);

CameraData cameraInit() {
	CameraData temp = {0};
	return temp;
}

void createViewMatrix(CameraData camera, mat4* out) {
	vec3 up = { 0.0f, 1.0f, 0.0f };
	if(camera.useDirection) {
		glm_vec3_add(camera.direction, camera.pos, &camera.target);
		glm_lookat(camera.pos, camera.target, up, *out);
	}
	else{
		glm_lookat(camera.pos, camera.target, up, *out);
	}
}

static float rad(float val) {
	return (val * (float)(M_PI) / 180.0f);
}

void updateCameraDirection(CameraData* camera) {
	camera->direction[0] = (float)(cos((rad(camera->yaw))) * cos(rad(camera->pitch)));
	camera->direction[1] = (float)sin(rad(camera->pitch));
	camera->direction[2] = (float)(sin(rad(camera->yaw)) * cos(rad(camera->pitch)));
}

void moveCameraForwards(CameraData* camera, float mult) {
	if(camera->useDirection ) {
		vec3 cameraDirectionMult;
		glm_vec3_scale(camera->direction, mult, cameraDirectionMult);
		glm_vec3_add(cameraDirectionMult, camera->pos, &(camera->pos));
	}
	else {
		camera->pos[2] += mult;
	}
}

void moveCameraBackwards(CameraData* camera, float mult) {
	if (camera->useDirection) {
		vec3 cameraDirectionMult;
		glm_vec3_scale(camera->direction, mult, cameraDirectionMult);
		glm_vec3_sub(camera->pos,cameraDirectionMult, &(camera->pos));
	}
	else {
		camera->pos[2] -= mult;
	}
}

void strafeCameraRight(CameraData* camera, float mult) {
	if (camera->useDirection) {
		vec3 up = {0.0f, 1.0f, 0.0f};
		vec3 normCross;
		vec3 multiplied;
		glm_vec3_crossn(camera->direction, up, normCross);
		glm_vec3_scale(normCross, mult, multiplied);
		glm_vec3_add(camera->pos, multiplied, &(camera->pos));
	}
	else {
		camera->pos[0] += mult;
	}
}

void strafeCameraLeft(CameraData* camera, float mult) {
	if (camera->useDirection) {
		vec3 up = {0.0f, 1.0f, 0.0f};
		vec3 normCross;
		vec3 multiplied;
		glm_vec3_crossn(camera->direction, up, normCross);
		glm_vec3_scale(normCross, mult, multiplied);
		glm_vec3_sub(camera->pos, multiplied, &(camera->pos));
	}
	else {
		camera->pos[0] -= mult;
	}
}

void moveCameraDown(CameraData* camera, float mult) {
	camera->pos[1] -= mult;
}
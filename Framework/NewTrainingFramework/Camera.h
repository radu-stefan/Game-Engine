#pragma once
#include "../Utilities/utilities.h"

class Camera {
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 right;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;

	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix projectionMatrix;

	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat nearPlane;
	GLfloat farPlane;
	GLfloat fov;
	GLfloat directie;

	static GLfloat deltaTime;

	void moveForward();

	void moveOz();
	void moveOy();
	void moveOx();
	void rotateOx();
	void rotateOy();
	void rotateOz();

	void updateWV();

	Camera();
	GLfloat GetDirectie();
	void SetDirectie(GLfloat dir);
	void SetPosition(Vector4 pos);
	Vector3 GetPosition();
	void SetTarget(Vector4 t);
	Vector3 GetTarget();
	void SetUp(Vector4 u);
	Vector3 GetUp();
	void SetMoveSpeed(GLfloat ms);
	GLfloat GetMoveSpeed();
	void SetRotateSpeed(GLfloat rs);
	GLfloat GetRotateSpeed();
	void SetNear(GLfloat n);
	GLfloat GetNear();
	void SetFar(GLfloat f);
	GLfloat GetFar();
	void SetFov(GLfloat fov);
	GLfloat GetFov();
};
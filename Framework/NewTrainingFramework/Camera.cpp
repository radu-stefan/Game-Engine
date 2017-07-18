#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
GLfloat Camera::deltaTime;

void Camera::moveOz()
{
	Vector3 vectorDeplasare = zAxis * moveSpeed * deltaTime * directie;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWV();

}

void Camera::moveOy()
{
	Vector3 vectorDeplasare = yAxis * moveSpeed * deltaTime * directie;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWV();

}

void Camera::moveOx()
{
	Vector3 vectorDeplasare = xAxis * moveSpeed * deltaTime * directie;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWV();
}

void Camera::rotateOx()
{
	Matrix mRotateOx;
	mRotateOx.SetRotationX(rotateSpeed);
	Vector4 temp = (mRotateOx * Vector4(up, 1.0f)) * worldMatrix;
	up = (Vector3(&temp.x)).Normalize();

	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	temp = (localTarget * mRotateOx) * worldMatrix;
	target = Vector3(&temp.x);

	updateWV();

}

void Camera::rotateOy()
{
	Matrix mRotateOy;
	mRotateOy.SetRotationY(rotateSpeed);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 temp = (localTarget * mRotateOy) * worldMatrix;
	target = Vector3(&temp.x);

	updateWV();
}

void Camera::rotateOz()
{
	Matrix mRotateOz;
	mRotateOz.SetRotationZ(rotateSpeed);
	Vector4 temp = (mRotateOz * Vector4(up, 1.0f)) * worldMatrix;
	up = Vector3(&temp.x).Normalize();

	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	temp = (localTarget * mRotateOz) * worldMatrix;
	target = Vector3(&temp.x);

	updateWV();
}

void Camera::updateWV()
{
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = (Vector3(zAxis.x, zAxis.y, zAxis.z).
		Cross(Vector3(yAxis.x, yAxis.y, yAxis.z))).Normalize();

	Matrix T;
	T.SetTranslation(position.x, position.y, position.z);
	worldMatrix.SetZero();
	viewMatrix.SetZero();
	Matrix R;
	R.m[0][0] = xAxis.x;	R.m[0][1] = xAxis.y;	R.m[0][2] = xAxis.z;	R.m[0][3] = 0;
	R.m[1][0] = yAxis.x;	R.m[1][1] = yAxis.y;	R.m[1][2] = yAxis.z;	R.m[1][3] = 0;
	R.m[2][0] = zAxis.x;	R.m[2][1] = zAxis.y;	R.m[2][2] = zAxis.z;	R.m[2][3] = 0;
	R.m[3][0] = 0;			R.m[3][1] = 0;			R.m[3][2] = 0;			R.m[3][3] = 1;

	Matrix RT = R.Transpose();
	worldMatrix = R * T;
	T.SetTranslation(-position.x, -position.y, -position.z);
	viewMatrix = T * RT;

}


Camera::Camera()
{
	directie = -1;
	zAxis = Vector3(0.0f,0.0f,1.0f);
	yAxis = Vector3(0.0f, 1.0f, 0.0f);
	xAxis = Vector3(1.0f, 0.0f, 0.0f);

	position = Vector3(500.0f,0.0f,0.0f);
	target = Vector3(0.0f, 0.0f, -1.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);

	moveSpeed = 100.0f;
	rotateSpeed = 0.05f;
	nearPlane = 0.02f;
	farPlane = 5000.0f;
	fov = 3.14/3.0f;

	projectionMatrix.SetPerspective( fov, Globals::screenWidth/Globals::screenHeight, nearPlane, farPlane);

	updateWV();
}

GLfloat Camera::GetDirectie() {
	return directie;
}

void Camera::SetDirectie(GLfloat dir) {
	directie = dir;
}

GLfloat Camera::GetRotateSpeed() {
	return rotateSpeed;
}

void Camera::SetRotateSpeed(GLfloat rs) {
	rotateSpeed = rs;
}

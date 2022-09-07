#ifndef CAMERA_H
#define CAMERA_H

#include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/GLFW/glfw3.h"

#include <iostream>
#include <deque>

const float TurnSpeed = 80.0f;

class Camera {
public:
    Camera(glm::vec3 cPos = glm::vec3(0.0f, 0.0f, 0.0f) ):cameraPos(cPos) {};
	~Camera() {};
    void CameraMove(GLFWwindow *window);
    void setDeltaTime();
    void shakewindow();
	//放到轮循中
    
	glm::mat4 CameraView();//得到view矩阵
    void setshake(bool s);//开始抖动
	void MovewithMouse(float xoffset, float yoffset);//获得鼠标移动距离
	void Zoom(float yoffset);//鼠标滚轮放大画面
	glm::mat4 getProjection(float width, float height);//得到projection矩阵
	void ForwardEffect();
	void BackEffect();
	void ZoomRecover();
	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	void FixView(glm::vec3 carPos, glm::vec3 carFront);
	bool isFixed();
	void setFixed(glm::vec3 &carfront) {
		fixed = !fixed;
		yaw = 0;
		FixedYaw = 0;
		pitch = 0;
		lastFrontX.push_back(carfront.x);
		lastFrontZ.push_back(carfront.z);
	}

	float getYaw() {
		return yaw;
	}
	glm::vec3 cameraPos;
//private:
	float currentTime;//当前帧时间
    float lastTime = 0.0f; // 上一帧的时间
	bool shakeflag = true; //用于决定抖动的方向
    bool shake = false; //是否发生抖动
    float yaw = -90.0f;
    float pitch = 0.0f;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -3.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float fov = 80.0f;
	float sensitivity = 0.05;
	bool fixed = false;//固定
	float radius = 1.0f;
	float FixedYaw = 0.0f;
	std::deque<float>lastFrontX;
	std::deque<float>lastFrontZ;
};

#endif

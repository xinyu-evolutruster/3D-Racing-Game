#include <camera.h>

void Camera::setDeltaTime()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

void Camera::CameraMove(GLFWwindow* window)
{
	//Esc
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 2.5f * deltaTime;
	if (!fixed && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (!fixed && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if(!fixed)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		else 
			FixedYaw -= TurnSpeed * deltaTime;

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if(!fixed)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		else
			FixedYaw += TurnSpeed * deltaTime;
	}
	if (!fixed && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	if (!fixed && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	//固定时更新观察角度
	if(fixed){
		cameraFront.x = radius * sin(glm::radians(yaw));
		cameraFront.y = 0;
		cameraFront.z = radius * cos(glm::radians(yaw));
		cameraFront = glm::normalize(cameraFront);
	}
}

void Camera::setshake(bool s) {
	shake = s;
}

void Camera::MovewithMouse(float xoffset, float yoffset) {
	if (!fixed) {
		yaw += xoffset * sensitivity;
		pitch += yoffset * sensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}

void Camera::shakewindow() {
	static float lastShakeTime = 0.0f;
	if (shake && (currentTime-lastShakeTime) > 0.1f ) {
		static float sign = -1.0f;
		if (shakeflag) {
			sign = -sign;
			cameraPos.x -= 1.5f * deltaTime;
			cameraPos.y += sign * 1.0f * deltaTime;
		}
		else {
			cameraPos.x += 1.5f * deltaTime;
			cameraPos.y += sign * 1.0f * deltaTime;
		}
		shakeflag = !shakeflag;
		lastShakeTime = currentTime;
	}
}

void Camera::Zoom(float yoffset) {
	if (fov >= 60.0f && fov <= 100.0f)
		fov -= yoffset;
	if (fov <= 60.0f)
		fov = 60.0f;
	if (fov >= 100.0f)
		fov = 100.0f;
}

glm::mat4 Camera::getProjection(float width, float height) {
	return glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
}

glm::mat4 Camera::CameraView() {
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ForwardEffect()
{
	if (fov >= 70.0f)
		fov -= 0.2f;
}

void Camera::BackEffect()
{
	if (fov <= 90.0f)
		fov += 0.2f;
}

void Camera::ZoomRecover()
{
	if (fov < 80.0f)
		fov += 0.02f;
	if (fov > 80.0f)
		fov -= 0.02f;
}

void Camera::FixView(glm::vec3 carPos, glm::vec3 carFront) {
	if (fixed) {
		float sumX = 0, sumZ = 0;
		for (auto p : lastFrontX)
			sumX += p;
		for (auto p : lastFrontZ)
			sumZ += p;
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(FixedYaw), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec4 tempFront = glm::vec4((carFront.x + sumX/lastFrontX.size()) / 2.0f,\
			carFront.y, (carFront.z + sumZ/lastFrontZ.size()) / 2.0f, 1.0f);

		tempFront = trans * tempFront;
		cameraFront = glm::vec3(tempFront.x, tempFront.y, tempFront.z);
		cameraPos.x = carPos.x - 5.2f * tempFront.x;
		cameraPos.z = carPos.z - 5.2f * tempFront.z;
		cameraPos.y = 2.2f;
		lastFrontX.push_back(carFront.x);
		lastFrontZ.push_back(carFront.z);
		while (lastFrontX.size() > 25) {
			lastFrontX.pop_front();
			lastFrontZ.pop_front();
		}
	}
}

bool Camera::isFixed() {
	return fixed;
}
#ifndef CAR_H
#define CAR_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>


enum Direction {
    CAR_FORWARD,
    CAR_BACKWARD,
    CAR_LEFT,
    CAR_RIGHT
};

class Car {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    queue<float> HistoryYaw;
    queue<glm::vec3> HistoryPosition;
    glm::vec3 DelayPosition;
	float Yaw;
	int DelayFrameNum = 12;
	float DelayYaw;
    float Speed;
    float AngularVelocity;
	float Acceleration;
	float StaticAcceleration;
	float MaxSpeed;
    Car(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f))
        : Speed(0.0f)
        , AngularVelocity(100.0f)
        , Yaw(-60.0f)
        , DelayYaw(0.0f)
		, Acceleration(8.0f)
		, StaticAcceleration(5.0f)
		, MaxSpeed(35.0f)
		, Position(position)
    {
        
        updateFront();
    }
	void CarInit(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
		Speed = 0.0f;
		Yaw = -60.0f;
		DelayYaw = 0.0f;
		while(HistoryPosition.size())
			HistoryPosition.pop();
		while (HistoryYaw.size())
			HistoryYaw.pop();
		Position = position;
		updateFront();
	}
    glm::vec3 getPosition()
    {
        return Position;
    }

    float getYaw()
    {
        return Yaw;
    }

    float getDelayYaw()
    {
        return DelayYaw;
    }

    float getMidValYaw()
    {
        return (DelayYaw + Yaw) / 2;
    }

    glm::vec3 getMidValPosition()
    {
        return (DelayPosition + Position) / 2.0f;
    }    

    glm::mat4 GetViewMatrix(glm::vec3 cameraPosition)
    {
        return glm::lookAt(cameraPosition, Position, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // 接受键盘输入
    void ProcessKeyboard(Direction direction, float deltaTime)
    {
		if (direction == CAR_FORWARD) {
			if(Speed<MaxSpeed)
			Speed += Acceleration * deltaTime;
			Position += Front * Speed * deltaTime;
		}
		if (direction == CAR_BACKWARD) {
			if (Speed > (-1)*MaxSpeed)
			Speed -= Acceleration * deltaTime;
			Position += Front * Speed * deltaTime;
		}
        if (direction == CAR_LEFT)
            Yaw += AngularVelocity * deltaTime;
        if (direction == CAR_RIGHT)
            Yaw -= AngularVelocity * deltaTime;
		if (Position.x > 118.0)Position.x = 118.0;
		if (Position.z > 225.0)Position.z = 225.0;
		if (Position.x < -107.0)Position.x = -107.0;
		if (Position.z <-165.0)Position.z = -165.0;
		updateFront();
    }
	void ProcessKeyboard_static(float deltaTime) {
		if (Speed > 0 && Speed - StaticAcceleration * deltaTime > 0) {
			Speed -= StaticAcceleration * deltaTime;
			Position += Front * Speed * deltaTime;
		}
		else if(Speed < 0 && Speed + StaticAcceleration * deltaTime < 0) {
			Speed += StaticAcceleration * deltaTime;
			Position += Front * Speed * deltaTime;
		}
		else if (Speed < 0 && Speed + StaticAcceleration * deltaTime > 0) {
			Speed=0;
			Position += Front * Speed * deltaTime;
		}
		else if (Speed > 0 && Speed - StaticAcceleration * deltaTime < 0) {
			Speed=0;
			Position += Front * Speed * deltaTime;
		}
		if (Position.x > 118.0)Position.x = 118.0;
		if (Position.z > 225.0)Position.z = 225.0;
		if (Position.x < -107.0)Position.x = -107.0;
		if (Position.z < -165.0)Position.z = -165.0;
		updateFront();
	}

   
    void UpdateDelayYaw()
    {
        HistoryYaw.push(Yaw);
        while (HistoryYaw.size() > DelayFrameNum) {
            HistoryYaw.pop();
        }
        DelayYaw = HistoryYaw.front();
    }

    // 更新DalayYaw
    void UpdateDelayPosition()
    {
        HistoryPosition.push(Position);
        while (HistoryPosition.size() > DelayFrameNum) {
            HistoryPosition.pop();
        }
        DelayPosition = HistoryPosition.front();
    }

private:
    // 计算新的 Front 向量
    void updateFront()
    {
        glm::vec3 front;
        front.x = -sin(glm::radians(getDelayYaw()));
        front.y = 0.0f;
        front.z = -cos(glm::radians(getDelayYaw()));
        Front = glm::normalize(front);
    }
};

#endif
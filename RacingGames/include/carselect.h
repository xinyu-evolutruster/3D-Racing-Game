#pragma once
#ifndef _CARSELECT_H
#define _CARSELECT_H
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/model.h>
#include <learnopengl/shader_m.h>

#include <car.h>
#include <iostream>
#include <gl/glut.h>
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "assimp.lib")
#define BITMAP_ID 0x4D42
void CarSelectInit(int carshaderProgram) {
	const char* carselectvertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 transform,view3,projection3;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =projection3*view3*transform*vec4(aPos,1.0);\n"
		"}\0";

	const char* carselectfragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";
	int carvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(carvertexShader, 1, &carselectvertexShaderSource, NULL);
	glCompileShader(carvertexShader);

	int carfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(carfragmentShader, 1, &carselectfragmentShaderSource, NULL);
	glCompileShader(carfragmentShader);

	glAttachShader(carshaderProgram, carvertexShader);
	glAttachShader(carshaderProgram, carfragmentShader);
	glLinkProgram(carshaderProgram);

}
GLuint BgInit_1(int bgshaderProgram) {
	const char* bgfragmentShaderSource_2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D bgtexture2;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(bgtexture2, outTexcoord);\n"
		"}\n\0";


	const char* bgvertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 inTexcoord;\n"
		"uniform mat4 view,projection;\n"
		"out vec2 outTexcoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =projection*view*vec4(aPos,1.0);\n"
		"   outTexcoord = vec2(inTexcoord.x, inTexcoord.y);\n"
		"}\0";

	const char* bgfragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D bgtexture;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(bgtexture, outTexcoord);\n"
		"}\n\0";



	int bgvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(bgvertexShader, 1, &bgvertexShaderSource, NULL);
	glCompileShader(bgvertexShader);

	int bgfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(bgfragmentShader, 1, &bgfragmentShaderSource, NULL);
	glCompileShader(bgfragmentShader);

	;
	glAttachShader(bgshaderProgram, bgvertexShader);
	glAttachShader(bgshaderProgram, bgfragmentShader);
	glLinkProgram(bgshaderProgram);


	unsigned int bgtexture;
	glGenTextures(1, &bgtexture);
	glBindTexture(GL_TEXTURE_2D, bgtexture);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("asset/pictures/carselect1.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glUseProgram(bgshaderProgram);
	glUniform1i(glGetUniformLocation(bgshaderProgram, "bgtexture"), 0);

	return bgtexture;
}
GLuint BgInit_2(int bgshaderProgram2) {
	const char* bgfragmentShaderSource_2 = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D bgtexture2;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(bgtexture2, outTexcoord);\n"
		"}\n\0";


	const char* bgvertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 inTexcoord;\n"
		"uniform mat4 view,projection;\n"
		"out vec2 outTexcoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =projection*view*vec4(aPos,1.0);\n"
		"   outTexcoord = vec2(inTexcoord.x, inTexcoord.y);\n"
		"}\0";

	const char* bgfragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D bgtexture;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(bgtexture, outTexcoord);\n"
		"}\n\0";


	int bgvertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(bgvertexShader2, 1, &bgvertexShaderSource, NULL);
	glCompileShader(bgvertexShader2);

	int bgfragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(bgfragmentShader2, 1, &bgfragmentShaderSource_2, NULL);
	glCompileShader(bgfragmentShader2);


	glAttachShader(bgshaderProgram2, bgvertexShader2);
	glAttachShader(bgshaderProgram2, bgfragmentShader2);
	glLinkProgram(bgshaderProgram2);


	unsigned int bgtexture2;
	glGenTextures(1, &bgtexture2);
	glBindTexture(GL_TEXTURE_2D, bgtexture2);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data2 = stbi_load("asset/pictures/carselect2.jpg", &width, &height, &nrChannels, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glUseProgram(bgshaderProgram2);
	glUniform1i(glGetUniformLocation(bgshaderProgram2, "bgtexture2"), 1);

	return bgtexture2;
}

void Drawcarselect1(GLuint bgtexture, GLuint bgshaderProgram, GLuint bgVAO, Shader carShader_1, Model ourModel_1, GLFWwindow* window) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bgtexture);

	glUseProgram(bgshaderProgram);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -70.0f));
	//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1000.0f, -1000.0f);
	projection = glm::perspective(glm::radians(1.5f), (float)1300 / (float)1200, 0.01f, 100.0f);
	GLint viewLoc = glGetUniformLocation(bgshaderProgram, "view");
	GLint projLoc = glGetUniformLocation(bgshaderProgram, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


	glBindVertexArray(bgVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	carShader_1.use();
	glm::mat4 projection2;
	//projection2 = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
	projection2 = glm::perspective(glm::radians(60.0f), (float)1500 / (float)800, 0.01f, 100.0f);
	glm::mat4 view2 = glm::mat4(1.0f);
	view2 = glm::translate(view2, glm::vec3(16.5f, -12.5f, -53.0f));
	view2 = glm::scale(view2, glm::vec3(0.03f, 0.03f, 0.03f));
	carShader_1.setMat4("projection", projection2);
	carShader_1.setMat4("view", view2);

	glm::mat4 model = glm::mat4(1.0f);

		// it's a bit too big for our scene, so scale it down
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, +100.0f)); // translate it down so it's at the center of the scene
	model = glm::rotate(model, 1 * (float)glfwGetTime() / 2, glm::vec3(-0.0f, 1.0f, 0.0f));
	carShader_1.setMat4("model", model);
	ourModel_1.Draw(carShader_1);
}
void Drawcarselect2(GLuint bgtexture2, GLuint bgshaderProgram2, GLuint bgVAO2, Shader carShader_1, Model ourModel_2, GLFWwindow* window) {
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bgtexture2);
	glUseProgram(bgshaderProgram2);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -70.0f));
	//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1000.0f, -1000.0f);
	projection = glm::perspective(glm::radians(1.5f), (float)1300 / (float)1200, 0.01f, 100.0f);
	GLint viewLoc = glGetUniformLocation(bgshaderProgram2, "view");
	GLint projLoc = glGetUniformLocation(bgshaderProgram2, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(bgVAO2);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	carShader_1.use();
	glm::mat4 projection2;
	//projection2 = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
	projection2 = glm::perspective(glm::radians(60.0f), (float)1500 / (float)800, 0.01f, 100.0f);
	glm::mat4 view2 = glm::mat4(1.0f);
	view2 = glm::translate(view2, glm::vec3(16.5f, -12.5f, -60.0f));
	carShader_1.setMat4("projection", projection2);
	carShader_1.setMat4("view", view2);

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));	// it's a bit too big for our scene, so scale it down
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, +100.0f)); // translate it down so it's at the center of the scene
	model = glm::rotate(model, 1 * (float)glfwGetTime() / 2, glm::vec3(-0.0f, 1.0f, 0.0f));
	carShader_1.setMat4("model", model);
	ourModel_2.Draw(carShader_1);
}


#endif // !_CARSELECT_H



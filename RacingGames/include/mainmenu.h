#pragma once
#ifndef _MAINMENU_H
#define _MAINMENU_H
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
GLuint MenuInit(int menushaderProgram) {
	const char* menuvertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 inTexcoord;\n"
		"out vec2 outTexcoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =vec4(aPos,1.0);\n"
		"   outTexcoord = vec2(inTexcoord.x, inTexcoord.y);\n"
		"}\0";

	const char* menufragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D menutexture;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(menutexture, outTexcoord);\n"
		"}\n\0";

	float bgvertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};


	int menuvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(menuvertexShader, 1, &menuvertexShaderSource, NULL);
	glCompileShader(menuvertexShader);

	int menufragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(menufragmentShader, 1, &menufragmentShaderSource, NULL);
	glCompileShader(menufragmentShader);

	glAttachShader(menushaderProgram, menuvertexShader);
	glAttachShader(menushaderProgram, menufragmentShader);
	glLinkProgram(menushaderProgram);


	GLuint menutexture;
	glGenTextures(1, &menutexture);
	glBindTexture(GL_TEXTURE_2D, menutexture);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* menudata = stbi_load("asset/pictures/menu.jpg", &width, &height, &nrChannels, 0);
	if (menudata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, menudata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glUseProgram(menushaderProgram);
	glUniform1i(glGetUniformLocation(menushaderProgram, "menutexture"), 3);
	return menutexture;

}

GLuint WinInit(int winshaderProgram) {
	const char* winvertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 inTexcoord;\n"
		"out vec2 outTexcoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =vec4(aPos,1.0);\n"
		"   outTexcoord = vec2(inTexcoord.x, inTexcoord.y);\n"
		"}\0";

	const char* winfragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D wintexture;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(wintexture, outTexcoord);\n"
		"}\n\0";

	float bgvertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};


	int winvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(winvertexShader, 1, &winvertexShaderSource, NULL);
	glCompileShader(winvertexShader);

	int winfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(winfragmentShader, 1, &winfragmentShaderSource, NULL);
	glCompileShader(winfragmentShader);

	glAttachShader(winshaderProgram, winvertexShader);
	glAttachShader(winshaderProgram, winfragmentShader);
	glLinkProgram(winshaderProgram);


	GLuint wintexture;
	glGenTextures(1, &wintexture);
	glBindTexture(GL_TEXTURE_2D, wintexture);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* windata = stbi_load("asset/pictures/win2.jpg", &width, &height, &nrChannels, 0);
	if (windata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, windata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glUseProgram(winshaderProgram);
	glUniform1i(glGetUniformLocation(winshaderProgram, "wintexture"), 4);
	return wintexture;

}


GLuint HelpInit(int helpshaderProgram) {
	const char* helpvertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 inTexcoord;\n"
		"out vec2 outTexcoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =vec4(aPos,1.0);\n"
		"   outTexcoord = vec2(inTexcoord.x, inTexcoord.y);\n"
		"}\0";

	const char* helpfragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 outTexcoord;\n"
		"uniform sampler2D helptexture;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(helptexture, outTexcoord);\n"
		"}\n\0";

	float bgvertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};


	int helpvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(helpvertexShader, 1, &helpvertexShaderSource, NULL);
	glCompileShader(helpvertexShader);

	int helpfragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(helpfragmentShader, 1, &helpfragmentShaderSource, NULL);
	glCompileShader(helpfragmentShader);

	glAttachShader(helpshaderProgram, helpvertexShader);
	glAttachShader(helpshaderProgram, helpfragmentShader);
	glLinkProgram(helpshaderProgram);


	GLuint helptexture;
	glGenTextures(1, &helptexture);
	glBindTexture(GL_TEXTURE_2D, helptexture);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* helpdata = stbi_load("asset/pictures/help2.jpg", &width, &height, &nrChannels, 0);
	if (helpdata)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, helpdata);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glUseProgram(helpshaderProgram);
	glUniform1i(glGetUniformLocation(helpshaderProgram, "helptexture"), 5);
	return helptexture;

}


void Drawmainmenu(GLuint menutexture, GLuint menushaderProgram, GLuint menuVAO, GLFWwindow* window) {


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, 1500, 800);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, menutexture);

	glUseProgram(menushaderProgram);
	glBindVertexArray(menuVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Swap the screen buffers

}

void Drawwin(GLuint menutexture, GLuint menushaderProgram, GLuint menuVAO, GLFWwindow* window) {


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, 1500, 800);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, menutexture);

	glUseProgram(menushaderProgram);
	glBindVertexArray(menuVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Swap the screen buffers
}


	void Drawhelp(GLuint menutexture, GLuint menushaderProgram, GLuint menuVAO, GLFWwindow * window) {


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glViewport(0, 0, 1500, 800);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, menutexture);

		glUseProgram(menushaderProgram);
		glBindVertexArray(menuVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the screen buffers

	}
#endif // !_MAINMENU_H



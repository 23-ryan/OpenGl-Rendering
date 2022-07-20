// consider OpenGl as state machine.

// get vertexShader and fragmentShader form the end of this file, 
// and place the corresponding shaders into the corresponding file for the shaders 

#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shader.h"


#define PI 3.14159f

void framebuffer_size_callback(GLFWwindow*, int, int);
void keyCallback(GLFWwindow*, int, int, int, int);


int main() {


	glfwInit(); // descriptable by name.

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // sets the GLFW version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // sets the GLFW version

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //??

	//Create window
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGl", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to load window" << std::endl;
		glfwTerminate(); // terminate GLFW if window is not created.
		return -1;
	}
	// make the window "window" as the current context.
	glfwMakeContextCurrent(window);

	// Load Glad, to render colors, otherwise it wouldn't be possible.
	gladLoadGL();

	// to change the rendering after the window size change.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	Shader ourShader("shader.vs", "shader.fs");

	float R = 0.5f;
	float Th = PI / 2;

	// *Normalized* device co-ordinates as float array.
	//float vertices[] = {
	//	// vertices          //color
	//	R*cos(Th), R*sin(Th), 0.0f,                             1.0f, 0.0f, 0.0f,
	//	R*cos(Th + 2 * PI / 3), R*sin(Th + 2 * PI / 3), 0.0f,   0.0f, 1.0f, 0.0f,
	//	R*cos(Th - 2 * PI / 3), R*sin(Th - 2 * PI / 3), 0.0f,   0.0f, 0.0f, 1.0f
	//};

	float vertices[] = {
		R,  0.0f,         1.0f, 0.0f, 0.0f,
		R,  2 * PI / 3,	  0.0f, 1.0f, 0.0f,
		R, -2 * PI / 3,	  0.0f, 0.0f, 1.0f
	};


	unsigned int VBO;
	unsigned int VAO;
	//unsigned int EBO;

	// bind the Vertex Array Object first, then bindand set vertex buffer(s), and then configure vertex attributes(s).
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// for the location attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//for the color attribute
	//the last element specifies the offset--> space before the required data. --> which in this case are colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

	// you have to enable the vertexAttribPointer before using it, 
	// according to the correct starting location.
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// To disable filling inside the polygon rendered.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float x = 0.0f, y = 0.001f, Tx = PI / 2, Ty = 0.0005f;

	// render loop
	while (!glfwWindowShouldClose(window)) {

		// input
		glfwSetKeyCallback(window, keyCallback);

		//rendering commands here
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // 
		glClear(GL_COLOR_BUFFER_BIT); // Clear --> fill {as i understand} of course its not correct.

		// using the shader program to render.
		if (Tx >= 2 * PI) { Tx = 0; }
		if (x + R * cos(Tx) >= 1.0f
			|| x + R * cos(Tx + 2 * (PI / 3)) >= 1.0f
			|| x + R * cos(Tx - 2 * (PI / 3)) >= 1.0f
			|| x + R * cos(Tx + PI) >= 1.0f
			|| x + R * cos(Tx + PI + 2 * (PI / 3)) >= 1.0f
			|| x + R * cos(Tx + PI - 2 * (PI / 3)) >= 1.0f)
		{
			//std::cout << x + R * cos(Tx) << "\n";
			//std::cout << x + R * cos(Tx + 2*(PI/3)) << "\n";
			//std::cout << x + R * cos(Tx - 2* (PI/3)) << "\n" << std::endl;
			y = -abs(y);
		}
		else if (x + R * cos(Tx + PI) <= -1.0f
			|| x + R * cos(Tx + PI + 2 * (PI / 3)) <= -1.0f
			|| x + R * cos(Tx + PI - 2 * (PI / 3)) <= -1.0f
			|| x + R * cos(Tx) <= -1.0f
			|| x + R * cos(Tx + 2 * (PI / 3)) <= -1.0f
			|| x + R * cos(Tx - 2 * (PI / 3)) <= -1.0f)
		{
			y = abs(y);
		}

		ourShader.use();
		ourShader.setFloat("offset", x);
		ourShader.setFloat("Th", Tx + PI);

		// specifying which data to use.
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ourShader.setFloat("offset", x);
		ourShader.setFloat("Th", Tx);

		// specifying which data to use.
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// update params
		x += y;
		Tx += Ty;
	}

	glDeleteVertexArrays(1, &VAO);
	/*glDeleteBuffers(1, &VBO);*/
	ourShader.deleteProgram();

	glfwTerminate();
	return 0;
}

// To continue rendering the color over the new window size and not just the initial size.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // specifies the location and the size of window to render.
	glfwSwapBuffers(window); // To eliminate any delay in rendering after resizing the window.
}

// to callback function to process the input and print that, this callback function will be called by the 
//	function "glfwSetKeyCallback()", whcih takes this callback function as argument along with the context window.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	else std::cout << char(key) << std::endl;
}


// vertex Shader
/*
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float offset;
uniform float Th;

void main()
{
	gl_Position = vec4(aPos.x*cos(Th + aPos.y) + offset, aPos.x*sin(Th + aPos.y), 0.0f, 1.0f);
	ourColor = aColor;
}
*/

// fragment Shader
/*
#version 330 core

out vec4 FragColor;
in vec3 ourColor;

void main(){
	FragColor = vec4(ourColor, 1.0f);
}

*/

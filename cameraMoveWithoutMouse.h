// get the shader from hthe end of this file, 
// and place those into the corresponding shader files


#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image.h"

float mixValue = 0.2f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float lastFrame = 0.0f, deltaTime = 0.0f;



void framebuffer_size_callback(GLFWwindow*, int, int);
void keyCallback(GLFWwindow*, int, int, int, int);
void changeMergeTextureParam(bool);

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

	// activating the depth test
	glEnable(GL_DEPTH_TEST);

	Shader ourShader("shader.vs", "shader.fs");

	// *Normalized* device co-ordinates as float array.

	// the texture coordinates are from 0.0 to 1.0 but if u specify a larger value,
	// then it tends to wrap according to the method specified.
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	//unsigned int indices[]{
	//	0, 1, 3,
	//	1, 2, 3
	//};

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

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// for the location attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//for the color attribute
	//the last element specifies the offset--> space before the required data. --> which in this case are colors
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	// you have to enable the vertexAttribPointer before using it, 
	// according to the correct starting location.
	//glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// load and create a texture 
	 // -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// flip the image
	stbi_set_flip_vertically_on_load(true);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture!" << std::endl;
	}
	stbi_image_free(data);


	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	// load image, create texture and generate mipmaps
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		// RGBA channel for png files.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture!" << std::endl;
	}
	stbi_image_free(data);


	// Note the order of operations first the scaling will happen then rotation.
	// think about the matrix multiplication

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	glm::mat4 model, view, proj;
	view = glm::mat4(1.0);
	proj = glm::mat4(1.0);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
	ourShader.setInt("ourTexture1", 1);

	proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
	// To disable filling inside the polygon rendered.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FIgLL);

	ourShader.use();
	ourShader.setMat4("proj", proj);

	float radius = 30.0f;
	float camX, camZ;

	float currentFrame;

	// render loop
	while (!glfwWindowShouldClose(window)) {

		// input
		glfwSetKeyCallback(window, keyCallback);

		//rendering commands here
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear --> fill {as i understand} of course its not correct. // Now I get it, its clearing the buffer from the previous rendered frame.


		// bind the texture // maybe, its also setting the value of the uniform variabe sampler2D 
		glActiveTexture(GL_TEXTURE0);  // activating the  textire unit first before binding.
		glBindTexture(GL_TEXTURE_2D, texture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// render container.

		// defining the view matrix
		//camX = radius * cos((float)glfwGetTime());
		//camZ = radius * sin((float)glfwGetTime());

		//cameraPos = glm::vec3(camX, 0.0f, camZ);
		//Target = glm::vec3(0.0f, 0.0f, 0.0f);
		//cameraDirection = glm::normalize(cameraPos - Target);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		ourShader.use();
		ourShader.setMat4("view", view);
		// defining the model matrix to render rotatiing objects.
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			//maintaining deltaTime
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;


			ourShader.use();
			model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			if (false) {
				model = glm::rotate(model, (float)glm::radians(20.0f * i), glm::vec3(0.5f, 1.0f, 0.0f));
			}
			else {
				model = glm::rotate(model, (float)glfwGetTime() * (float)glm::radians(20.0f) * 2 * i, glm::vec3(0.5f, 1.0f, 0.0f));
			}
			ourShader.setMat4("model", model);
			ourShader.setFloat("varMix", mixValue);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			//glBindVertexArray(0);
		}

		// 36 vertices ==> 6(face) * 2(traingles per face) * 3(traingle vertices)

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
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
	const float cameraSpeed = 10000.0f * deltaTime; // adjust accordingly;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraFront * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraFront * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraUp, cameraFront)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		changeMergeTextureParam(true);

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		changeMergeTextureParam(false);

}

void changeMergeTextureParam(bool signPositive) {

	if (!(abs(mixValue - 1.0f) <= 0.0001f) && signPositive) {
		mixValue += 0.1f;
	}
	else if (!(abs(mixValue - 0.0f) <= 0.0001f) && !signPositive) {
		mixValue -= 0.1f;
	}
	return;
}


// vertex shader
/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
void main()
{
   gl_Position = vec4(aPos, 1.0f);
   ourColor = aColor;
   TexCoord = aTexCoord;
}
*/



// fragment shader
/*
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;

void main(){
	FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 0.3);
}
*/

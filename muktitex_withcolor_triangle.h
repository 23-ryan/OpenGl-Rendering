

#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shader.h"
#include "stb_image.h"


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

	// *Normalized* device co-ordinates as float array.
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	//};

	float vertices[] = {
		// vertices				// colors				// texture coord
		 0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,		0.5f, 1.0f,
		-0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,		0.0f, 0.5f,
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.5f
	};

	unsigned int indices[]{
		0, 1, 2,
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	// bind the Vertex Array Object first, then bindand set vertex buffer(s), and then configure vertex attributes(s).
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// for the location attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//for the color attribute
	//the last element specifies the offset--> space before the required data. --> which in this case are colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	// you have to enable the vertexAttribPointer before using it, 
	// according to the correct starting location.
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


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


	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
	ourShader.setInt("ourTexture1", 1);


	// To disable filling inside the polygon rendered.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		glfwSetKeyCallback(window, keyCallback);

		//rendering commands here
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // 
		glClear(GL_COLOR_BUFFER_BIT); // Clear --> fill {as i understand} of course its not correct.

		// bind the texture // maybe, its also setting the value of the uniform variabe sampler2D 
		glActiveTexture(GL_TEXTURE0);  // activating the  textire unit first before binding.
		glBindTexture(GL_TEXTURE_2D, texture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// render container.

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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



//vertex shader
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
	FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 1.0f)*vec4(ourColor, 1.0f);
}

*/


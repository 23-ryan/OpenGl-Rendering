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
#include "Camera.h"
#include "Texture.h"


#define SCR_WIDTH 400.0f
#define SCR_HEIGHT 400.0f

//float mixValue = 0.2f;
float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT;
bool firstMouse = true;
float currentFrame, lastFrame, deltaTime;
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);

Camera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));


void framebuffer_size_callback(GLFWwindow*, int, int);
void keyCallback(GLFWwindow*, int, int, int, int);
void changeMergeTextureParam(bool);
void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);

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

	glfwSwapInterval(1);
	// Load Glad, to render colors, otherwise it wouldn't be possible.
	gladLoadGL();

	// to change the rendering after the window size change.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, keyCallback);

	// activating the depth test
	glEnable(GL_DEPTH_TEST);

	Shader ourShader("shader.vs", "shader.fs");
	//Shader floorShader("shaderA.vs", "shaderA.fs");
	Shader lightShader("lightShader.vs", "lightShader.fs");

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
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	//float floorVertices[] = {
	//	-7.5f, 0.0f,  7.5f,
	//	-7.5f, 0.0f, -7.5f,
	//	 7.5f, 0.0f, -7.5f,
	//	 7.5f, 0.0f,  7.5f,
	//};

	//float floorVertices[] = {
	//	-8.5f, 0.0f,  8.5f,	 0.0f, 0.0f, // 0
	//	-8.5f, 0.0f, -8.5f,  1.0f, 0.0f, // 1
	//	 8.5f, 0.0f, -8.5f,  1.0f, 1.0f, // 2
	//	 8.5f, 0.0f,  8.5f,	 0.0f, 1.0f, // 3

	//};

	//unsigned int floorIndices[]{
	//	0, 1, 2,
	//	2, 3, 0,
	//};

	unsigned int VAO;
	unsigned int VBO;
	//unsigned int VAO_A;
	//unsigned int VBO_A;
	//unsigned int EBO_A;

	//bind the Vertex Array Object first, then bindand set vertex buffer(s), and then configure vertex attributes(s).
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// defining the light VAO so that the source cube of light remains isolated form any changes heppning in the environment.
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// see crefully how we bind a dufferent vertex array object with the same buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	//glGenVertexArrays(1, &VAO_A);
	//glGenBuffers(1, &VBO_A);
	//glGenBuffers(1, &EBO_A);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glVertexAttribPointer(0, sizeof(vertices), GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	//glEnableVertexAttribArray(0);

	//glBindVertexArray(VAO_A);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_A);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_A);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);

	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
	//glEnableVertexAttribArray(2);

	//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(3);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);



	// load image, create texture and generate mipmaps
	/*Texture texture1("Images/container.jpg");
	Texture texture2("Images/awesomeface.png");*/
	//Texture floorTexture("Images/floorImage.jpg");


	glm::vec3 cubePositions[] = {
		glm::vec3(-2.5f,  5.0f,  2.5f),
		glm::vec3(-2.5f,  5.0f,  -2.5f),
		glm::vec3(2.5f, 5.0f,   -2.5f),
		glm::vec3(2.5f, 5.0f,  2.5f),

		glm::vec3(-7.5f,  5.0f,  2.5f),
		glm::vec3(-7.5f,  5.0f,  -2.5f),
		glm::vec3(7.5f, 5.0f,   -2.5f),
		glm::vec3(7.5f, 5.0f,  2.5f),

		glm::vec3(-2.5f,  5.0f,  7.5f),
		glm::vec3(-2.5f,  5.0f,  -7.5f),
		glm::vec3(2.5f, 5.0f,   -7.5f),
		glm::vec3(2.5f, 5.0f,  7.5f),

		glm::vec3(-7.5f,  5.0f,  7.5f),
		glm::vec3(-7.5f,  5.0f,  -7.5f),
		glm::vec3(7.5f, 5.0f,   -7.5f),
		glm::vec3(7.5f, 5.0f,  7.5f)
	};

	ourShader.use();
	//glUniform3f(glGetUniformLocation(ourShader.ID, "ourColor"), 1.0f, 1.0f, 1.0f);
	ourShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	ourShader.setVec3("ourColor", glm::vec3(1.0f, 0.5f, 0.31f));
	//glUniform1i(glGetUniformLocation(ourShader.ID, "ourTexture"), 0);
	//ourShader.setInt("ourTexture1", 1);

	//floorShader.use();
	//floorShader.setInt("myTexture", 2);
	// To disable filling inside the polygon rendered.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FIgLL);

	glm::mat4 model, view, proj;
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);

	// render loop
	while (!glfwWindowShouldClose(window)) {

		//updating deltaTime
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//rendering commands here
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear --> fill {as i understand} of course its not correct. // Now I get it, its clearing the buffer from the previous rendered frame.

		//texture1.Bind(static_cast<unsigned int>(0));
		//texture2.Bind(static_cast<unsigned int>(1));
		//floorTexture.Bind(static_cast<unsigned int>(2));

		// view and proj matrix
		// cameraFront, cameraPos --> changing in the callback_function
		//model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));
		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		proj = glm::mat4(1.0f);
		view = myCamera.GetViewMatrix();
		proj = glm::perspective(glm::radians(myCamera.Zoom), 800.0f / 800.0f, 0.1f, 100.0f);

		//floorShader.use();
		//floorShader.setMat4("model", model);
		//floorShader.setMat4("proj", proj);
		//floorShader.setMat4("view", view);

		//glBindVertexArray(VAO_A);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_A);
		//glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, nullptr);
		//glBindVertexArray(0);


		// defining the model matrix to render rotatiing objects.
		//for (unsigned int i = 0; i < 16; i++)
		//{
		//	model = glm::mat4(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	if (false) {
		//		model = glm::rotate(model, (float)glm::radians(20.0f * i), glm::vec3(0.5f, 1.0f, 0.0f));
		//	}
		//	else {
		//		model = glm::rotate(model, (float)glfwGetTime() * (float)glm::radians(20.0f) * 2*i, glm::vec3(0.5f, 1.0f, 0.0f));
		//	}

		// updating the matrices i.e, model, view, projection.
		// model = glm::rotate(model, (float)glfwGetTime() * (float)glm::radians(20.0f)*10, glm::vec3(0.5f, 1.0f, 0.0f));

		ourShader.use();
		ourShader.setMat4("model", model);
		ourShader.setMat4("proj", proj);
		ourShader.setMat4("view", view);
		ourShader.setVec3("viewPos", myCamera.getCameraPos());
		ourShader.setVec3("lightPos", lightPos);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);


		//}
		model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.5f));
		std::cout << model[3][0] << std::endl;
		lightPos.x = model[3][0];
		lightPos.y = model[3][1];
		lightPos.z = model[3][2];



		model = glm::scale(model, glm::vec3(0.2f));

		//lightPos = model * glm::vec4(lightPos, 1.0f);
		//lightPos = glm::vec3(glm::vec3((float)cos(glfwGetTime()), 0.0f, (float)sin(glfwGetTime())));

		lightShader.use();
		lightShader.setMat4("model", model);
		lightShader.setMat4("proj", proj);
		lightShader.setMat4("view", view);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	//glDeleteVertexArrays(1, &VAO_A);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	/*glDeleteBuffers(1, &VBO_A);
	glDeleteBuffers(1, &EBO_A);*/

	//glDeleteBuffers(1, &EBO);

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


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UPWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWNWARD, deltaTime);


	//if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//	changeMergeTextureParam(true);
	//if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//	changeMergeTextureParam(false);

}


void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) // initially set to true
	{
		lastX = static_cast<float>(xPos);
		lastY = static_cast<float>(yPos);
		firstMouse = false;
	}

	float Xoffset = static_cast<float>(xPos) - lastX;
	float Yoffset = lastY - static_cast<float>(yPos); // reversed since y-coordinates range from bottom to top.
	lastX = static_cast<float>(xPos);
	lastY = static_cast<float>(yPos);

	myCamera.ProcessMouseMovement(Xoffset, Yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}

//void changeMergeTextureParam(bool signPositive) {
//
//	if (!(abs(mixValue - 1.0f) <= 0.0001f) && signPositive) {
//		mixValue += 0.1f;
//	}
//	else if (!(abs(mixValue - 0.0f) <= 0.0001f) && !signPositive) {
//		mixValue -= 0.1f;
//	}
//	return;
//}


// vertex shader
/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos; // positon of the vertex in the world's view.

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0f));
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
	// See, the next operation is necessary when rotation or scaling operation is performed,
	// because it will change the actual direction of the normal vector(think), so to undo that we have to do this.
	Normal = mat3(transpose(inverse(model))) * aNormal;
}
*/



// fragment shader
/*
#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 ourColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 256); // 32--> represents the shininess.
	vec3 specular = spec * lightColor;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(ourColor*result , 1.0f);
}
*/

// lightVertexShader --> (light object)
/*
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   gl_Position = proj * view * model * vec4(aPos, 1.0f);
}

*/

// lightFragmentShader --> (light object)
/*
# version 330 core

out vec4 FragColor;


void main(){
	FragColor = vec4(1.0f);
}
*/
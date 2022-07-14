// consider OpenGl as state machine.

#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

	// To reder the color over the window
void draw(GLFWwindow* window) {
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // 
	glClear(GL_COLOR_BUFFER_BIT); // Clear --> fill {as i understand} of course its not correct.
	glfwSwapBuffers(window); // swap current and the next buffers.(dual buffer system)
}

// To continue rendering the color over the new window size and not just the initial size.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); // specifies the location and the size of window to render.
	draw(window);
}

// to cllback function to process the input and print that, this callback function will be called by the 
//	function "glfwSetKeyCallback()", whcih takes this callback function as argument along with the context window.
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	else std::cout << char(key) << std::endl;
}

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

	glfwMakeContextCurrent(window); // make the window "window" as the current context.
	gladLoadGL(); // Load Glad, to render colors, otherwise it wouldn't be possible.
	draw(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // to change the rendering after the window size change.

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		glfwSetKeyCallback(window, keyCallback);

		//rendering commands here


		//check and call events and swap the buffers
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


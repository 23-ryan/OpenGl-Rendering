#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;

class Form {
	GLFWwindow* w;
	GLuint width, height;
	string name;
	public:
		Form(GLuint width, GLuint height, const string name) {
			this->name = name;
			this->width = width;
			this->height = height;
			w = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		}
		
		void show() {

			glfwMakeContextCurrent(this->w);
			glViewport(0, 0, width, height);
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(w);
			while (!glfwWindowShouldClose(w)) {
				glfwPollEvents();
			}
			glfwDestroyWindow(w);
		}

};
	void draw(GLFWwindow* window) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		draw(window);
	}
	//void processInput(GLFWwindow* window)
	//{
	//	
	//}
	
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		else std::cout << char(key) << std::endl;
	}

int main() {
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGl", NULL, NULL);
	if (window == NULL) {
		cout << "failed to load window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	draw(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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


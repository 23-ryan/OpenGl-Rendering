//Setting the color of the triangke through vertex shader by linking the vertex shadder with the fragment shader.


#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow*, int, int);
void keyCallback(GLFWwindow*, int, int, int, int);


//Vertex shader --> which contains the position related information of the redering object,
//and uses a vec3 to store that and further transform into vec4 as u can see.
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
// setting the value of the vec4 variable to send to fragment shader to use
"vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

//Vertex shader --> which contains the color related information of the rendering object,
//and uses a vec4.
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n" // setting the color value using the vertex shader
"void main()\n"
"{\n"
"	FragColor = vertexColor;\n"  // RGBA channel
"}\n\0";

//Note: 
// You can see we have defined the vec3 in vertex shader as "in" channel, means it takes input
// and gives output to the fragment shader and which finally outputs the object, that's why the vec4 in 
// fragment shader is defined as "out".


const char* vertexShaderSource1 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"  // RGBA channel
"}\n\0";


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

	//Creating vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// variables to get the compile status.
	int success;
	char infolog[512];

	//checking compile status.
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
		return 0;
	}

	//Creating fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//checking compile status.
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
		return 0;
	}

	// Creating an program object and linking vertex and fragment shaders.
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//checking compile status.
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
		return 0;
	}

	// Deleting the shaders as we don't need them now.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int vertexShader1;
	vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader1, 1, &vertexShaderSource1, NULL);
	glCompileShader(vertexShader1);


	//checking compile status.
	glGetShaderiv(vertexShader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader1, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
		return 0;
	}

	//Creating fragment Shader
	unsigned int fragmentShader1;
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);

	//checking compile status.
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
		return 0;
	}

	// Creating an program object and linking vertex and fragment shaders.
	unsigned int shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader1);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	//checking compile status.
	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram1, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
		return 0;
	}

	// Deleting the shaders as we don't need them now.
	glDeleteShader(vertexShader1);
	glDeleteShader(fragmentShader1);



	// *Normalized* device co-ordinates as float array.
	/*float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};*/
	float vertices1[] = {
	 0.0f,  0.0f, 0.0f,  // center
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f  // top left
	};

	float vertices2[] = {
	 0.0f,  0.0f, 0.0f,  // center
	 0.5f,  0.5f, 0.0f,   // top right
	 0.5f, -0.5f, 0.0f   // bottom left
	};

	//unsigned int indices[] = {  // note that we start from 0!
	//	0, 1, 2,   // first triangle
	//	0, 3, 4    // second triangle
	//};


	unsigned int VBO1;
	unsigned int VAO1;

	unsigned int VBO2;
	unsigned int VAO2;
	//unsigned int EBO;

	// bind the Vertex Array Object first, then bindand set vertex buffer(s), and then configure vertex attributes(s).
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	//glGenBuffers(1, &EBO);
	glBindVertexArray(VAO1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	//glGenBuffers(1, &EBO);
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// To disable filling inside the polygon rendered.
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		glfwSetKeyCallback(window, keyCallback);

		//rendering commands here
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // 
		glClear(GL_COLOR_BUFFER_BIT); // Clear --> fill {as i understand} of course its not correct.

		//Draw first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO1);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO2);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram1);

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



#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include "shader_s.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include "cube.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void processInput(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
unsigned int loadtexture(std::string filename);
void generate_model_matrices();

float vertices[] = {
	// positions          // normals           // texture coords //color white
	-0.5f, -0.5f, -0.5f, 	0.0f, 0.0f, -1.0f, 	0.0f, 0.0f, 	0.94f,0.94f,0.94f,
	0.5f, -0.5f, -0.5f, 	0.0f, 0.0f, -1.0f, 	1.0f, 0.0f, 	0.94f,0.94f,0.94f,
	0.5f, 0.5f, -0.5f, 		0.0f, 0.0f, -1.0f, 	1.0f, 1.0f, 	0.94f,0.94f,0.94f,
	0.5f, 0.5f, -0.5f, 		0.0f, 0.0f, -1.0f, 	1.0f, 1.0f, 	0.94f,0.94f,0.94f,
	-0.5f, 0.5f, -0.5f, 	0.0f, 0.0f, -1.0f, 	0.0f, 1.0f, 	0.94f,0.94f,0.94f,
	-0.5f, -0.5f, -0.5f, 	0.0f, 0.0f, -1.0f, 	0.0f, 0.0f, 	0.94f,0.94f,0.94f,
																//yellow	
	-0.5f, -0.5f, 0.5f, 	0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, 	1.f, 1.f, 0.25f,
	0.5f, -0.5f, 0.5f, 		0.0f, 0.0f, 1.0f, 	1.0f, 0.0f, 	1.f, 1.f, 0.25f,
	0.5f, 0.5f, 0.5f, 		0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, 	1.f, 1.f, 0.25f,
	0.5f, 0.5f, 0.5f, 		0.0f, 0.0f, 1.0f, 	1.0f, 1.0f, 	1.f, 1.f, 0.25f,
	-0.5f, 0.5f, 0.5f, 		0.0f, 0.0f, 1.0f, 	0.0f, 1.0f, 	1.f, 1.f, 0.25f,
	-0.5f, -0.5f, 0.5f, 	0.0f, 0.0f, 1.0f, 	0.0f, 0.0f, 	1.f, 1.f, 0.25f,
																//blue
	-0.5f, 0.5f, 0.5f, 		-1.0f, 0.0f, 0.0f, 	1.0f, 0.0f, 	0.1f, 0.42f, 0.66f,	
	-0.5f, 0.5f, -0.5f, 	-1.0f, 0.0f, 0.0f, 	1.0f, 1.0f, 	0.1f, 0.42f, 0.66f,	
	-0.5f, -0.5f, -0.5f, 	-1.0f, 0.0f, 0.0f, 	0.0f, 1.0f, 	0.1f, 0.42f, 0.66f,	
	-0.5f, -0.5f, -0.5f, 	-1.0f, 0.0f, 0.0f, 	0.0f, 1.0f, 	0.1f, 0.42f, 0.66f,	
	-0.5f, -0.5f, 0.5f, 	-1.0f, 0.0f, 0.0f, 	0.0f, 0.0f, 	0.1f, 0.42f, 0.66f,	
	-0.5f, 0.5f, 0.5f, 		-1.0f, 0.0f, 0.0f, 	1.0f, 0.0f, 	0.1f, 0.42f, 0.66f,	
																//green
	0.5f, 0.5f, 0.5f, 		1.0f, 0.0f, 0.0f, 	1.0f, 0.0f, 	0.14f, 0.61f, 0.18f,
	0.5f, 0.5f, -0.5f, 		1.0f, 0.0f, 0.0f, 	1.0f, 1.0f, 	0.14f, 0.61f, 0.18f,
	0.5f, -0.5f, -0.5f, 	1.0f, 0.0f, 0.0f, 	0.0f, 1.0f, 	0.14f, 0.61f, 0.18f,
	0.5f, -0.5f, -0.5f, 	1.0f, 0.0f, 0.0f, 	0.0f, 1.0f, 	0.14f, 0.61f, 0.18f,
	0.5f, -0.5f, 0.5f, 		1.0f, 0.0f, 0.0f, 	0.0f, 0.0f, 	0.14f, 0.61f, 0.18f,
	0.5f, 0.5f, 0.5f, 		1.0f, 0.0f, 0.0f, 	1.0f, 0.0f, 	0.14f, 0.61f, 0.18f,
																//red
	-0.5f, -0.5f, -0.5f, 	0.0f, -1.0f, 0.0f, 	0.0f, 1.0f, 	0.82f, 0.f, 0.16f,
	0.5f, -0.5f, -0.5f, 	0.0f, -1.0f, 0.0f, 	1.0f, 1.0f, 	0.82f, 0.f, 0.16f,
	0.5f, -0.5f, 0.5f, 		0.0f, -1.0f, 0.0f, 	1.0f, 0.0f, 	0.82f, 0.f, 0.16f,
	0.5f, -0.5f, 0.5f, 		0.0f, -1.0f, 0.0f, 	1.0f, 0.0f, 	0.82f, 0.f, 0.16f,
	-0.5f, -0.5f, 0.5f, 	0.0f, -1.0f, 0.0f, 	0.0f, 0.0f, 	0.82f, 0.f, 0.16f,
	-0.5f, -0.5f, -0.5f, 	0.0f, -1.0f, 0.0f, 	0.0f, 1.0f, 	0.82f, 0.f, 0.16f,
																//orange
	-0.5f, 0.5f, -0.5f, 	0.0f, 1.0f, 0.0f, 	0.0f, 1.0f, 	1.f, .43f, 0.13f,
	0.5f, 0.5f, -0.5f, 		0.0f, 1.0f, 0.0f, 	1.0f, 1.0f, 	1.f, .43f, 0.13f,
	0.5f, 0.5f, 0.5f, 		0.0f, 1.0f, 0.0f, 	1.0f, 0.0f, 	1.f, .43f, 0.13f,
	0.5f, 0.5f, 0.5f, 		0.0f, 1.0f, 0.0f, 	1.0f, 0.0f, 	1.f, .43f, 0.13f,
	-0.5f, 0.5f, 0.5f, 		0.0f, 1.0f, 0.0f, 	0.0f, 0.0f, 	1.f, .43f, 0.13f,
	-0.5f, 0.5f, -0.5f, 	0.0f, 1.0f, 0.0f, 	0.0f, 1.0f, 	1.f, .43f, 0.13f
	};

unsigned int VBO, VAO, instanceVBO;
unsigned int texture1;
std::vector<Cube> carpet;

Shader *myShader;

void generate_new_carpet()
{
	std::vector<Cube> newCarpet;
	if (carpet.empty())
	{
		newCarpet.push_back(Cube(0, 0, 0, 9));
	}
	else
	{
		for (Cube c : carpet)
		{
			std::vector<Cube> newBoxs = c.generate_carpet();
			newCarpet.insert(newCarpet.end(), newBoxs.begin(), newBoxs.end());
		}
	}
	carpet = newCarpet;
	generate_model_matrices();
}

void generate_model_matrices()
{
	std::vector<glm::mat4> modelMatrices;
	for (Cube c : carpet)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, c.pos);
		model = glm::scale(model, glm::vec3(c.dim));
		modelMatrices.push_back(model);
	}
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	glBufferData(GL_ARRAY_BUFFER, carpet.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STREAM_DRAW);

	// enable vertex attribute 3 -> mat4
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);

	//vertex attribute configuration
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(4, 1); // tell OpenGL this is an instanced vertex attribute.
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void render(glm::mat4 projection)
{
	glClearColor(.0f, 0.11f, 0.28f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// pass transformation matrices to the shader
	myShader->use();
	myShader->setMat4("projection", projection);
	myShader->setInt("myTexture1", 0);

	glm::mat4 view = glm::mat4(1.0f); //identity matrix;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -21.0f));
	view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(-0.5f, 1.0f, 0.0f));
	myShader->setMat4("view", view);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, carpet.size());
	glBindVertexArray(0);
}

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Menger sponge - press the SPACE BAR to expolde the cube", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	myShader = new Shader("./shaders/vertex_shader.vs", "./shaders/fragment_shader.fs");

	texture1 = loadtexture("./assets/border.jpg");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// color attribute
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// Start the carpet with one cube
	glGenBuffers(1, &instanceVBO);
	generate_new_carpet();

	// unbind the vertex array object
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	// create transformations
	glm::mat4 projection = glm::mat4(1.0f); //identity matrix
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		render(projection);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &instanceVBO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		generate_new_carpet();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// load and create a texture
unsigned int loadtexture(std::string filename)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(data);

	return texture;
}

#pragma once

#include <iostream>
#include "stb_image.h"
#include <string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int	m_Width, m_Height, m_nrChannels; // bits per pixel.

public:
	Texture(const std::string& path) 
		:m_RendererID(0), m_FilePath(path.c_str()), m_Width(0), m_Height(0), m_nrChannels(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_nrChannels, 4);

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (m_LocalBuffer)
		{
			// RGBA channel for png files.
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			std::cout << "Failed to load texture!" << std::endl;
		}

		stbi_image_free(m_LocalBuffer);
	}
	~Texture() {
		glDeleteTextures(1, &m_RendererID);
	}

	void Bind(unsigned int slot) const {
		// bind the texture // maybe, its also setting the value of the uniform variabe sampler2D 
		glActiveTexture(GL_TEXTURE0 + slot); // activating the  textire unit first before binding.
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	void Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline int GetWidth() const { return m_Width; };
	inline int Getheight() const { return m_Height; };

};

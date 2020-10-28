#pragma once

#include <array>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Mesh
{
private:
	std::vector<glm::vec3> m_Vertices;
	std::vector<unsigned int> m_Indices;
	GLuint vao, ibo;
public:
	Mesh(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices) : m_Vertices(vertices), m_Indices(indices)
	{
		Create();
	}

	~Mesh()
	{
		Destroy();
	}

	void Bind() const
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	}

	size_t GetVerticesCount() const
	{
		return m_Vertices.size();
	}
private:
	void Create()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), m_Vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);
	}

	void Destroy()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &ibo);
	}
public:
	void ReCreate(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
	{
		Destroy();

		m_Vertices = vertices;
		m_Indices = indices;

		Create();
	}
};
#pragma once

#include <string>
#include <unordered_map>

//#include <GL/glew.h>

#include "Debug.hpp"
#include "Util.hpp"

class Shader
{
private:
	std::string m_VertexPath, m_FragmentPath, m_VertexFile, m_FragmentFile;
	GLuint m_ProgramID, m_VertexID, m_FragmentID;

	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath) : m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
	{
		m_VertexFile = ReadFile(m_VertexPath);
		m_FragmentFile = ReadFile(m_FragmentPath);

		Create();
	}

	~Shader()
	{
		glDetachShader(m_ProgramID, m_VertexID);
		glDetachShader(m_ProgramID, m_FragmentID);
		glDeleteProgram(m_ProgramID);
	}

	void Bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void SetUniformMat4(const std::string& name, glm::mat4 v) const
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &v[0][0]);
	}

	int GetUniformLocation(const std::string& name) const
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int loc = glGetUniformLocation(m_ProgramID, name.c_str());

		m_UniformLocationCache[name] = loc;

		return loc;
	}
private:
	void Create()
	{
		m_VertexID = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexSource = m_VertexFile.c_str();
		glShaderSource(m_VertexID, 1, &vertexSource, nullptr);
		glCompileShader(m_VertexID);

		{
			GLint status;
			glGetShaderiv(m_VertexID, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLsizei length;
				glGetShaderiv(m_VertexID, GL_INFO_LOG_LENGTH, &length);

				GLchar* msg = (GLchar*)_malloca(length * sizeof(GLchar));
				glGetShaderInfoLog(m_VertexID, length, &length, msg);
				glDeleteShader(m_VertexID);

				cerr("Failed to compile Vertex Shader:\n" << msg);
			}
		}

		m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentSource = m_FragmentFile.c_str();
		glShaderSource(m_FragmentID, 1, &fragmentSource, nullptr);
		glCompileShader(m_FragmentID);

		{
			GLint status;
			glGetShaderiv(m_FragmentID, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				GLsizei length;
				glGetShaderiv(m_FragmentID, GL_INFO_LOG_LENGTH, &length);

				GLchar* msg = (GLchar*)_malloca(length * sizeof(GLchar));
				glGetShaderInfoLog(m_FragmentID, length, &length, msg);
				glDeleteShader(m_FragmentID);

				cerr("Failed to compile Fragment Shader:\n" << msg);
			}
		}

		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID, m_VertexID);
		glAttachShader(m_ProgramID, m_FragmentID);

		glLinkProgram(m_ProgramID);
		glValidateProgram(m_ProgramID);

		glDeleteShader(m_VertexID);
		glDeleteShader(m_FragmentID);
	}
};
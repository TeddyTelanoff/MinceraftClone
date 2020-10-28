#pragma once

#include "Window.hpp"

#include "Transform.hpp"
#include "Mesh.hpp"

class Camera
{
private:
	Transform* m_Transform;
	glm::mat4 m_Projection;
	float m_Fov;
	glm::vec2 m_ClipPlanes;
public:
	Camera(Transform*&& transform, float fov, const glm::vec2& clipPlanes)
		: m_Transform(transform), m_Projection(glm::mat4(1)), m_Fov(fov), m_ClipPlanes(clipPlanes) {}

	~Camera()
	{
		delete m_Transform;
	}

	const Transform* GetTransform() const
	{
		return m_Transform;
	}

	Transform* GetTransform()
	{
		return m_Transform;
	}

	glm::mat4 GetView() const
	{
		return m_Transform->GetView();
	}

	glm::mat4 GetProjection() const
	{
		return glm::perspective(m_Fov, (float)GetWindowWidth() / (float)GetWindowHeight(), m_ClipPlanes.x, m_ClipPlanes.y);
		//return glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, m_ClipPlanes.x, m_ClipPlanes.y);
	}
};
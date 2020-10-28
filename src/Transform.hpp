#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "util/ImGuiComponent.h"

class Transform : public ImGuiComponent
{
public:
	union
	{
		glm::vec3 m_Translation;
		glm::vec3 translation;
		glm::vec3 position;
	};
	union
	{
		glm::vec3 m_Rotation;
		glm::vec3 rotation;
	};
	union
	{
		glm::vec3 m_Scale;
		glm::vec3 scale;
	};

	Transform()
		: m_Translation(glm::vec3()), m_Rotation(glm::vec3()), m_Scale(glm::vec3(1))
	{
		GenID(3);
	}

	Transform(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		: m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
	{
		GenID(3);
	}

	~Transform()
	{
		DeleteID();
	}

	bool* ShowGUI() override
	{
		ImGui::Separator();

		ImGui::Text("Transform");

		DrawVec3("Position", m_Translation);
		DrawVec3("Rotation", m_Rotation);
		DrawVec3("Scale", m_Scale, 1);

		return nullptr;
	}

	glm::vec3 GetForward() const
	{
		glm::mat4 view = GetView();
		return normalize(glm::vec3(view[2]));
	}

	glm::vec3 GetRight() const
	{
		glm::mat4 view = GetView();
		return normalize(glm::vec3(view[0]));
	}

	glm::vec3 GetUp() const
	{
		glm::mat4 view = GetView();
		return normalize(glm::vec3(view[1]));
	}

	operator glm::mat4() const
	{
		return glm::translate(glm::mat4(1), m_Translation) * ((
				glm::rotate(glm::mat4(1), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) * (
				glm::rotate(glm::mat4(1), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) * (
					glm::rotate(glm::mat4(1), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1))
					)
				)
			) *
			glm::scale(glm::mat4(1), m_Scale));
	}

	glm::mat4 GetView() const
	{
		return glm::translate(glm::mat4(1), -m_Translation) * (
			glm::rotate(glm::mat4(1), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) * (
				glm::rotate(glm::mat4(1), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
				glm::rotate(glm::mat4(1), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1))
			)
		);
	}
};
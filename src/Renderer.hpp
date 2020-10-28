#pragma once

#include "Window.hpp"

#include "GameObject.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class Renderer
{
public:
	void RenderMesh(const GameObject* const gameObject, const Camera* const camera, const Shader* const shader) const
	{
		shader->Bind();
		shader->SetUniformMat4("u_Model", *gameObject->GetTransform());
		shader->SetUniformMat4("u_View", camera->GetView());
		shader->SetUniformMat4("u_Projection", camera->GetProjection());

		for (unsigned int i = 0; i < gameObject->GetMeshCount(); i++)
		{
			const Mesh& mesh = gameObject->GetMeshes()[i];

			mesh.Bind();
			
			glDrawElements(GL_TRIANGLES, mesh.GetVerticesCount() * 3, GL_UNSIGNED_INT, 0);
		}
	}

	void RenderMesh(const Transform* const transform, const Mesh* const mesh, const Camera* const camera, const Shader* const shader) const
	{
		mesh->Bind();

		shader->Bind();
		shader->SetUniformMat4("u_Model", *transform);
		shader->SetUniformMat4("u_View", camera->GetView());
		shader->SetUniformMat4("u_Projection", camera->GetProjection());

		glDrawElements(GL_TRIANGLES, mesh->GetVerticesCount() * 3, GL_UNSIGNED_INT, 0);
	}

	void RenderMesh(const Mesh* const mesh, const Camera* const camera, const Shader* const shader) const
	{
		mesh->Bind();

		shader->Bind();
		shader->SetUniformMat4("u_Model", glm::mat4(1));
		shader->SetUniformMat4("u_View", camera->GetView());
		shader->SetUniformMat4("u_Projection", camera->GetProjection());

		glDrawElements(GL_TRIANGLES, mesh->GetVerticesCount() * 3, GL_UNSIGNED_INT, 0);
	}
};
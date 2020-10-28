#pragma once

#include "Transform.hpp"
#include "Mesh.hpp"

class GameObject
{
private:
	Transform* m_Transform;
	Mesh* m_Meshes;
	unsigned int m_MeshCount;
public:
	GameObject(Transform*&& transform, Mesh*&& meshes, unsigned int meshCount)
		: m_Transform(transform), m_Meshes(meshes), m_MeshCount(meshCount) {}

	~GameObject()
	{
		delete m_Transform;
		delete[] m_Meshes;
	}

	const Transform* GetTransform() const
	{
		return m_Transform;
	}

	Transform*& GetTransform()
	{
		return m_Transform;
	}

	const Mesh* GetMeshes() const
	{
		return m_Meshes;
	}

	Mesh*& GetMeshes()
	{
		return m_Meshes;
	}

	const unsigned int GetMeshCount() const
	{
		return m_MeshCount;
	}
};
#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include "../Debug.hpp"
#include "../util/Hashing.hpp"
#include "Chunk.hpp"

class World
{
private:
	std::unordered_map<size_t, Chunk*> m_Chunks;
public:
	World()
	{
		GenerateChunk({ 0, 0 });
	}

	~World()
	{
		for (const auto& item : m_Chunks)
		{
			delete item.second;
		}
	}

	void Render(const Renderer* const renderer, const Camera* const camera, const Shader* const shader)
	{
		for (const auto& item : m_Chunks)
		{
			renderer->RenderMesh(&item.second->GetMesh(), camera, shader);
		}
	}

	void GenerateChunk(glm::ivec2 position)
	{
		size_t hash = Hash(position);

		asr(m_Chunks.find(hash) == m_Chunks.end(), "Chunk Already Exists!");
		m_Chunks[hash] = new Chunk(position);
		m_Chunks[hash]->Generate();
	}
};

World* s_CurrentWorld;
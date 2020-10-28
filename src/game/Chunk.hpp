#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Block.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_SIZE CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z
#define CHUNK_SIZE_VEC = glm::ivec3(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z);

class Chunk
{
private:
	glm::ivec2 m_Position;
	Block m_Blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z] = {};
	Mesh m_Mesh;
	std::vector<glm::vec3> m_Vertices;
	std::vector<unsigned int> m_Indices;
public:
	Chunk(glm::ivec2 position)
		: m_Position(position), m_Mesh(m_Vertices, m_Indices)
	{
		glm::vec3 worldPosition = { m_Position.x * CHUNK_SIZE_X, 0, m_Position.y * CHUNK_SIZE_Z };

		for (int x = 0; x < CHUNK_SIZE_X; x++)
			for (int y = 0; y < CHUNK_SIZE_Y; y++)
				for (int z = 0; z < CHUNK_SIZE_Z; z++)
					m_Blocks[x][y][z] = { (unsigned char)(x % 2), worldPosition + glm::vec3(x, y, z) };
	}

	void Generate()
	{
		m_Vertices.clear();
		m_Indices.clear();

		for (int x = 0; x < CHUNK_SIZE_X; x++)
			for (int y = 0; y < CHUNK_SIZE_Y; y++)
				for (int z = 0; z < CHUNK_SIZE_Z; z++)
				{
					BuildFace({ x, y, z }, { 0, 1, 0 }, { 1, 0, 0 });
					BuildFace({ x, y, z + 1 }, { 0, 1, 0 }, { 1, 0, 0 });

					//BuildFace({ x, y, z }, { 1, 0, 0 }, { 1, 0, 0 });
					//BuildFace({ x, y + 1, z }, { 1, 0, 0 }, { 1, 0, 0 });

					//BuildFace({ x, y, z }, { 0, 1, 0 }, { 0, 0, 1 });
					//BuildFace({ x + 1, y, z}, { 0, 1, 0 }, { 0, 0, 1 });
				}

		m_Mesh.ReCreate(m_Vertices, m_Indices);
	}

	void BuildFace(glm::vec3 corner, glm::vec3 top, glm::vec3 right)
	{
		unsigned int index = m_Vertices.size();

		m_Vertices.push_back(corner);
		m_Vertices.push_back(corner + top);
		m_Vertices.push_back(corner + top + right);
		m_Vertices.push_back(corner + right);

		m_Indices.push_back(index + 0);
		m_Indices.push_back(index + 1);
		m_Indices.push_back(index + 2);

		m_Indices.push_back(index + 0);
		m_Indices.push_back(index + 2);
		m_Indices.push_back(index + 3);
	}

	const Mesh& GetMesh() const
	{
		return m_Mesh;
	}

	Mesh& GetMesh()
	{
		return m_Mesh;
	}

	const Block& GetBlock(int x, int y, int z) const
	{
		return m_Blocks[x][y][z];
	}

	Block& GetBlock(int x, int y, int z)
	{
		return m_Blocks[x][y][z];
	}

	Block& SetBlock(int x, int y, int z, Block value)
	{
		return m_Blocks[x][y][z] = value;
	}
};
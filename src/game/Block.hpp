#pragma once

#include <glm/ext/vector_int3.hpp>

enum BlockType : unsigned char
{
	Air,
	Dirt
};

struct Block
{
	unsigned char type = BlockType::Air;
	glm::ivec3 position;
};
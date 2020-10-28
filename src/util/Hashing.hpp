#pragma once

#include <glm/glm.hpp>

template<typename t_Type>
size_t Hash(t_Type obj) noexcept
{
	static_assert(false, "Type Not Allowed");
}

template<>
size_t Hash<glm::ivec2>(glm::ivec2 obj) noexcept
{
	return std::hash<int>()(obj.x) ^ std::hash<int>()(obj.y);
}

template<>
size_t Hash<glm::ivec3>(glm::ivec3 obj) noexcept
{
	return std::hash<int>()(obj.x) ^ std::hash<int>()(obj.y) ^ std::hash<int>()(obj.z);
}

template<>
size_t Hash<glm::vec2>(glm::vec2 obj) noexcept
{
	return std::hash<float>()(obj.x) ^ std::hash<float>()(obj.y);
}

template<>
size_t Hash<glm::vec3>(glm::vec3 obj) noexcept
{
	return std::hash<float>()(obj.x) ^ std::hash<float>()(obj.y) ^ std::hash<float>()(obj.z);
}
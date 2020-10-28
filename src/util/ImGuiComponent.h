#pragma once

#include <vector>
#include <string>
#include <sstream>

#include <glm/glm.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "../Debug.hpp"

class ImGuiComponent
{
private:
	static std::vector<unsigned int> s_IDs;
protected:
	unsigned int m_ImGuiID;
	std::vector<std::string> m_Params;

	void GenID(unsigned int numIDs);

	void DeleteID();

	static void DrawVec3(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
public:
	virtual bool* ShowGUI();
};
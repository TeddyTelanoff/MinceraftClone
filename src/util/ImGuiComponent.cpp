#include "ImGuiComponent.h"

std::vector<unsigned int> ImGuiComponent::s_IDs;

void ImGuiComponent::GenID(unsigned int numIDs)
{
	bool invalid;
	m_ImGuiID = 0;
	do
	{
		invalid = false;

		for (unsigned int i = 0; i < s_IDs.size(); i++)
		{
			if (s_IDs[i] == m_ImGuiID)
			{
				invalid = true;

				m_ImGuiID++;
			}
		}
	} while (invalid);

	s_IDs.push_back(m_ImGuiID);

	std::vector<std::stringstream> ss;
	for (unsigned int i = 0; i < numIDs; i++)
	{
		ss.push_back(std::stringstream());
		ss[i] << "##" << i << m_ImGuiID;
		m_Params.push_back(ss[i].str());
	}
}

void ImGuiComponent::DeleteID()
{
	for (unsigned int i = 0; i < s_IDs.size(); i++)
		if (s_IDs[i] == m_ImGuiID)
			s_IDs.erase(s_IDs.begin() + i);
}

void ImGuiComponent::DrawVec3(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
{
	ImGuiIO& io = ImGui::GetIO();
	auto boldFont = io.Fonts->Fonts[0];

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

	float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("X", buttonSize))
		values.x = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Y", buttonSize))
		values.y = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushFont(boldFont);
	if (ImGui::Button("Z", buttonSize))
		values.z = resetValue;
	ImGui::PopFont();
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();
}

bool* ImGuiComponent::ShowGUI()
{
	ImGui::Separator();

	for (unsigned int i = 0; i < m_Params.size(); i++)
	{
		ImGui::Text("PARAM[%d]", i);
	}

	ImGui::Separator();

	return nullptr;
}
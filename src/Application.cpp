#include <cstdlib>
#include <iostream>
#include <array>
#include <thread>
#include <Windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#define IMGUI_IMPL_OPENGL_LOADER_GL3W
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Debug.hpp"

#include "Window.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "game/World.hpp"

void SetDarkThemeColors();
void SetupImGuiTheme();
void DrawImGui();
void Exit();

static bool shouldClose = false;

static GLFWwindow* window;

static std::vector<glm::vec3> vertices = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(1.0f,  0.0f,  0.0f),
	glm::vec3(1.0f,  1.0f,  0.0f),
	glm::vec3(0.0f,  1.0f,  0.0f),

	glm::vec3(0.0f,  0.0f,  1.0f),
	glm::vec3(1.0f,  0.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(0.0f,  1.0f,  1.0f)
};

static std::vector<unsigned int> indices = {
	0, 1, 2,
	0, 2, 3,

	0, 4, 7,
	0, 7, 3,

	1, 8, 9,
	1, 9, 3
};

static Renderer* s_Renderer;
static Camera* s_Camera;
static Transform* s_CamTransform;
static Shader* s_Shader;

void Setup()
{
	if (!glfwInit())
		exit(-1);

	if (!(window = glfwCreateWindow(1280, 720, "Minceraft", nullptr, nullptr)))
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwShowWindow(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		exit(-1);

	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();

	////SetupImGuiTheme();
	//SetDarkThemeColors();

	//ImGui_ImplGlfw_InitForOpenGL(window, false);
	//ImGui_ImplOpenGL3_Init();

	CreateCallbacks(window);

	s_CurrentWorld = new World();

	s_Renderer = new Renderer();
	s_Camera = new Camera(new Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1)), 80.0f, glm::vec2(0, 100));
	s_CamTransform = s_Camera->GetTransform();

	s_Shader = new Shader("res/shaderVert.shader", "res/shaderFrag.shader");

	glClearColor(0.22352941176f, 0.22352941176f, 0.22352941176f, 1);
}

void Update()
{
	glfwPollEvents();

	if (Keys[GLFW_KEY_ESCAPE] == GLFW_PRESS)
		shouldClose = true;

	if (Keys[GLFW_KEY_LEFT] == GLFW_PRESS)
		s_CamTransform->rotation.y++;
	if (Keys[GLFW_KEY_RIGHT] == GLFW_PRESS)
		s_CamTransform->rotation.y--;
	if (Keys[GLFW_KEY_UP] == GLFW_PRESS)
		s_CamTransform->rotation.x++;
	if (Keys[GLFW_KEY_DOWN] == GLFW_PRESS)
		s_CamTransform->rotation.x--;

	if (s_CamTransform->rotation.x > 90)
		s_CamTransform->rotation.x = 90;
	if (s_CamTransform->rotation.x < -90)
		s_CamTransform->rotation.x = -90;

	if (Keys[GLFW_KEY_A] == GLFW_PRESS)
		s_CamTransform->position -= s_CamTransform->GetRight();
	if (Keys[GLFW_KEY_D] == GLFW_PRESS)
		s_CamTransform->position += s_CamTransform->GetRight();
	if (Keys[GLFW_KEY_W] == GLFW_PRESS)
		s_CamTransform->position += s_CamTransform->GetForward();
	if (Keys[GLFW_KEY_S] == GLFW_PRESS)
		s_CamTransform->position -= s_CamTransform->GetForward();
	if (Keys[GLFW_KEY_SPACE] == GLFW_PRESS)
		s_CamTransform->position.y++;
	if (Keys[GLFW_KEY_LEFT_SHIFT] == GLFW_PRESS)
		s_CamTransform->position.y--;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
;
	s_CurrentWorld->Render(s_Renderer, s_Camera, s_Shader);

	DrawImGui();

	glfwSwapBuffers(window);
}

void DrawImGui()
{
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();

	//if (ImGui::BeginMainMenuBar())
	//{
	//	if (ImGui::BeginMenu("Application"))
	//	{
	//		if (ImGui::MenuItem("Exit", "Escape"))
	//			shouldClose = true;

	//		ImGui::EndMenu();
	//	}

	//	ImGui::EndMainMenuBar();
	//}

	//ImGui::Begin("Camera");
	//s_CamTransform->ShowGUI();
	//ImGui::End();

	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Exit()
{
	delete s_CurrentWorld;
	delete s_Renderer;
	delete s_Camera;
	delete s_Shader;

	glfwSetWindowShouldClose(window, GLFW_TRUE);

	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();

	//ImGui::DestroyContext();
	
	glfwTerminate();
}

int main()
{
	rrun(
		ShowWindow(GetConsoleWindow(), false);
	);
	 
	Setup();

	while (!(glfwWindowShouldClose(window) || shouldClose))
	{
		Update();
		Render();
	}

	Exit();
}

void SetupImGuiTheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style.GrabRounding = style.FrameRounding = 2.3f;
}

void SetDarkThemeColors()
{
	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}
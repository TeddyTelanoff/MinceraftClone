#pragma once

#include <GLFW/glfw3.h>

#include <imgui/imgui_impl_glfw.h>

static int WindowWidth = 1280, WindowHeight = 720;
static GLFWwindow* myWin;

static double MouseX, MouseY;
static double ScrollX, ScrollY;

static int Keys[GLFW_KEY_LAST];
static int MouseButtons[GLFW_MOUSE_BUTTON_LAST];

inline void CreateCallbacks(GLFWwindow* win)
{
	myWin = win;

	glfwSetWindowSizeCallback(win, [](GLFWwindow* window, int nWidth, int nHeight)
		{
			if (nWidth > 0 && nHeight > 0)
			{
				WindowWidth = nWidth;
				WindowHeight = nHeight;
			}

			//glViewport(0, 0, nWidth, nHeight);
		});

	glfwSetCharCallback(win, [](GLFWwindow* window, unsigned int c)
		{
			//ImGui_ImplGlfw_CharCallback(window, c);
		});

	glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key != GLFW_KEY_UNKNOWN && action != GLFW_REPEAT)
				Keys[key] = action;

			//ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
		});

	glfwSetMouseButtonCallback(win, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action != GLFW_REPEAT)
				MouseButtons[button] = action;

			//ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
		});

	glfwSetCursorPosCallback(win, [](GLFWwindow* window, double mouseX, double mouseY)
		{
			MouseX = mouseX;
			MouseY = mouseY;
		});

	glfwSetScrollCallback(win, [](GLFWwindow* window, double scrollX, double scrollY)
		{
			ScrollX = scrollX;
			ScrollY = scrollY;

			//ImGui_ImplGlfw_ScrollCallback(window, scrollX, scrollY);
		});
}

inline int GetWindowWidth()
{
	return WindowWidth;
}

inline int GetWindowHeight()
{
	return WindowHeight;
}

inline double GetScrollX()
{
	return ScrollX;
}

inline double GetScrollY()
{
	return ScrollY;
}

inline int* GetMouseButtons()
{
	return MouseButtons;
}

inline void SetWindowSize(int width, int height)
{
	glfwSetWindowSize(myWin, width, height);
}
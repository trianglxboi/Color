#include "ColorPCH.h"
#include "GenericInput.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Color
{
	InputState GenericInput::GetKeyState_(KeyCode keycode) const
	{
		GLFWwindow* window = (GLFWwindow*) Application::Get()->GetMainWindow()->GetNativeWindowPtr();
		return (InputState) glfwGetKey(window, keycode);
	}

	InputState GenericInput::GetMouseButtonState_(MouseCode button) const
	{
		GLFWwindow* window = (GLFWwindow*) Application::Get()->GetMainWindow()->GetNativeWindowPtr();
		return (InputState) glfwGetMouseButton(window, button);
	}

	glm::vec2 GenericInput::GetMousePosition_() const
	{
		GLFWwindow* window = (GLFWwindow*) Application::Get()->GetMainWindow()->GetNativeWindowPtr();
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float) xpos, (float) ypos };
	}

	float GenericInput::GetMouseX_() const
	{
		return GetMousePosition_().x;
	}

	float GenericInput::GetMouseY_() const
	{
		return GetMousePosition_().y;
	}
}

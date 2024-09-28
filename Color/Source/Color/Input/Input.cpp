#include "ColorPCH.h"
#include "Input.h"

#include "Platform/Windows/WindowsInput.h"
#include "Platform/Linux/LinuxInput.h"

namespace Color
{
	Scope<Input> Input::s_Instance = CreateScope<CL_ConcatWithPlatformName(Input)>();

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		InputState state = GetKeyState(keycode);
		return state == InputState::Press;
	}

	bool Input::IsKeyDown(KeyCode keycode)
	{
		InputState state = GetKeyState(keycode);
		return state == InputState::Press || state == InputState::Repeat;
	}

	bool Input::IsKeyUp(KeyCode keycode)
	{
		InputState state = GetKeyState(keycode);
		return state == InputState::Release;
	}

	bool Input::IsMouseButtonDown(MouseCode button)
	{
		InputState state = GetMouseButtonState(button);
		return state == InputState::Press;
	}

	bool Input::IsMouseButtonUp(MouseCode button)
	{
		InputState state = GetMouseButtonState(button);
		return state == InputState::Release;
	}
}

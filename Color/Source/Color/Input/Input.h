#pragma once

#include "Core/Base.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include <glm/glm.hpp>

namespace Color
{
	enum class InputState
	{
		Press = 1,
		Repeat = 2,
		Release = 0
	};

	class Input
	{
	public:
		virtual ~Input() = default;
	public:
		static InputState GetKeyState(KeyCode keycode) { return s_Instance->GetKeyState_(keycode); }
		static InputState GetMouseButtonState(MouseCode button) { return s_Instance->GetMouseButtonState_(button); }

		static bool IsKeyPressed(KeyCode keycode);
		static bool IsKeyDown(KeyCode keycode);
		static bool IsKeyUp(KeyCode keycode);

		static bool IsMouseButtonDown(MouseCode button);
		static bool IsMouseButtonUp(MouseCode button);

		static glm::vec2 GetMousePosition() { return s_Instance->GetMousePosition_(); }
		static float GetMouseX() { return s_Instance->GetMouseX_(); }
		static float GetMouseY() { return s_Instance->GetMouseY_(); }
	protected:
		virtual InputState GetKeyState_(KeyCode keycode) const = 0;
		virtual InputState GetMouseButtonState_(MouseCode button) const = 0;

		virtual glm::vec2 GetMousePosition_() const = 0;
		virtual float GetMouseX_() const = 0;
		virtual float GetMouseY_() const = 0;
	private:
		static Scope<Input> s_Instance;
	};
}

#pragma once

#include "Input/Input.h"

namespace Color
{
	class GenericInput : public Input
	{
	protected:
		virtual InputState GetKeyState_(KeyCode keycode) const override;
		virtual InputState GetMouseButtonState_(MouseCode button) const override;

		virtual glm::vec2 GetMousePosition_() const override;
		virtual float GetMouseX_() const override;
		virtual float GetMouseY_() const override;
	};
}

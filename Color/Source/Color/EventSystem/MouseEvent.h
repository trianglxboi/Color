#pragma once

#include "EventSystem/Event.h"
#include "Input/MouseCodes.h"

#include <glm/glm.hpp>
#include <sstream>

namespace Color
{
	class MouseButtonEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Input | EC_Mouse | EC_MouseButton);
		MouseCode GetButton() const { return m_Button; }
	protected:
		MouseButtonEvent(MouseCode button)
			: m_Button(button) { }
	private:
		MouseCode m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		CL_EVENT_TYPE_DEF(MouseButtonPressed);
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << GetButton();
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		CL_EVENT_TYPE_DEF(MouseButtonReleased);
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << GetButton();
			return ss.str();
		}
	};

	class MouseMovedEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Input | EC_Mouse);
		CL_EVENT_TYPE_DEF(MouseMoved);
	public:
		MouseMovedEvent(const glm::vec2& position)
			: m_Position(position) { }

		MouseMovedEvent(float xpos, float ypos)
			: m_Position{xpos, ypos} { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_Position.x << ", " << m_Position.y;
			return ss.str();
		}

		const glm::vec2& GetPosition() const { return m_Position; }
		float GetPosX() const { return m_Position.x; }
		float GetPosY() const { return m_Position.y; }
	private:
		glm::vec2 m_Position;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Input | EC_Mouse);
		CL_EVENT_TYPE_DEF(MouseScrolled);
	public:
		MouseScrolledEvent(const glm::vec2& offset)
			: m_Offset(offset) { }

		MouseScrolledEvent(float xoff, float yoff)
			: m_Offset{xoff, yoff} { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_Offset.x << ", " << m_Offset.y;
			return ss.str();
		}

		const glm::vec2& GetOffset() const { return m_Offset; }
		float GetOffsetX() const { return m_Offset.x; }
		float GetOffsetY() const { return m_Offset.y; }
	private:
		glm::vec2 m_Offset;
	};
}

#pragma once

#include "EventSystem/Event.h"

#include <glm/glm.hpp>
#include <sstream>

namespace Color
{
	class WindowClosedEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Application);
		CL_EVENT_TYPE_DEF(WindowClosed);
	public:
		WindowClosedEvent() = default;
	};

	class WindowMovedEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Application);
		CL_EVENT_TYPE_DEF(WindowMoved);
	public:
		WindowMovedEvent(const glm::uvec2& position)
			: m_Position(position) { }

		WindowMovedEvent(uint32_t xpos, uint32_t ypos)
			: m_Position{xpos, ypos} { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent: " << m_Position.x << ", " << m_Position.y;
			return ss.str();
		}

		const glm::uvec2& GetPosition() const { return m_Position; }
		uint32_t GetPosX() const { return m_Position.x; }
		uint32_t GetPosY() const { return m_Position.y; }
	private:
		glm::uvec2 m_Position;
	};
	
	class WindowResizedEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Application);
		CL_EVENT_TYPE_DEF(WindowResized);
	public:
		WindowResizedEvent(const glm::uvec2& size)
			: m_Size(size) { }

		WindowResizedEvent(uint32_t xsize, uint32_t ysize)
			: m_Size{xsize, ysize} { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << m_Size.x << ", " << m_Size.y;
			return ss.str();
		}

		const glm::uvec2& GetSize() const { return m_Size; }
		uint32_t GetSizeX() const { return m_Size.x; }
		uint32_t GetSizeY() const { return m_Size.y; }
	private:
		glm::uvec2 m_Size;
	};

	class WindowFocusEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Application);
		CL_EVENT_TYPE_DEF(WindowFocus);
	public:
		WindowFocusEvent() = default;
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Application);
		CL_EVENT_TYPE_DEF(WindowLostFocus);
	public:
		WindowLostFocusEvent() = default;
	};
}

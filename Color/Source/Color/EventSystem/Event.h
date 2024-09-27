#pragma once

#include "Core/Base.h"

namespace Color
{
	enum class EventType
	{
		None = 0,
		WindowClosed, WindowMoved, WindowResized, WindowFocus, WindowLostFocus,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		EC_None        =        0,
		EC_Application = CL_BIT(1),
		EC_Input       = CL_BIT(2),
		EC_Keyboard    = CL_BIT(3),
		EC_Mouse       = CL_BIT(4),
		EC_MouseButton = CL_BIT(5)
	};

	class Event
	{
	public:
		// Specifies whether or not this event has been handled before, presumably by another layer.
		bool Handled = false;
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual std::string ToString() const { return GetEventName(); }
			
		bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}
	};

	// Helper macros to implement the Event derivate classes.
	#define CL_EVENT_CATEGORY_DEF(category) virtual int GetCategoryFlags() const override { return (int)(category); }
	#define CL_EVENT_TYPE_DEF(type)         static ::Color::EventType GetStaticEventType() { return ::Color::EventType::##type; } \
                                            virtual EventType GetEventType() const override { return GetStaticEventType(); } \
											virtual const char* GetEventName() const override { return #type; }

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: m_Event(e) { }

		template <typename T, typename F>
		bool Dispatch(F&& function) const
		{
			if (m_Event.GetEventType() == T::GetStaticEventType())
			{
				m_Event.Handled |= function((T&) m_Event);
				return true;
			}

			return false;
		}
	private:
		Event& m_Event;
	};
}

template <typename OStream>
inline OStream& operator<<(OStream& stream, const Color::Event& e)
{
	return stream << e.ToString();
}

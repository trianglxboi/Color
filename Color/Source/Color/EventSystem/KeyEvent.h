#pragma once

#include "EventSystem/Event.h"
#include "Input/KeyCodes.h"

#include <sstream>

namespace Color
{
	class KeyEvent : public Event
	{
	public:
		CL_EVENT_CATEGORY_DEF(EC_Input | EC_Keyboard);
		KeyCode GetKeyCode() const { return m_KeyCode; }
	protected:
		KeyEvent(KeyCode keycode)
			: m_KeyCode(keycode) { }
	private:
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		CL_EVENT_TYPE_DEF(KeyPressed);
	public:
		KeyPressedEvent(KeyCode keycode, bool isRepeat)
			: KeyEvent(keycode), m_Repeat(isRepeat) { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << ", " << (m_Repeat ? "true" : "false");
			return ss.str();
		}

		bool IsRepeat() const { return m_Repeat; }
	private:
		bool m_Repeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		CL_EVENT_TYPE_DEF(KeyReleased);
	public:
		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode) { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << GetKeyCode();
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		CL_EVENT_TYPE_DEF(KeyTyped);
	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode) { }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << GetKeyCode();
			return ss.str();
		}
	};
}

#include "ColorPCH.h"
#include "WindowsPopup.h"

namespace Color
{
	WindowsPopup::WindowsPopup(std::string_view caption, std::string_view content, PopupButtonSet buttonset, PopupIcon icon)
		: m_Caption(caption), m_Content(content), m_Buttonset(buttonset), m_Icon(icon)
	{
	}

	PopupCreateResult WindowsPopup::CreateAndWait()
	{
		// TODO: When we have a main window, think about giving the HWND handle to it.
		// We might not do it, just a thought for now. The decision will be made when it gets added.
		return (PopupCreateResult) MessageBoxA(NULL, m_Content.c_str(), m_Caption.c_str(), (UINT)((long) m_Buttonset | (long) m_Icon));
	}

	void WindowsPopup::SetCaption(std::string_view caption)
	{
		m_Caption = caption;
	}

	void WindowsPopup::SetContent(std::string_view content)
	{
		m_Content = content;
	}

	void WindowsPopup::SetButtonset(PopupButtonSet buttonset)
	{
		m_Buttonset = buttonset;
	}

	void WindowsPopup::SetIcon(PopupIcon icon)
	{
		m_Icon = icon;
	}
}

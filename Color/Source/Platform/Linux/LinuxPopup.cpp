#include "ColorPCH.h"
#include "LinuxPopup.h"

namespace Color
{
	LinuxPopup::LinuxPopup(std::string_view caption, std::string_view content, PopupButtonSet buttonset, PopupIcon icon)
		: m_Caption(caption), m_Content(content), m_Buttonset(buttonset), m_Icon(icon)
	{
	}

	PopupCreateResult LinuxPopup::CreateAndWait()
	{
		// Linux doesn't support Popups yet.
		return PopupCreateResult::CreationError;
	}

	void LinuxPopup::SetCaption(std::string_view caption)
	{
		m_Caption = caption;
	}

	void LinuxPopup::SetContent(std::string_view content)
	{
		m_Content = content;
	}

	void LinuxPopup::SetButtonset(PopupButtonSet buttonset)
	{
		m_Buttonset = buttonset;
	}

	void LinuxPopup::SetIcon(PopupIcon icon)
	{
		m_Icon = icon;
	}
}

#pragma once

#include "Misc/Popup.h"

namespace Color
{
	class LinuxPopup : public Popup
	{
	public:
		LinuxPopup(std::string_view caption, std::string_view content, PopupButtonSet buttonset, PopupIcon icon);

		virtual PopupCreateResult CreateAndWait() override;

		virtual void SetCaption(std::string_view caption) override;
		virtual void SetContent(std::string_view content) override;
		virtual void SetButtonset(PopupButtonSet buttonset) override;
		virtual void SetIcon(PopupIcon icon) override;

		virtual const std::string& GetCaption() const override { return m_Caption; }
		virtual const std::string& GetContent() const override { return m_Content; }
		virtual PopupButtonSet GetButtonset() const override { return m_Buttonset; }
		virtual PopupIcon GetIcon() const override { return m_Icon; }
	private:
		std::string m_Caption, m_Content;
		PopupButtonSet m_Buttonset = PopupButtonSet::None;
		PopupIcon m_Icon = PopupIcon::None;
	};
}

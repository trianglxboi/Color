#pragma once

#include "Misc/SmartPtrs.h"

#include <string_view>
#include <string>

namespace Color
{
	// NOTE: Color's Popup API is heavily designed after Windows' MessageBoxes. Windows implementation will be very straight forward.
	// On the other hand, other platform's implementations must convert these to their respective native APIs' format.

	enum class PopupButtonSet : long
	{
		None              = 0x00000000L,
		AbortRetryIgnore  = 0x00000002L,
		CancelTryContinue = 0x00000006L,
		Help              = 0x00004000L,
		Ok                = 0x00000000L,
		OkCancel          = 0x00000001L,
		RetryCancel       = 0x00000005L,
		YesNo             = 0x00000004L,
		YesNoCancel       = 0x00000003L
	};

	enum class PopupIcon : long
	{
		None        = 0x00000000L,
		Warning     = 0x00000030L,
		Information = 0x00000040L,
		Question    = 0x00000020L,
		Error       = 0x00000010L
	};

	enum class PopupCreateResult
	{
		// Special case where the MessageBox couldn't be created.
		CreationError = 0,

		Ok       = 1,
		Cancel   = 2,
		Abort    = 3,
		Retry    = 4,
		Ignore   = 5,
		Yes      = 6,
		No       = 7,
		TryAgain = 10,
		Continue = 11
	};

	class Popup
	{
	public:
		virtual ~Popup() = default;

		// Creates the popup and blocks the execution of the current thread until the user inputs their decision.
		virtual PopupCreateResult CreateAndWait() = 0;

		virtual void SetCaption(std::string_view caption) = 0;
		virtual void SetContent(std::string_view content) = 0;
		virtual void SetButtonset(PopupButtonSet buttonset) = 0;
		virtual void SetIcon(PopupIcon icon) = 0;

		virtual const std::string& GetCaption() const = 0;
		virtual const std::string& GetContent() const = 0;
		virtual PopupButtonSet GetButtonset() const = 0;
		virtual PopupIcon GetIcon() const = 0;

		static Scope<Popup> Create(std::string_view caption = "", std::string_view content = "", PopupButtonSet buttonset = PopupButtonSet::None, PopupIcon icon = PopupIcon::None);
	};
}

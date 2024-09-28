#pragma once

#include "Core/Base.h"
#include "EventSystem/Event.h"

namespace Color
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;
		bool Resizable, Fullscreen, VSync;

		WindowProps(std::string_view title = "Color Window",
					uint32_t width = 1600,
					uint32_t height = 900,
					bool resizable = true,
					bool fullscreen = false,
					bool vSync = true)
			: Title(title), Width(width), Height(height), Resizable(resizable), Fullscreen(fullscreen), VSync(vSync) { }
	};

	class Window
	{
	public:
		typedef std::function<void(Event&)> EventCallbackFn;
	public:
		virtual ~Window() = default;

		virtual bool Init() = 0;
		virtual bool IsOpen() const = 0;
		virtual void Update() = 0;
		virtual bool Destroy() = 0;

		virtual void RequestAttention() = 0;
		virtual void Focus() = 0;
		virtual bool HasFocus() const = 0;

		virtual void SetTitle(std::string_view title) = 0;
		virtual void SetSize(const glm::uvec2& size) = 0;
		virtual void SetSize(uint32_t width, uint32_t height) = 0;
		virtual void SetWidth(uint32_t width) = 0;
		virtual void SetHeight(uint32_t height) = 0;
		virtual void SetVSync(bool vSync) = 0;
		virtual void SetEventCallback(EventCallbackFn fn) = 0;

		virtual const std::string& GetTitle() const = 0;
		virtual glm::uvec2 GetSize() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual bool IsResizable() const = 0;
		virtual bool IsFullscreen() const = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindowPtr() const = 0;

		static Scope<Window> Create(const WindowProps& props = {});
	};
}

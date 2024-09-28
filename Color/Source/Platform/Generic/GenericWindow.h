#pragma once

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Color
{
	class GenericWindow : public Window
	{
	public:
		GenericWindow(const WindowProps& props);
		virtual ~GenericWindow() override;

		virtual bool Init() override;
		virtual bool IsOpen() const override;
		virtual void Update() override;
		virtual bool Destroy() override;

		virtual void RequestAttention() override;
		virtual void Focus() override;
		virtual bool HasFocus() const override;

		virtual void SetTitle(std::string_view title) override;
		virtual void SetSize(const glm::uvec2& size) override;
		virtual void SetSize(uint32_t width, uint32_t height) override;
		virtual void SetWidth(uint32_t width) override;
		virtual void SetHeight(uint32_t height) override;
		virtual void SetVSync(bool vSync) override;
		virtual void SetEventCallback(EventCallbackFn fn) override;

		virtual const std::string& GetTitle() const override { return m_Data.Title; }
		virtual glm::uvec2 GetSize() const override { return { m_Data.Width, m_Data.Height }; }
		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }
		virtual bool IsResizable() const override { return m_Data.Resizable; }
		virtual bool IsFullscreen() const override { return m_Data.Fullscreen; }
		virtual bool IsVSync() const override { return m_Data.VSync; }
		virtual void* GetNativeWindowPtr() const override { return m_Handle; }
	private:
		GLFWwindow* m_Handle = nullptr;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			GLFWwindow*& HandleRef;

			std::string Title;
			uint32_t Width, Height;
			bool Resizable, Fullscreen, VSync;

			EventCallbackFn EventCallback = nullptr;
			void BroadcastEvent(Event& e)
			{
				if (EventCallback)
				{
					EventCallback(e);
				}
			}

			WindowData(GLFWwindow*& handleRef, std::string_view title, uint32_t width, uint32_t height, bool resizable, bool fullscreen, bool vSync)
				: HandleRef(handleRef), Title(title), Width(width), Height(height), Resizable(resizable), Fullscreen(fullscreen), VSync(vSync) { }
		} m_Data;
	};
}

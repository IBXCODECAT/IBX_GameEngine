#pragma once

#include "ibxpch.h"

#include "IBX/Core/Core.h"
#include "IBX/Events/Event.h"

namespace IBX_Engine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "IBX Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class IBX_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		/// <summary>
		/// Returns a Window
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeWindow() const = 0;

		// Must be implemented per platform (Windows, Mac, Linux, iOS, Android, etc.)
		static Window* Create(const WindowProps& props = WindowProps());
	};
}
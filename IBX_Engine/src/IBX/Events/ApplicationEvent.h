#pragma once

#include "Event.h"

#include <sstream>
#include <spdlog/fmt/fmt.h>

namespace IBX_Engine
{
	class IBX_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class IBX_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class IBX_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class IBX_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class IBX_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}

// Include this after your class definitions to provide formatter specializations
namespace fmt {
	template<>
	struct formatter<IBX_Engine::WindowResizeEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::WindowResizeEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "WindowResizeEvent: {}, {}", e.GetWidth(), e.GetHeight());
		}
	};

	template<>
	struct formatter<IBX_Engine::WindowCloseEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::WindowCloseEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "WindowCloseEvent");
		}
	};

	template<>
	struct formatter<IBX_Engine::AppTickEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::AppTickEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "AppTickEvent");
		}
	};

	template<>
	struct formatter<IBX_Engine::AppUpdateEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::AppUpdateEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "AppUpdateEvent");
		}
	};

	template<>
	struct formatter<IBX_Engine::AppRenderEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::AppRenderEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "AppRenderEvent");
		}
	};
}
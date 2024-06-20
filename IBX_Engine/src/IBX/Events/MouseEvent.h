#pragma once

#include "Event.h"
#include <sstream>

// Include for spdlog formatter specializations
#include <spdlog/fmt/fmt.h>

namespace IBX_Engine {

	class IBX_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class IBX_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class IBX_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class IBX_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class IBX_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

// Include this after your class definitions to provide formatter specializations
namespace fmt {
	template<>
	struct formatter<IBX_Engine::MouseMovedEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::MouseMovedEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "MouseMovedEvent: {}, {}", e.GetX(), e.GetY());
		}
	};

	template<>
	struct formatter<IBX_Engine::MouseScrolledEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::MouseScrolledEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "MouseScrolledEvent: {}, {}", e.GetXOffset(), e.GetYOffset());
		}
	};

	template<>
	struct formatter<IBX_Engine::MouseButtonPressedEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::MouseButtonPressedEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "MouseButtonPressedEvent: {}", e.GetMouseButton());
		}
	};

	template<>
	struct formatter<IBX_Engine::MouseButtonReleasedEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::MouseButtonReleasedEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "MouseButtonReleasedEvent: {}", e.GetMouseButton());
		}
	};
}

#pragma once

#include "Event.h"

// Include the fmt library for spdlog formatting
#include <spdlog/fmt/fmt.h>

namespace IBX_Engine {

	class IBX_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		// Protected constructor so nothing else can create a KeyEvent
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class IBX_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class IBX_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}

// Include this after your class definitions to provide formatter specializations
namespace fmt {
	template<>
	struct formatter<IBX_Engine::KeyPressedEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::KeyPressedEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "KeyPressedEvent: {} ({}) repeats", e.GetKeyCode(), e.GetRepeatCount());
		}
	};

	template<>
	struct formatter<IBX_Engine::KeyReleasedEvent> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::KeyReleasedEvent& e, FormatContext& ctx) {
			return format_to(ctx.out(), "KeyReleasedEvent: {}", e.GetKeyCode());
		}
	};
}

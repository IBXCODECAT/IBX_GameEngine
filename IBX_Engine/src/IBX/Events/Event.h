#pragma once

#include "ibxpch.h"

#include "IBX/Core.h"

#include <spdlog/fmt/fmt.h>

namespace IBX_Engine
{
	// Events in the engine are currently blocking, meaning that when an event occurs
	// it immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event bus
	// and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class IBX_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/// <summary>
		/// Utility function to check if the event is in a certain category.
		/// </summary>
		/// <param name="category">- EventCategory</param>
		/// <returns>True if in category</returns>
		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		/// <summary>
		/// Utility function to check if the event has been handled.
		/// </summary>
		/// <returns>True if handled</returns>
		inline bool Handled() const { return m_Handled; }

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		
		/// <summary>
		/// Dispatches the event to the function if the event is of type T.
		/// </summary>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

// Include this after your class definitions to provide formatter specializations
namespace fmt {
	template<>
	struct formatter<IBX_Engine::Event> {
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template<typename FormatContext>
		auto format(const IBX_Engine::Event& e, FormatContext& ctx) {
			return format_to(ctx.out(), "{}", e.ToString());
		}
	};
}
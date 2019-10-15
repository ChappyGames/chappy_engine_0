#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace ChappyEngine {

	/*
	Events in Chappy Engine are currently blocking, meaning when an event occurs, it
	immediately gets dispatched and must be dealt with right away. For the future,
	a better strategy might be to buffer events in an event bus and process them
	during the "event" update stage.
	*/

	enum class EventType {
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	};

	enum EventCategory {
		NONE = 0,
		EVENT_CATEGORY_APPLICATION = BIT(0),
		EVENT_CATEGORY_INPUT = BIT(1),
		EVENT_CATEGORY_KEYBOARD = BIT(2),
		EVENT_CATEGORY_MOUSE = BIT(3),
		EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class CHAPPY_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		inline bool IsInCategory(EventCategory aCategory) {
			return GetCategoryFlags() & aCategory;
		}
	protected:
		bool handled = false;
	};

	class CHAPPY_API EventDispatcher {
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& aEvent) : event(aEvent) {}

		template<typename T>
		bool Dispatch(EventFn<T> aFunc) {
			if (event.GetEventType() == T::GetStaticType()) {
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& aOS, const Event& aE) {
		return aOS << aE.ToString();
	}
}

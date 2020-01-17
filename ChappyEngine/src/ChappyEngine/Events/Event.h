#pragma once

#include "ChappyEngine\Core.h"

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
		EVENT_TYPE_NONE = 0,
		EVENT_TYPE_WINDOW_CLOSE, EVENT_TYPE_WINDOW_RESIZE, EVENT_TYPE_WINDOW_FOCUS, EVENT_TYPE_WINDOW_LOST_FOCUS, EVENT_TYPE_WINDOW_MOVED,
		EVENT_TYPE_APP_TICK, EVENT_TYPE_APP_UPDATE, EVENT_TYPE_APP_RENDER,
		EVENT_TYPE_KEY_PRESSED, EVENT_TYPE_KEY_RELEASED, EVENT_TYPE_KEY_TYPED,
		EVENT_TYPE_MOUSE_BUTTON_PRESSED, EVENT_TYPE_MOUSE_BUTTON_RELEASED, EVENT_TYPE_MOUSE_MOVED, EVENT_TYPE_MOUSE_SCROLLED
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
		virtual bool Handled() const { return handled; }
		
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
				event.handled = aFunc(*(T*)&event);
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

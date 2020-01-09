#pragma once

#include "Core.h"
#include "Event.h"
#include "ChappyEngine/Events/ApplicationEvent.h"

#include "Window.h"

namespace ChappyEngine {

	class CHAPPY_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int aWidth, unsigned int aHeight) : width(aWidth), height(aHeight) {}

		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "WindowResizeEvent: " << width << ", " << height;
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_WINDOW_RESIZE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	private:
		unsigned int width;
		unsigned int height;
	};

	class CHAPPY_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(EVENT_TYPE_WINDOW_CLOSE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class CHAPPY_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(EVENT_TYPE_APP_TICK)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class CHAPPY_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(EVENT_TYPE_APP_UPDATE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

	class CHAPPY_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(EVENT_TYPE_APP_RENDER)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};
}

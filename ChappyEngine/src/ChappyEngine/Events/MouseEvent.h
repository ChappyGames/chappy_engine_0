#pragma once

#include "Event.h"

namespace ChappyEngine {

	class CHAPPY_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float aX, float aY) : mouseX(aX), mouseY(aY) {}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "MouseMovedEvent: " << mouseX << ", " << mouseY;
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

	private:
		float mouseX;
		float mouseY;
	};

	class CHAPPY_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float aOffsetX, float aOffsetY) : offsetX(aOffsetX), offsetY(aOffsetY) {}

		inline float GetXOffset() const { return offsetX; }
		inline float GetYOffset() const { return offsetY; }

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)

	private:
		float offsetX;
		float offsetY;
	};

	class CHAPPY_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return button; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
	protected:
		MouseButtonEvent(int aButton) : button(aButton) {}

		int button;
	};

	class CHAPPY_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int aButton) : MouseButtonEvent(aButton) {}

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "MouseButtonPressedEvent: " << button;
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_MOUSE_BUTTON_PRESSED)
	};

	class CHAPPY_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int aButton) : MouseButtonEvent(aButton) {}

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "MouseButtonReleasedEvent: " << button;
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_MOUSE_BUTTON_RELEASED)
	};
}

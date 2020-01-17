#pragma once

#include "Event.h"

namespace ChappyEngine {

	class CHAPPY_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return keyCode; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)

	protected:
		KeyEvent(int aKeyCode) : keyCode(aKeyCode) {}

		int keyCode;
	};

	class CHAPPY_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int aKeyCode, int aRepeatCount)
			: KeyEvent(aKeyCode), repeatCount(aRepeatCount) {}

		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_KEY_PRESSED)

	private:
		int repeatCount;
	};

	class CHAPPY_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int aKeyCode) : KeyEvent(aKeyCode) {}

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "KeyReleasedEvent: " << keyCode;
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_KEY_RELEASED)
	};

	class CHAPPY_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int aKeyCode)
			: KeyEvent(aKeyCode) {}

		std::string ToString() const override {
			std::stringstream lSS;
			lSS << "KeyTypedEvent: " << keyCode;
			return lSS.str();
		}

		EVENT_CLASS_TYPE(EVENT_TYPE_KEY_TYPED)

	private:
	};
}

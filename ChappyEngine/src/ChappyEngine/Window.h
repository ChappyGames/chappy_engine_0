#pragma once

#include "cepch.h"

#include "Core.h"
#include "Events\Event.h"

namespace ChappyEngine {

	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& aTitle = "Chappy Engine v0", unsigned int aWidth = 1280, unsigned int aHeight = 720) : title(aTitle), width(aWidth), height(aHeight) {}
	};

	// Interface representing a desktop system based Window
	class CHAPPY_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& aCallback) = 0;
		virtual void SetVSync(bool aEnabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& aProps = WindowProps());
	};

}
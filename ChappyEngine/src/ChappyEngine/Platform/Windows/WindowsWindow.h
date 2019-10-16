#pragma once

#include "ChappyEngine\Window.h"

#include <GLFW\glfw3.h>

namespace ChappyEngine {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& aProps);
		virtual	~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& aCallback) override { data.eventCallback = aCallback; }
		void SetVSync(bool aEnabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& aProps);
		virtual void Shutdown();
	private:
		GLFWwindow* window;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		WindowData data;
	};
}

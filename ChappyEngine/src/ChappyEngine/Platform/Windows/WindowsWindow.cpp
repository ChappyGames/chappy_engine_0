#include "cepch.h"
#include "WindowsWindow.h"

namespace ChappyEngine {

	static bool GLFWInitialized = false;

	Window* Window::Create(const WindowProps& aProps) {
		return new WindowsWindow(aProps);
	}

	WindowsWindow::WindowsWindow(const WindowProps& aProps) {
		Init(aProps);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& aProps) {
		data.title = aProps.title;
		data.width = aProps.width;
		data.height = aProps.height;

		CE_CORE_INFO("Creating window {0} ({1}, {2})", aProps.title, aProps.width, aProps.height);

		if (!GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int lSuccess = glfwInit();
			CE_CORE_ASSERT(lSuccess, "Could not initializeGLFW!");

			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)aProps.width, (int)aProps.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSync(bool aEnabled) {
		if (aEnabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		data.vSync = aEnabled;
	}

	bool WindowsWindow::IsVSync() const {
		return data.vSync;
	}
}
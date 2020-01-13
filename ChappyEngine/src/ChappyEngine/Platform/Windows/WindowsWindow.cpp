#include "cepch.h"
#include "WindowsWindow.h"

#include "ChappyEngine/Events/ApplicationEvent.h";
#include "ChappyEngine/Events/MouseEvent.h";
#include "ChappyEngine/Events/KeyEvent.h";

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace ChappyEngine {

	static bool GLFWInitialized = false;

	static void GLFWErrorCallback(int aError, const char* aDescription) {
		CE_CORE_ERROR("GLFW Error ({0}): {1}", aError, aDescription);
	}

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

			glfwSetErrorCallback(GLFWErrorCallback);

			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)aProps.width, (int)aProps.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		int lStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CE_CORE_ASSERT(lStatus, "Failed to initialize GLAD!");
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* aWindow, int aWidth, int aHeight) {
			WindowData& lData = *(WindowData*)glfwGetWindowUserPointer(aWindow);

			lData.width = aWidth;
			lData.height = aHeight;

			WindowResizeEvent lEvent(aWidth, aHeight);
			lData.eventCallback(lEvent);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* aWindow) {
			WindowData& lData = *(WindowData*)glfwGetWindowUserPointer(aWindow);

			WindowCloseEvent lEvent;
			lData.eventCallback(lEvent);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* aWindow, int aKey, int aScanCode, int aAction, int aMods) {
			WindowData& lData = *(WindowData*)glfwGetWindowUserPointer(aWindow);

			switch (aAction) {
				case GLFW_PRESS: {
					KeyPressedEvent lEvent(aKey, 0);
					lData.eventCallback(lEvent);
					break;
				}

				case GLFW_RELEASE: {
					KeyReleasedEvent lEvent(aKey);
					lData.eventCallback(lEvent);
					break;
				}
			
				case GLFW_REPEAT: {
					KeyPressedEvent lEvent(aKey, 1);
					lData.eventCallback(lEvent);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* aWindow, int aButton, int aAction, int aMods) {
			WindowData& lData = *(WindowData*)glfwGetWindowUserPointer(aWindow);

			switch (aAction) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent lEvent(aButton);
					lData.eventCallback(lEvent);
					break;
				}

				case GLFW_RELEASE: {
					MouseButtonReleasedEvent lEvent(aButton);
					lData.eventCallback(lEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* aWindow, double aXOffset, double aYOffset) {
			WindowData& lData = *(WindowData*)glfwGetWindowUserPointer(aWindow);

			MouseScrolledEvent lEvent((float)aXOffset, (float)aYOffset);
			lData.eventCallback(lEvent);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* aWindow, double aXPos, double aYPos) {
			WindowData& lData = *(WindowData*)glfwGetWindowUserPointer(aWindow);

			MouseMovedEvent lEvent((float)aXPos, (float)aYPos);
			lData.eventCallback(lEvent);
		});
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
#include "cepch.h"
#include "Application.h"

#include "Events\ApplicationEvent.h"
#include "Log.h"

//TEMP
#include <GLFW\glfw3.h>

namespace ChappyEngine {

	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run() {

		while (running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			window->OnUpdate();
		}
	}
}

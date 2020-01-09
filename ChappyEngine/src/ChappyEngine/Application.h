#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace ChappyEngine {

	class CHAPPY_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool running = true;
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();
}

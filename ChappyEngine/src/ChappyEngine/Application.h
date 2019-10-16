#pragma once

#include "Core.h"
#include "Events\Event.h"
#include "Window.h"

namespace ChappyEngine {

	class CHAPPY_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();
}

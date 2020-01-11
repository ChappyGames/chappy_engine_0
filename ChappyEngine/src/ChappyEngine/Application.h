#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "ChappyEngine/LayerStack.h"


namespace ChappyEngine {

	class CHAPPY_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* aLayer);
		void PushOverlay(Layer* aLayer);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();
}

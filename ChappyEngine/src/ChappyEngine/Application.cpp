#include "cepch.h"
#include "Application.h"

#include "Events\ApplicationEvent.h"
#include "Log.h"

#include <glad/glad.h>

namespace ChappyEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}


	Application::~Application()
	{
	}

	void Application::Run() {

		while (running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		
		EventDispatcher lDispatcher(e);
		lDispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		CE_CORE_TRACE("{0}", e);

		for (auto i = layerStack.end(); i != layerStack.begin();) {
			(*--i)->OnEvent(e);
			if (e.Handled()) {
				break;
			}
		}
	}

	void Application::PushLayer(Layer* aLayer) {
		layerStack.PushLayer(aLayer);
	}

	void Application::PushOverlay(Layer* aLayer) {
		layerStack.PushOverlay(aLayer);
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {

		running = false;
		return true;
	}
}

#include "Application.h"

#include "Events\ApplicationEvent.h"
#include "Log.h"

namespace ChappyEngine {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizeEvent lEvent(1280, 720);

		CE_TRACE(lEvent);

		while (true);
	}
}

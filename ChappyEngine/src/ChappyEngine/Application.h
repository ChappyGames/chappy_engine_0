#pragma once

#include "Core.h"

namespace ChappyEngine {

	class CHAPPY_API Application {

	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();
}

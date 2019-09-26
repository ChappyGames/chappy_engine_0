#include <ChappyEngine.h>

class Sandbox : public ChappyEngine::Application {

public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

ChappyEngine::Application* ChappyEngine::CreateApplication() {
	return new Sandbox();
}
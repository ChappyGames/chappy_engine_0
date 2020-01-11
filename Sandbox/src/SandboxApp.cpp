#include <ChappyEngine.h>

class ExampleLayer : public ChappyEngine::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		CE_INFO("ExampleLayer::Update");
	}

	void OnEvent(ChappyEngine::Event& aEvent) override {
		CE_TRACE("{0}", aEvent);
	}
};

class Sandbox : public ChappyEngine::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

ChappyEngine::Application* ChappyEngine::CreateApplication() {
	return new Sandbox();
}
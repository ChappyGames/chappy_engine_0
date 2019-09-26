#pragma once

#ifdef  CE_PLATFORM_WINDOWS

extern ChappyEngine::Application* ChappyEngine::CreateApplication();

int main(int argc, char** argv) {

	printf("Chappy Engine V0\n");
	auto lApp = ChappyEngine::CreateApplication();
	lApp->Run();
	delete lApp;

	return 0;
}

#endif


#include "cepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "ChappyEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include"ChappyEngine/Application.h"

// TEMP
#include "GLFW/glfw3.h"

namespace ChappyEngine {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach() {

		ImGui::CreateContext();
		ImGui::StyleColorsDark();


		ImGuiIO& lIO = ImGui::GetIO();
		lIO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		lIO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // TEMP: Should use ChappyEngine Keycodes
        lIO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        lIO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        lIO.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        lIO.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        lIO.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        lIO.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        lIO.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        lIO.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        lIO.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        lIO.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        lIO.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        lIO.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        lIO.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        lIO.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        lIO.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        lIO.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        lIO.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        lIO.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        lIO.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        lIO.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        lIO.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        lIO.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() {

	}

	void ImGuiLayer::OnUpdate() {

        ImGuiIO& lIO = ImGui::GetIO();
        Application& lApp = Application::Get();
        lIO.DisplaySize = ImVec2(lApp.GetWindow().GetWidth(), lApp.GetWindow().GetHeight());

        float lTime = (float)glfwGetTime();
        lIO.DeltaTime = time > 0.0f ? (lTime - time) : (1.0f / 60.0f);
        time = lTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool lShowDemo = true;
        ImGui::ShowDemoWindow(&lShowDemo);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& aEvent) {

	}
}
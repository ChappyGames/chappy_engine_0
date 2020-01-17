#include "cepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "ChappyEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include"ChappyEngine/Application.h"

// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

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

        EventDispatcher lDispatcher(aEvent);
        lDispatcher.Dispatch<MouseButtonPressedEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        lDispatcher.Dispatch<MouseButtonReleasedEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        lDispatcher.Dispatch<MouseMovedEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        lDispatcher.Dispatch<MouseScrolledEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        lDispatcher.Dispatch<KeyPressedEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        lDispatcher.Dispatch<KeyReleasedEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        lDispatcher.Dispatch<KeyTypedEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        lDispatcher.Dispatch<WindowResizeEvent>(CE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.MouseWheelH += e.GetXOffset();
        lIo.MouseWheel += e.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.KeysDown[e.GetKeyCode()] = true;

        lIo.KeyCtrl = lIo.KeysDown[GLFW_KEY_LEFT_CONTROL] || lIo.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        lIo.KeyShift = lIo.KeysDown[GLFW_KEY_LEFT_SHIFT] || lIo.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        lIo.KeyAlt = lIo.KeysDown[GLFW_KEY_LEFT_ALT] || lIo.KeysDown[GLFW_KEY_RIGHT_ALT];
        lIo.KeySuper = lIo.KeysDown[GLFW_KEY_LEFT_SUPER] || lIo.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
        ImGuiIO& lIo = ImGui::GetIO();
        int lKeycode = e.GetKeyCode();
        if (lKeycode > 0 && lKeycode < 0x10000) {
            lIo.AddInputCharacter((unsigned short)lKeycode);
        }

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {

        ImGuiIO& lIo = ImGui::GetIO();
        lIo.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        lIo.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }
}
#pragma once

#include "ChappyEngine/Layer.h"

namespace ChappyEngine {

	class CHAPPY_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& aEvent);
	private:
		float time = 0.0f;
	};
}

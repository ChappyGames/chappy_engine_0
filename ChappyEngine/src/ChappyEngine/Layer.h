#pragma once

#include "ChappyEngine/Core.h"
#include "ChappyEngine/Events/Event.h"

namespace ChappyEngine {

	class CHAPPY_API Layer {
	public:
		Layer(const std::string& aName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& aEvent) {}

		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
	};
}
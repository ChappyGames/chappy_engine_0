#pragma once

#include "ChappyEngine/Core.h"
#include "Layer.h"

#include <vector>

namespace ChappyEngine {

	class CHAPPY_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* aLayer);
		void PushOverlay(Layer* aOverlay);
		void PopLayer(Layer* aLayer);
		void PopOverlay(Layer* aOverlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }

	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;
	};
}


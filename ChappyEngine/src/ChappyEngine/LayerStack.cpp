#include "cepch.h"
#include "LayerStack.h"

namespace ChappyEngine {

	LayerStack::LayerStack() {
		layerInsert = layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* aLayer) {
		layerInsert = layers.emplace(layerInsert, aLayer);
	}

	void LayerStack::PushOverlay(Layer* aOverlay) {
		layers.emplace_back(aOverlay);
	}

	void LayerStack::PopLayer(Layer* aLayer) {
		auto lIt = std::find(layers.begin(), layers.end(), aLayer);
		if (lIt != layers.end()) {
			layers.erase(lIt);
			layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* aOverlay) {
		auto lIt = std::find(layers.begin(), layers.end(), aOverlay);
		if (lIt != layers.end()) {
			layers.erase(lIt);
		}
	}
}

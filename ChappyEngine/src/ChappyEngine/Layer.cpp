#pragma once
#include "cepch.h"
#include "Layer.h"

namespace ChappyEngine {

	Layer::Layer(const std::string& aDebugName) : debugName(aDebugName) {}
	Layer::~Layer() {}
}
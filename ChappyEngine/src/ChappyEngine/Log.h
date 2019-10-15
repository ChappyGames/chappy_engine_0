#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog\fmt\ostr.h"

namespace ChappyEngine {
	class CHAPPY_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define CE_CORE_TRACE(...)::ChappyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CE_CORE_INFO(...)::ChappyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CE_CORE_WARN(...)::ChappyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CE_CORE_ERROR(...)::ChappyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CE_CORE_FATAL(...)::ChappyEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CE_TRACE(...)::ChappyEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CE_INFO(...)::ChappyEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CE_WARN(...)::ChappyEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CE_ERROR(...)::ChappyEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CE_FATAL(...)::ChappyEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

// Because we define these as macros, we can actually define the macro as nothing which will strip the logs from distribution builds!


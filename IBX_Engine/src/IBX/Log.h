#pragma once

#include "Core.h";

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // for custom formatting
#include <spdlog/sinks/stdout_color_sinks.h>

namespace IBX_Engine
{
	class IBX_API Log
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Logging Macros
#define IBX_CORE_FATAL(...) ::IBX_Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define IBX_CORE_ERROR(...) ::IBX_Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define IBX_CORE_WARN(...) ::IBX_Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define IBX_CORE_DEBUG(...) ::IBX_Engine::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define IBX_CORE_INFO(...) ::IBX_Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define IBX_CORE_TRACE(...) ::IBX_Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client Logging Macros
#define IBX_CLIENT_FATAL(...) ::IBX_Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define IBX_CLIENT_ERROR(...) ::IBX_Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define IBX_CLIENT_WARN(...) ::IBX_Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define IBX_CLIENT_DEBUG(...) ::IBX_Engine::Log::GetClientLogger()->debug(__VA_ARGS__)
#define IBX_CLIENT_INFO(...) ::IBX_Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define IBX_CLIENT_TRACE(...) ::IBX_Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
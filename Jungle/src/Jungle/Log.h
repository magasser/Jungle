#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "Core.h"

namespace Jungle
{
	class JUNGLE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define JNGL_CORE_TRACE(...)	::Jungle::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JNGL_CORE_DEBUG(...)	::Jungle::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define JNGL_CORE_INFO(...)		::Jungle::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JNGL_CORE_WARN(...)		::Jungle::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JNGL_CORE_ERROR(...)	::Jungle::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JNGL_CORE_CRITICAL(...) ::Jungle::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define JNGL_TRACE(...)			::Jungle::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JNGL_DEBUG(...)			::Jungle::Log::GetClientLogger()->debug(__VA_ARGS__)
#define JNGL_INFO(...)			::Jungle::Log::GetClientLogger()->info(__VA_ARGS__)
#define JNGL_WARN(...)			::Jungle::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JNGL_ERROR(...)			::Jungle::Log::GetClientLogger()->error(__VA_ARGS__)
#define JNGL_CRITICAL(...)		::Jungle::Log::GetClientLogger()->critical(__VA_ARGS__)


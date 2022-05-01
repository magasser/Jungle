#pragma once

#ifdef JNGL_PLATFORM_WINDOWS
	#ifdef JNGL_BUILD_DLL
		#define JUNGLE_API __declspec(dllexport)
	#else 
		#define JUNGLE_API __declspec(dllimport)
	#endif
#else
	#error Jungle Engine is only supported on Windows
#endif

#define BIT(x) (1 << (x))

#define JNGL_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Jungle
{
	template<typename T>
	using Scope = std::unique_ptr<T>; 
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

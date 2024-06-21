#pragma once

#ifdef IBX_PLATFORM_WINDOWS

	#ifdef IBX_BUILD_DLL
		#define IBX_API __declspec(dllexport)
	#else
		#define IBX_API __declspec(dllimport)
	#endif // IBX_BUILD_DLL

#else
	#error IBX_Engine only supports Windows!
#endif // IBX_PLATFORM_WINDOWS

#ifdef HZ_ENABLE_ASSERTS
#define IBX_CLIENT_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define IBX_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define IBX_CLIENT_ASSERT(x, ...)
#define IBX_CORE_ASSERT(x, ...)
#endif

// BIT(x) is a macro that shifts 1 by x bits to the left
#define BIT(x) (1 << x)
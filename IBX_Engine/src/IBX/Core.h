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

// BIT(x) is a macro that shifts 1 by x bits to the left
#define BIT(x) (1 << x)
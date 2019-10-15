#pragma once

#ifdef CE_PLATFORM_WINDOWS
	#ifdef CE_BUILD_DLL
		#define CHAPPY_API __declspec(dllexport)
	#else
		#define CHAPPY_API __declspec(dllimport)
	#endif
#else
	#error Chappy Engine only supports Windows!
#endif

#define BIT(x) (1 << x)

#ifndef CLEGINE_CORE_COMMON_HPP
#define CLEGINE_CORE_COMMON_HPP

#include <Core/Platform.hpp>

#define CLEGINE_DEBUG_ALWAYS

#define BIT(x)	(1 << x)

#if defined(CLEGINE_PLATFORM_WINDOWS)
# if defined(CLEGINE_BUILD_API)
#	define API_EXPORT __declspec(dllexport)
#	define API_IMPORT __declspec(dllimport)
# else
# define API_EXPORT
# define API_IMPORT
# endif
# ifdef _MSC_VER
#  pragma warning(disable: 4251)
# endif
# ifndef NOMINMAX
#  define NOMINMAX
# endif
#else 
# define API_EXPORT
# define API_IMPORT
#endif

#endif // CLEGINE_CORE_COMMON_HPP
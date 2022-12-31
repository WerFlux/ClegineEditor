#ifndef CLEGINE_CORE_COMMON_HPP
#define CLEGINE_CORE_COMMON_HPP

#ifdef _WIN32
# define CLEGINE_PLATFORM_WINDOWS
# ifdef _WIN64
#  define CLEGINE_PLATFORM_WINDOWS_X64
# else
#  define CLEGINE_PLATFORM_WINDOWS_X86
# endif
#else
# error "Clegine only works for Windows (for now)"
#endif

#define CLEGINE_DEBUG_ALWAYS
#define CLEGINE_DISABLE_ASSERTING 0

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
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